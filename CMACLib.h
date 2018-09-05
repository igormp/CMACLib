#ifndef CMACLIB_H
#define CMACLIB_H

#include <stdint.h>
#include <string.h>
#include "AESLib.h"

// Cipher block size, in bytes
const uint8_t BLOCK_SIZE = 16;

struct cmac_subkeys_t{
    uint8_t sk1[BLOCK_SIZE];
    uint8_t sk2[BLOCK_SIZE];
};

// Generates subkeys. Takes in your cipher key and 
// optionally the key length in bytes, which defaults to 16 bytes.
struct cmac_subkeys_t cmac_generate_subkeys(uint8_t *key, uint8_t key_len = 16);

// Generates the actual MAC. Takes in the location to store the MAC tag,
// your previously generated subkeys, the message to authenticate, 
// and optionally both the MAC length (which defaults  to 8),
// key and message lengths in byteS (both of which defaults to 16 bytes).
void cmac_auth(uint8_t *T, uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *message,
                uint8_t mac_len = 8, uint8_t msg_len = 16, uint8_t key_len = 16);

// Verifies if a message is valid. Takes in your previously generated subkeys,
// the received message, and optionally both the received MAC and its length 
// (which defaults to 8), the key and message lengths in bytes (both of which 
// defaults to 16 bytes).
bool cmac_verify(uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *rec_message,
                uint8_t *rec_mac, uint8_t mac_len = 8,
                uint8_t msg_len = 16, uint8_t key_len = 16);

#endif