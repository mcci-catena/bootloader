# mccibootloader_image

Hash images and sign images for the MCCI bootloader.

**Contents:**
<!--
  This TOC uses the VS Code markdown TOC extension AlanWalk.markdown-toc.
  We strongly recommend updating using VS Code, the markdown-toc extension and the
  bierner.markdown-preview-github-styles extension. Note that if you are using
  VS Code 1.29 and Markdown TOC 1.5.6, https://github.com/AlanWalk/markdown-toc/issues/65
  applies -- you must change your line-ending to some non-auto value in Settings>
  Text Editor>Files.  `\n` works for me.
-->
<!-- markdownlint-disable MD033 MD004 -->
<!-- markdownlint-capture -->
<!-- markdownlint-disable -->
<!-- TOC depthFrom:2 updateOnSave:true -->

- [Features](#features)
- [Synopsis](#synopsis)
- [Description](#description)
- [Operational Notes](#operational-notes)
- [Generating a key pair](#generating-a-key-pair)
- [Build instructions](#build-instructions)
- [Meta](#meta)
	- [License](#license)
	- [Support Open Source Hardware and Software](#support-open-source-hardware-and-software)
	- [Trademarks](#trademarks)

<!-- /TOC -->
<!-- markdownlint-restore -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Features

- Written in C++; only uses the facilities in the bootloader distribution and the C++ standard libraries.
- Computes and inserts the hash used for image verification
- Prepares a proper
- Accepts the ed25519 keys in the form of OpenSSH `.pem` files.
- Builds with make and C++

## Synopsis

```bash
mccibootloader_image [OPTION]... INPUTFILE [OPTION]... [OUTPUTFILE] [OPTION]...
```

## Description

This program computes hashes and signs binary images for use with the MCCI bootloader. Conforming Cortex M-series images contain metadata in a special structure of type `McciBootloader_AppInfo_t`, located at byte offsets 0xC0 though 0xFF, called the `AppInfo` object.

It operates by reading an input image, modifying it in memory, and then writing the image to a new file. Optionally, it will update the input image in place.

The following options are defined. Note that options can be mixed with the input and output file specifications in any order.

<dl>
<dt><code>--dry-run</code></dt>
<dd>Go through all the motions, but don't touch the output file (or patch the input file if <code>-p</code> specified).</dd>

<dt><code>-t</code>, <code>--add-time</code></dt>
<dd>Change the time in the <code>AppInfo</code> to the current time. The <code>-nt</code> or <code>--no-add-time</code> options tell mccibootloader_image not to set the time. The default is <code>-t</code>.</dd>
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
<dd>Print program version and exit successfully.</dd>
</dl>

## Operational Notes

The bootloader itself must be hashed, but it does not check its own signature. However, it gets its public key from the signature block. So the bootloader image should be hashed and signed either with the user-supplied private key or with the test signing key. Apps to be loaded into flash by the bootloader therefore should be signed either by the test key or by the user-supplied private key that was used to sign the target bootloader.

## Generating a key pair

Use `ssh-keygen` to generate a key as follows:

```bash
ssh-keygen -t ed25519 -C "key comment" -f outputfile.pem
```

For example:

```console
$ ssh-keygen -t ed25519 -C "key desciptive comment" -f outputfile.pem
Generating public/private ed25519 key pair.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in outputfile.pem
Your public key has been saved in outputfile.pem.pub
The key fingerprint is:
SHA256:Dyk+fVgizYB24hPRIPATBmxFDRh4gy8j2wxrurIbGTI key desciptive comment
The key's randomart image is:
+--[ED25519 256]--+
|==O+=o           |
|o*oo +.          |
|.oo.= o          |
|= .+ + + .       |
|EO  o o S .      |
|+=o  o + *       |
|=     o o o      |
|o.     . .       |
|=+               |
+----[SHA256]-----+
$
```

## Build instructions

On Windows, we use git bash and use [scoop](https://scoop.io) to install GNU make and clang. (At time of writing, there was no working gcc available via scoop, although that may have been fixed.) Use `make -j3 -O` to build.

On macOS, we have used either GCC 10 (installed via homebrew) or clang (installed via `xcode-select --install`).

- With GCC, build using `make MCCI_CC=gcc-10`.
- With clang, build using `make`.

On Ubuntu, we used GCC 9 (installed via normal `apt-get` mechanisms). Build using `make`.

Although the code is believed to be 32-bit clean (and certainly should work properly), we've not compiled for any 32-bit targets.

To cross-compile, use the typical mechanism: `CROSS_COMPILE=prefix- make`. This has not been tested, however.

## Meta

### License

`mccibooloader_image` and wrappers released under the [MIT license](../../LICENSE). Commercial licenses and commercial support are available from MCCI Corporation. The TweetNaCl and NaCl code is all public domain (including MCCI contributions in those directories). The collective work is MIT licensed.

### Support Open Source Hardware and Software

MCCI invests time and resources providing this open source code, please support MCCI and open-source hardware by purchasing products from MCCI, Adafruit and other open-source hardware/software vendors!

For information about MCCI's products, please visit [store.mcci.com](https://store.mcci.com/).

### Trademarks

MCCI and MCCI Catena are registered trademarks of MCCI Corporation. All other marks are the property of their respective owners.
