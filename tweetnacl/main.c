// a simple test to confirm that we can compile TweetNaCl and
// access the sign verification routines.
//
// To compile, we use the following:
//
// arm-none-eabi-gcc -c -mcpu=cortex-m0plus -mthumb -ffunction-sections -fdata-sections -std=gnu11 main.c tweetnacl.c
// arm-none-eabi-gcc -o main.elf main.o tweetnacl.o -Wl,--gc-sections -Wl,--cref -Wl,--check-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -nostdlib -lgcc
#include "tweetnacl.h"
#include <stdint.h>

uint8_t message[1000] = {};
uint8_t key[32] = { };
uint64_t mlen;

void McciBootloader_Main(int argc, char **argv)
        {
        crypto_sign_open(message, &mlen, message, sizeof(message)-64, key);
        }
