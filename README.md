# CMACLib

CMAC Auth library, still a work in progress and not audited at all. Currently tested and working on Arduino.

Depends on [AESLib](https://github.com/igormp/AESLib)

This library is meant to provide a way to authenticate your data by generating an auth tag using a block cipher instead of a hashing function, following NIST's CMAC (also known as OMAC) specification.

Currently it only works on AVR microcontrollers due to the hard requirement on AESLib, which is written in AVR asm.

## Usage

Clone this repository into your Arduino libraries folder, and include this library into your code.

## ☑ Roadmap

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