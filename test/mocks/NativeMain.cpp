// Fallback entry point for the native environments, so that "Build" (pio run -e native*) links
// successfully, e.g. when clicked in the VS Code PlatformIO sidebar. During "pio test" each test
// suite provides its own main() and this file contributes nothing.
#if !defined(PIO_UNIT_TESTING) && !defined(UNIT_TEST)
#include <cstdio>

int main()
{
    std::puts("BetterDuino native environment: this build only contains the firmware sources and test mocks.\n"
              "Run the unit tests with: pio test -e native  (or native_chopper / native_bt1)\n"
              "The firmware itself is built with the ATmega328P environment: pio run");
    return 0;
}
#endif
