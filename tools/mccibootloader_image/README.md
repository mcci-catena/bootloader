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
- [Typical Verbose Output](#typical-verbose-output)
- [Signing the bootloader](#signing-the-bootloader)
- [Generating a key pair](#generating-a-key-pair)
- [Using private keys in your build](#using-private-keys-in-your-build)
- [Build instructions](#build-instructions)
- [Meta](#meta)
	- [Copyright and License](#copyright-and-license)
	- [Support Open Source Hardware and Software](#support-open-source-hardware-and-software)
	- [Trademarks](#trademarks)

<!-- /TOC -->
<!-- markdownlint-restore -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Features

- Written in C++; only uses the facilities in the bootloader distribution and the C++ standard libraries.
- Operates on binary or linked ELF files.
- Computes and inserts the hash used for image verification
- Prepares a properly signed image
- Accepts the ed25519 keys in the form of OpenSSH `.pem` files.
- Builds with make and C++

## Synopsis

```bash
mccibootloader_image [OPTION]... INPUTFILE [OPTION]... [OUTPUTFILE] [OPTION]...
```

## Description

This program computes hashes and signs binary images for use with the MCCI bootloader. Conforming Cortex M-series images contain metadata in a special structure of type `McciBootloader_AppInfo_t`, located at byte offsets 0xC0 though 0xFF, called the `AppInfo` object.

It operates by reading an input image, modifying it in memory, and then writing the image to a new file. Optionally, it will update the input image in place.

If the input image is an ELF file, the output will also be an ELF file. Otherwise input and output are binary files.

The following options are defined. Note that options can be mixed with the input and output file specifications in any order.

<dl>
<dt><code>--dry-run</code></dt>
<dd>Go through all the motions, but don't touch the output file (or patch the input file if <code>-p</code> specified).</dd>

<dt><code>-t</code>, <code>--add-time</code></dt>
<dd>Change the time in the <code>AppInfo</code> to the current time. The <code>-nt</code> or <code>--no-add-time</code> options tell <code>mccibootloader_image</code> not to set the time. The default is <code>-t</code>.</dd>
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

## Typical Verbose Output

When run with the verbose flag, `mccibootloader_image` outputs useful information about the image and the signatures.

```console
Program settings:
     --verbose: true
        --hash: true
        --sign: true
    --add-time: true
     --dry-run: false
--force-binary: false
       --patch: false
     --keyfile: C:/mcci/projects/lora/bootloader/tools/mccibootloader_image/test/mcci-test.pem
     --comment: <<none>>

input:          build/arm-none-eabi/release/McciBootloader_46xx
output:         build/arm-none-eabi/release/McciBootloader_46xx.elf

Treating build/arm-none-eabi/release/McciBootloader_46xx as ELF file
ELF: section 0: vaddr(8000000) paddr(8000000) size(2920) vend(8002920) offset(10000) fsize(2920) flags(5)
ELF: section 1: vaddr(20003000) paddr(8002920) size(50) vend(20003050) offset(13000) fsize(50) flags(7)
ELF: section 2: vaddr(8002970) paddr(8002970) size(a0) vend(8002a10) offset(22970) fsize(a0) flags(6)
ELF: section 3: vaddr(20003050) paddr(20003050) size(10e4) vend(20004134) offset(23050) fsize(0) flags(6)
Elf: skipping non-contiguous writable section 3
Keyfile comment: MCCI test code-signing key

AppInfo from input:
          magic:         3050414d
           size:               40
  targetAddress:          8000000
      imageSize:             2970
       authSize:               a0
 posixTimestamp:                0
        comment:
        version:            0.0.0

Posix time: 60834008
AppInfo after update:
          magic:         3050414d
           size:               40
  targetAddress:          8000000
      imageSize:             2970
       authSize:               a0
 posixTimestamp:         60834008
        comment:
        version:            0.0.0

App page 0:
00 50 00 20 79 01 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7f 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 35 1b 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
7d 21 00 08 7d 21 00 08 7d 21 00 08 7d 21 00 08
4d 41 50 30 40 00 00 00 00 00 00 08 70 29 00 00
a0 00 00 00 00 00 00 00 08 40 83 60 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

Public key:
34 e7 50 ed d5 c5 b9 bb 43 58 40 6c 60 f8 13 64
70 12 81 a1 7d 31 cb b6 e7 3e 0e 5b c0 69 41 93

Appended Hash @ 0x2990:
00 df 83 07 f9 f7 d2 ac bb 30 78 91 71 4b 74 d5
f6 8d c1 a7 5f c1 09 fb e9 ef 64 24 80 1d 32 9e
c2 0c d9 67 54 e3 84 ee fc 3b 9e 37 26 24 62 82
5e 0a 4f 65 db 2d a3 9f 57 3e 99 33 28 1c 53 df

signature:
2b ef e1 53 da 75 26 da 92 e8 fd 44 c5 1e 80 b7
24 14 9b 63 46 19 55 fe 7d 3c 82 65 62 22 b9 32
c2 b0 51 47 a6 0f 11 28 4b 4d ef 0f 29 10 26 24
27 6f 66 5a 0d 89 14 17 4e e2 13 d2 f6 60 1f 01

output file successfully written: build/arm-none-eabi/release/McciBootloader_46xx.elf
```

## Signing the bootloader

The bootloader checks its own hash, but it does not check its own signature on every boot. However, it gets its public key from the signature block (and the public key is covered by the hash). So the bootloader image should be hashed and signed either with the user-supplied private key or with the test signing key. Apps to be loaded into flash by the bootloader therefore should be signed either by the test key or by the user-supplied private key that was used to sign the target bootloader.

## Generating a key pair

Use `ssh-keygen` to generate a key as follows:

```bash
ssh-keygen -t ed25519 -C "key comment" -f outputfile.pem
```

We recommend entering a non-empty pass phrase to better secure the private key while it's not being used.

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

## Using private keys in your build

There are many ways to do this. At present, you must momentarily have your private key in the clear during a build, because `mccibootloader_image` doesn't know how to decrypt private keys. One way to do this to minimize risk on POSIX-like systems is:

1. Put the password-encrypted private key in a directory with permissions 600.
2. Set up your build script to remove any unencrypted private keys
3. Have your build script prompt you for the password and decrypt the private key when needed.

The removal step should be done with a `trap` command:

```bash
# function to remove private key file if it exists.
function _cleanup {
    [[ -f "$PRIVATE_KEY_UNLOCKED_FILE" ]] && shred -u "$PRIVATE_KEY_UNLOCKED_FILE"
}

trap '_cleanup' EXIT
```

The prompt/unlock steps might look like this

```bash
# set up private key
if [[ $OPTTESTSIGN -eq 0 ]]; then
    # rename keydir and keyfile as needed for your use.

    # set up pointer to locked (encrypted) private key file.
    PRIVATE_KEY_LOCKED_FILE="$(realpath keydir/keyfile.pem)"

    # set up pointer to unlocked private key file, by changing '.pem' to '.tmp.pem'
    # at the end of the file name.
    PRIVATE_KEY_UNLOCKED_FILE="${PRIVATE_KEY_LOCKED_FILE/%.pem/.tmp.pem}"

    # make sure permissions on the directory are safe.
    chmod 700 "$(dirname "$PRIVATE_KEY_LOCKED_FILE")"

    echo "Unlocking private key:"
    # first remove any old version
    rm -f "${PRIVATE_KEY_UNLOCKED_FILE}"
    # make a new empty file with the right permissions
    touch -m 600 "$PRIVATE_KEY_LOCKED_FILE"
    # copy the locked file into the unlocked file, preserving output permissions
    cat "$PRIVATE_KEY_LOCKED_FILE" >"$PRIVATE_KEY_UNLOCKED_FILE"
    # use ssh-keygen to decrypt the file. This will prompt for a password!
    ssh-keygen -p -N '' -f "$PRIVATE_KEY_UNLOCKED_FILE"
    # extreme caution: make sure permissions are still right.
    chmod 600 "$PRIVATE_KEY_UNLOCKED_FILE"
  
    # For Arduino builds, set up a platform.local.test that will refer to the unlocked file
    # so that the arduino builder will use the private key. Do what makes sense for
    # you if using PlatformIO or other build systems.
    printf "%s\n" \
      mccibootloader_keys.path="$(dirname $PRIVATE_KEY_UNLOCKED_FILE)" \
      mccibootloader_keys.test="$(basename $PRIVATE_KEY_UNLOCKED_FILE)" \
        > "$LOCAL_BSP_CORE"/platform.local.txt

    # we use a different variable for the key file in the rest of the script,
    # so that cleanup won't remove the test signature file.
    KEYFILE="${PRIVATE_KEY_UNLOCKED_FILE}"
else
    echo "** using test key **"

    # for MCCI's Arduino BSP, we don't want platform.local.txt; but you
    # might need to edit it rather than removing it.
    rm -rf "$LOCAL_BSP_CORE"/platform.local.txt

    # tell the rest of the script to use the test signing key
    KEYFILE="$(realpath extra/bootloader/tools/mccibootloader_image/test/mcci-test.pem)"
fi
```

## Build instructions

On Windows, we use git bash and use [scoop](https://scoop.sh) to install GNU make and clang.

Make sure to install the pre-requisites below, before make a build.
- scoop install make
- scoop install llvm

(At time of writing, there was no working gcc available via scoop, although that may have been fixed.) Use `make -j3 -O` to build.

On macOS, we have used either GCC 10 (installed via homebrew) or clang (installed via `xcode-select --install`).

- With GCC, build using `make MCCI_CC=gcc-10`.
- With clang, build using `make`.

On Ubuntu, we used GCC 9 (installed via normal `apt-get` mechanisms). Build using `make`.

Although the code is believed to be 32-bit clean (and certainly should work properly), we've not compiled for any 32-bit targets.

To cross-compile, use the typical mechanism: `CROSS_COMPILE=prefix- make`. This has not been tested, however.

## Meta

### Copyright and License

Except as explicitly noted, content created by MCCI in this repository tree is copyright (C) 2021, MCCI Corporation.

`mccibooloader_image` and wrappers are released under the attached [license](./LICENSE.md). Commercial licenses and commercial support are available from MCCI Corporation.

The TweetNaCl and NaCl code is all public domain (including MCCI contributions in those directories).

### Support Open Source Hardware and Software

MCCI invests time and resources providing this open source code, please support MCCI and open-source hardware by purchasing products from MCCI and other open-source hardware/software vendors!

For information about MCCI's products, please visit [store.mcci.com](https://store.mcci.com/).

### Trademarks

MCCI and MCCI Catena are registered trademarks of MCCI Corporation. All other marks are the property of their respective owners.
