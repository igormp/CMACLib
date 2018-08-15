#include "CMACLib.h"
#include <stdint.h>

// Returns if the most significant bit is 1 or 0 in a byte
static inline bool cmac_msb(uint8_t x){
    return (x & 128)?1:0;
}

// Left shifts a whole array by 1 in place
static void cmac_lshift(uint8_t *in, uint8_t len) {
    uint8_t carry, prev_carry = 0;  
    for(int8_t i = (len-1); i >= 0 ; --i){
        carry = cmac_msb(in[i]);
        in[i] <<= 1;
        in[i] += prev_carry;
        prev_carry = carry;
    }
}

// Xors 2 arrays byte per byte
static void cmac_xor(uint8_t *x, uint8_t *y, uint8_t len){
    for(int8_t i = 0; i < len; i++){
        x[i] ^= y[i];
    }
}

cmac_subkeys_t* cmac_generate_subkeys(uint8_t *key, uint8_t key_len = 16){
    cmac_subkeys_t subkey;

    // Rb value according to section 5.3 of the NIST doc
    const uint8_t Rb = 135;

    // Does L = CIPHk(0b) 
    uint8_t L[key_len] = {0};
    aes128_enc_multiple(key, L, key_len);


    if( (L[0] & 128) == 0 ){
        cmac_lshift(L, 16);
        subkey.sk1 = L;
    }
    else{
        cmac_lshift(L, 16);
        L[len-1] ^= Rb;
        subkey.sk1 = L;
    }

    if( (subkey.sk1[0] & 128) == 0 ){
        cmac_lshift(subkey.sk1, 16);
        subkey.sk2 = subkey.sk1;
    }
    else{
        cmac_lshift(subkey.sk1, 16);
        subkey.sk1[len-1] ^= Rb;
        subkey.sk2 = subkey.sk1;
    }

    return subkey;

}

uint8_t* cmac_auth(cmac_subkeys_t *subkeys, uint8_t *message, uint8_t mac_len,
                uint8_t key_len = 16, uint8_t msg_len = 16){

}

bool cmac_verify(cmac_subkeys_t *subkeys, uint8_t *rec_message, 
                uint8_t rec_mac, uint8_t mac_len,
                uint8_t key_len = 16, uint8_t msg_len = 16){

}