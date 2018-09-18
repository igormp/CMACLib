# CMACLib

CMAC Auth library, still a work in progress and not audited at all. Currently tested and working on Arduino.

Depends on [AESLib](https://github.com/igormp/AESLib)

This library is meant to provide a way to authenticate your data by generating an auth tag using a block cipher instead of a hashing function, following NIST's CMAC (also known as OMAC) specification.

Currently it only works on AVR microcontrollers due to the hard requirement on AESLib, which is written in AVR asm.

## Usage

Clone this repository into your Arduino libraries folder, and include this library into your code.

Change the `BLOCK_SIZE` variable to indicate the lenght of your block size in bytes. Its value is 16 by default (since we're using a 128 bits chiper).

Create an array containg your AES key (for example, for a 128 bit key, an array containing 16 unssigned bytes would do).

Derive subkeys from your actual key using the provided `cmac_generate_subkeys` function. E.g.: 

```
struct cmac_subkeys_t subkeys = cmac_generate_subkeys(key);
```


You can see the `CMACLib.h` file for further descriptions on the available functions and parameters.

## Roadmap

- [X] Pass on NIST's 128bit examples
- [ ] Pass on NIST's 192bit examples
- [ ] Pass on NIST's 256bit examples
- [ ] Replace AESLib for a more generic, architecture-agnostic version
- [ ] Allow for generic usage of any block chiper function
- [ ] Add code examples
- [ ] Finish this readme

## Resources

[NIST SP 800-38B](http://csrc.nist.gov/publications/nistpubs/800-38B/SP_800-38B.pdf) - The CMAC Mode for Authentication

[NIST test vectors](https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/AES_CMAC.pdf)