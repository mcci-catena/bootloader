# mccibootloader_image

Hash images for the MCCI bootloader.

- Written in C++; only uses the facilities in the bootloader distribution and the C++ 2011 standard libraries.

(Temporary: to build on Windows with Clang)

```bash
clang -I i -I ../../pkgsrc/mcci_tweetnacl/src -I ../../pkgsrc/mcci_arduino_development_kit_adk/src -D _CRT_SECURE_NO_WARNINGS src/main.cpp  src/keyfile_ed25519.cpp -o mccibootloader_image.exe ../../pkgsrc/mcci_tweetnacl/src/lib/mcci_tweetnacl_sign.c ../../pkgsrc/mcci_tweetnacl/src/lib/mcci_tweetnacl.c -ffunction-sections ../../pkgsrc/mcci_tweetnacl/src/hal/mcci_tweetnacl_hal_randombytes.c src/salt_test.cpp
```
