#!/usr/bin/env python3
"""Generates the Wokwi diagrams for all three board roles from the pin mapping in include/config.h.

    python3 sim/make_diagrams.py

Each role gets an Arduino Nano (ATmega328P @ 16 MHz, same as the MarcDuino), its servos, LEDs for
heartbeat/AUX1/holo lights and a logic analyzer on the software-serial outputs (A0/A1) and AUX1 (A2),
so the bytes sent to slave, sound module, magic panel and Teeces can be inspected (VCD export).
"""
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONFIG = os.path.join(ROOT, "include", "config.h")


def pins():
    defs = {}
    for line in open(CONFIG, encoding="utf-8"):
        m = re.match(r"\s*#define\s+(P_\w+)\s+(\d+)", line)
        if m:
            defs[m.group(1)] = int(m.group(2))
    return defs


P = pins()


def nano_pin(n):
    """Arduino pin number -> Wokwi Nano pin name."""
    return "A%d" % (n - 14) if n >= 14 else str(n)


class Diagram:
    def __init__(self):
        self.parts = [{"type": "wokwi-arduino-nano", "id": "nano", "top": 260, "left": 380, "attrs": {}}]
        self.conns = []

    def servo(self, pid, label, pin, x):
        self.parts.append({"type": "wokwi-servo", "id": pid, "top": 0, "left": x, "rotate": 270,
                           "attrs": {"hornColor": "DarkBlue"}})
        self.parts.append({"type": "wokwi-text", "id": pid + "_lbl", "top": -24, "left": x + 4,
                           "attrs": {"text": label}})
        self.conns += [["nano:GND.1", pid + ":GND", "black", []],
                       ["nano:5V", pid + ":V+", "red", []],
                       ["nano:" + nano_pin(pin), pid + ":PWM", "orange", []]]

    def led(self, pid, label, pin, color, x):
        self.parts.append({"type": "wokwi-led", "id": pid, "top": 470, "left": x,
                           "attrs": {"color": color, "label": label}})
        self.parts.append({"type": "wokwi-resistor", "id": pid + "_r", "top": 430, "left": x - 10,
                           "rotate": 90, "attrs": {"value": "220"}})
        self.conns += [["nano:GND.1", pid + ":C", "black", []],
                       [pid + "_r:1", pid + ":A", "green", []],
                       ["nano:" + nano_pin(pin), pid + "_r:2", "green", []]]

    def analyzer(self, channels):
        names = ",".join(label.replace(" ", "_") for _, label in channels)
        self.parts.append({"type": "wokwi-logic-analyzer", "id": "logic", "top": 300, "left": 700,
                           "attrs": {"bufferSize": "1000000", "triggerMode": "off", "channelNames": names}})
        self.conns.append(["nano:GND.1", "logic:GND", "black", []])
        for ch, (pin, _) in enumerate(channels):
            self.conns.append(["nano:" + nano_pin(pin), "logic:D%d" % ch, "violet", []])

    def write(self, role, comment):
        path = os.path.join(ROOT, "sim", role, "diagram.json")
        data = {"version": 1, "author": "RealNobser", "editor": "wokwi",
                "parts": self.parts, "connections": self.conns, "dependencies": {},
                "serialMonitor": {"display": "always", "newline": "cr"}}   # firmware expects CR-terminated commands
        with open(path, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
            f.write("\n")
        print("wrote", os.path.relpath(path, ROOT), "-", comment)


def common_leds(d):
    d.led("heartbeat", "LED2", P["P_LED2"], "red", 400)
    d.led("aux1", "AUX1", P["P_AUX1"], "blue", 470)


def master():
    d = Diagram()
    servos = ["P_SERVO_%02d" % i for i in range(1, 12)]
    for i, name in enumerate(servos):
        d.servo("servo%d" % (i + 1), "P%d" % (i + 1), P[name], i * 95)
    common_leds(d)
    d.analyzer([(P["P_SERIAL1"], "to slave"), (P["P_SERIAL2"], "to MP3"), (P["P_AUX1"], "AUX1")])
    d.write("master", "Dome Master: 11 panel servos, A0 = slave serial, A1 = sound serial")


def slave():
    d = Diagram()
    holo = [("P_HPF_H", "FH"), ("P_HPF_V", "FV"), ("P_HPR_H", "RH"), ("P_HPR_V", "RV"),
            ("P_HPT_H", "TH"), ("P_HPT_V", "TV"), ("P_SERVO_12", "P12"), ("P_SERVO_13", "P13")]
    for i, (name, label) in enumerate(holo):
        d.servo("servo_%s" % label.lower(), label, P[name], i * 95)
    common_leds(d)
    d.led("holo_front", "FL", P["P_FL"], "white", 540)
    d.led("holo_rear", "RL", P["P_RL"], "white", 610)
    d.led("holo_top", "TL", P["P_TL"], "white", 680)
    d.analyzer([(P["P_SERIAL1"], "magic panel"), (P["P_SERIAL2"], "teeces"), (P["P_AUX1"], "AUX1")])
    d.write("slave", "Dome Slave: 3 holos (2 servos + light each), panels 12/13")


def body():
    d = Diagram()
    servos = [("P_DPL", "DPL"), ("P_UTIL_ARM_U", "UtlU"), ("P_UTIL_ARM_L", "UtlL"), ("P_LEFT_BDY_DR", "LDoor"),
              ("P_LEFT_ARM", "LArm"), ("P_LEFT_ARM_TOOL", "LTool"), ("P_RIGHT_BDY_DR", "RDoor"),
              ("P_RIGHT_ARM", "RArm"), ("P_RIGHT_ARM_TOOL", "RTool"), ("P_CHRG_BAY_DR", "Charge"), ("P_RFU", "RFU")]
    for i, (name, label) in enumerate(servos):
        d.servo("servo%d" % (i + 1), label, P[name], i * 95)
    common_leds(d)
    d.analyzer([(P["P_SERIAL1"], "serial 1"), (P["P_SERIAL2"], "serial 2"), (P["P_AUX1"], "AUX1")])
    d.write("body", "Body Master: 11 body servos")


if __name__ == "__main__":
    master()
    slave()
    body()
