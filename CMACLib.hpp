#ifndef CMACLIB_H
#define CMACLIB_H

#include <stdint.h>
#include "AESLib.h"


struct cmac_subkeys_t{
    uint8_t *sk1;
    uint8_t *sk2;
};

// Cipher block size, in bytes
const uint8_t BLOCK_SIZE = 16;

// Generates subkeys. Takes in your cipher key and 
// optionally the key length in bytes, which defaults to 16 bytes.
cmac_subkeys_t* cmac_generate_subkeys(uint8_t *key, uint8_t key_len = 16);

// Generates the actual MAC. Takes in your previously generated subkeys, 
// the message to authenticate, and optionally both the MAC length (which defaults 
//  to 8), key and message lengths in byteS (both of which defaults to 16 bytes).
uint8_t* cmac_auth(uint8_t *key, cmac_subkeys_t *subkeys, uint8_t *message,
                uint8_t mac_len = 8, uint8_t msg_len = 16, uint8_t key_len = 16);

// Verifies if a message is valid. Takes in your previously generated subkeys,
// the received message, and optionally both the received MAC and its length 
// (which defaults to 8), the key and message lengths in bytes (both of which 
// defaults to 16 bytes).
bool cmac_verify(uint8_t *key, cmac_subkeys_t *subkeys, uint8_t *rec_message,
                uint8_t *rec_mac, uint8_t mac_len = 8,
                uint8_t msg_len = 16, uint8_t key_len = 16);


#endif