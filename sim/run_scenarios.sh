#!/usr/bin/env bash
# Runs all Wokwi automation scenarios against the built AVR firmware.
#
#   pio run                                  # build .pio/build/ATmega328P/firmware.hex/.elf
#   export WOKWI_CLI_TOKEN=...               # https://wokwi.com/dashboard/ci
#   sim/run_scenarios.sh [master|slave|body] # default: all roles
#
# Serial logs and logic analyzer captures (VCD) end up in sim/out/.
set -euo pipefail

SIM="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(dirname "$SIM")"
OUT="$SIM/out"

: "${WOKWI_CLI_TOKEN:?WOKWI_CLI_TOKEN not set (create one at https://wokwi.com/dashboard/ci)}"
command -v wokwi-cli >/dev/null || { echo "wokwi-cli not found (https://docs.wokwi.com/wokwi-ci/getting-started)"; exit 1; }
[ -f "$ROOT/.pio/build/ATmega328P/firmware.hex" ] || { echo "Firmware not built. Run: pio run"; exit 1; }

ROLES=("${@:-master slave body}")
mkdir -p "$OUT"
failed=0

for role in ${ROLES[*]}; do
    for scenario in "$SIM/$role"/scenarios/*.yaml; do
        name="$role-$(basename "$scenario" .yaml)"
        printf '%-45s ' "$name"
        if wokwi-cli "$SIM/$role" --quiet \
                --scenario "scenarios/$(basename "$scenario")" \
                --timeout 120000 \
                --serial-log-file "$OUT/$name.log" \
                --vcd-file "$OUT/$name.vcd" >"$OUT/$name.cli.txt" 2>&1; then
            echo "PASS"
        else
            echo "FAIL (see sim/out/$name.*)"
            failed=1
        fi
    done
done

exit $failed
