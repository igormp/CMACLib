# CMACLib

CMAC Auth library, still a work in progress and not audited at all. Currently tested and working on an Arduino.

Depends on [AESLib](https://github.com/igormp/AESLib).

This library is meant to provide a way to authenticate your data by generating an auth tag using a block cipher instead of a hashing function, following NIST's CMAC (also known as OMAC) specification.

Authentication is required because encryption by itself is not enough to verify that your data hasn't been tampered with. You can read more about it [here](https://en.wikipedia.org/wiki/Message_authentication_code).

Currently it only works on AVR microcontrollers due to the hard requirement on AESLib, which is written in AVR asm.

## Usage

Clone this repository into your Arduino libraries folder, and include this library into your code. Also remember to clone [this lib](https://github.com/igormp/AESLib), since it's used to generate the block cipher.

Change the `BLOCK_SIZE` variable to indicate the lenght of your block size in bytes. Its value is 16 by default (since we're using a 128 bits chiper).

Create an array containg your AES key (for example, for a 128 bit key, an array containing 16 unssigned bytes would do).

Derive subkeys from your actual key using the provided `cmac_generate_subkeys` function.

Generate your MAC tag with the `cmac_auth` function.

On the receiving end, you can use the `cmac_verify` function to see if its tag actually matches the one from the received message.

Check out the `CMACLib.h` file or the example file for further descriptions on the available functions and parameters.

## Roadmap

- [X] Pass on NIST's 128bit examples
- [ ] Pass on NIST's 192bit examples
- [ ] Pass on NIST's 256bit examples
- [ ] Replace AESLib with a more generic, architecture-agnostic version
- [ ] Allow for generic usage of any block chiper function

## Resources

[NIST SP 800-38B](https://csrc.nist.gov/publications/detail/sp/800-38b/final) - The CMAC Mode for Authentication

[NIST test vectors](https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/AES_CMAC.pdf)