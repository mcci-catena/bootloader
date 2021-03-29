# mccibootloader_image

Hash images and sign images for the MCCI bootloader.

- Written in C++; only uses the facilities in the bootloader distribution and the C++ standard libraries.
- Computes and inserts the hash used for image verification
- Prepares a proper
- Accepts the ed25519 keys in the form of OpenSSH `.pem` files.
- Builds with make and C++

## Synopsis

```bash
mccibootloader_image [OPTION]... INPUTFILE [OUTPUTFILE]
```

## Description

This program computes hashes and signs binary images for use with the MCCI bootloader. Conforming Cortex M-series images contain metadata in a special structure of type `McciBootloader_AppInfo_t`, located at byte offsets 0xC0 though 0xFF, called the `AppInfo` object.

It operates by reading an input image, modifying it in memory, and then writing the image to a new file. Optionally, it will update the input image in place.

The following options are defined.

<dl>
<dt><code>--dry-run</code></dt>
<dd>Go through all the motions, but don't touch the output file (or patch the input file if <code>-p</code> specified).</dd>

<dt><code>-g</code>, <code>--gps-time</code></dt>
<dd>Change the GPS time in the <code>AppInfo</code> to the current GPS time. The <code>-ng</code> or <code>--no-gps-time</code> options tell mccibootloader_image not to set the GPS time. The default is <code>-g</code>.</dd>
<dt><code>-h</code>, <code>--hash</code></dt>
<dd>Compute the application hash and place it in the output file.</dd>
<dt><code>-p</code>, <code>--patch</code></dt>
<dd>Update the input file in place.</dd>
<dt><code>-k <em>file</em></code>, <code>--keyfile <em>file</em></code></dt>
<dd>Read the signing key from <code><em>file</em></code>, which must be an OpenSSH ed25519 private key file, not password protected. The (insecure) keyfile <code>test/mcci-test.pem</code> is conventionally used for test purposes. </dd>
<dt><code>-s</code>, <code>--sign</code></dt>
<dd>Compute the hash (as with <code>-h</code>, and then sign. A key file must be provided.</dd>
<dt><code>-v</code>, <code>--verbose</code></dt>
<dd>Print a running commentary on what's being done.</dd>
<dt><code>--version</code></dt>
<dd>Print program version and exit sucessfully.</dd>
</dl>

## Operational Notes

The bootloader itself must be hashed, but it does not check its own signature. However, it gets its public key from the signature block. So the bootloader image should be hashed and signed either with the user-supplied private key or with the test signing key. Apps to be loaded into flash by the bootloader therefore should be signed either by the test key or by the user-supplied private key that was used to sign the target bootloader.

## Build instructions

On Windows, we use git bash and use [scoop](https://scoop.io) to install GNU make and clang. (At time of writing, there was no working gcc available via scoop, although that may have been fixed.) Use `make -j3 -O` to build.

On macOS, we have used either GCC 10 (installed via homebrew) or clang (installed via `xcode-select --install`).

- With GCC, build using `make MCCI_CC=gcc-10`.
- With clang, build using `make`.

On Ubuntu, we used GCC 9 (installed via normal `apt-get` mechanisms). Build using `make`.

Although the code is belived to be 32-bit clean (and certainly should work properly), we've not compiled for any 32-bit targets.

To cross-compile, use the typical mechanism: `CROSS_COMPILE=prefix- make`. This has not been tested, however.
