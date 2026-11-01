// PROGMEM mock: on the host, flash data is ordinary memory.
#ifndef MOCK_AVR_PGMSPACE_H
#define MOCK_AVR_PGMSPACE_H

#include <cstdint>
#include <cstring>

#define PROGMEM
#define PSTR(s) (s)
#define pgm_read_byte(addr) (*(const uint8_t*)(addr))
#define pgm_read_word(addr) ((uint16_t)(((const uint8_t*)(addr))[0] | (((const uint8_t*)(addr))[1] << 8)))

#endif
