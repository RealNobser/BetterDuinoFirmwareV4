#include <Arduino.h>
#include "Holo.h"

Holo::Holo(int VerticalServo, int HorizonatlServo, int LightPin) :
    VerticalServo(VerticalServo),
    HorizonatlServo(HorizonatlServo),
    LightPin(LightPin)
{
    Servo_H.attach(HorizonatlServo);
    Servo_V.attach(VerticalServo);

    pinMode(LightPin, OUTPUT);
    digitalWrite(LightPin, LOW);
}

void Holo::on()
{
    digitalWrite(LightPin, HIGH);
}

void Holo::off()
{
    digitalWrite(LightPin, LOW);
}
