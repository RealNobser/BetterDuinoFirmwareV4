# Wokwi simulation

One Wokwi project per board role. All three run the same firmware image (`pio run`); the role is
selected at runtime via `#MD00` / `#MD01` / `#MD02` exactly like on the real board.

| Directory | Role | Hardware in the diagram |
|--|--|--|
| `master/` | Dome Master | 11 panel servos, heartbeat (A3) and AUX1 (A2) LEDs, logic analyzer on A0 (to slave), A1 (to sound module), A2 |
| `slave/`  | Dome Slave  | 3 holos (H/V servo + light on 10/11/12), panel servos 12/13, logic analyzer on A0 (magic panel), A1 (Teeces), A2 |
| `body/`   | Body Master | 11 body servos, LEDs, logic analyzer |

The diagrams are generated from the pin mapping in `include/config.h`:
`python3 sim/make_diagrams.py` (re-run after changing pins; do not edit the JSON by hand).

## Interactive (VS Code)

1. Build: `pio run`
2. Command palette → **Wokwi: Select Config File** → `sim/master/wokwi.toml` (or slave/body)
3. **Wokwi: Start Simulator**. The serial monitor sends lines terminated with CR, as the firmware expects.
4. EEPROM starts blank: the first boot does the factory reset, reboots and comes up as Dome Master.
   Type `#MD01` (slave) or `#MD02` (body) to switch the role.

## Automated scenarios (wokwi-cli)

```sh
pio run
export WOKWI_CLI_TOKEN=...          # https://wokwi.com/dashboard/ci
sim/run_scenarios.sh                # all roles, or: sim/run_scenarios.sh slave
```

Scenarios live in `<role>/scenarios/*.yaml`. They assume the default `R2D2` build (product name in
the boot message) and blank EEPROM at simulation start. Serial logs and VCD captures go to `sim/out/`.

## What is tested where

- `test/` (native, `pio test -e native`): logic, parsing, EEPROM map, sequences, fuzzing with
  AddressSanitizer — fast, no hardware, no token.
- `sim/` (Wokwi): the real AVR binary — boot, role switch, pin level checks and crash regressions on
  the actual 2 KB RAM / 32 KB flash target.
