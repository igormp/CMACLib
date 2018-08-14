#include "CMACLib.h"
#include <stdint.h>


cmac_subkeys_t* cmac_generate_subkeys(uint8_t *key, uint8_t key_len = 16){
    cmac_subkeys_t subkey;
    uint8_t L[key_len] = {0};
    aes128_enc_multiple(key, L);
    if(L[0] & 128){
        // add shift for the whole key xor rb
    }
    else{
        // add shift for the whole key
    }

}

uint8_t* cmac_auth(cmac_subkeys_t *subkeys, uint8_t *message, uint8_t mac_len,
                uint8_t key_len = 16, uint8_t msg_len = 16){

}

bool cmac_verify(cmac_subkeys_t *subkeys, uint8_t *rec_message, 
                uint8_t rec_mac, uint8_t mac_len,
                uint8_t key_len = 16, uint8_t msg_len = 16){

}