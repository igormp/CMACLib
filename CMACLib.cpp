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
        in[i] = (in[i] << 1) | prev_carry; // Shifts value by 1 and adds the carry
        prev_carry = carry;
    }
}

// Xors 2 arrays byte per byte
static void cmac_xor(uint8_t *x, uint8_t *y, uint8_t len){
    for(int8_t i = 0; i < len; i++){
        x[i] ^= y[i];
    }
}

// Xors an array with a constant value
static void cmac_xor_const(uint8_t *x, const uint8_t value, uint8_t len){
    for(int8_t i = 0; i < len; i++){
        x[i] ^= value;
    }
}

struct cmac_subkeys_t cmac_generate_subkeys(uint8_t *key, uint8_t key_len){
    struct cmac_subkeys_t subkey;

    // Rb value according to section 5.3 of the NIST doc
    const uint8_t Rb = 135;

    // Does L = CIPHk(0b) 
    uint8_t L[key_len] = {0};
    aes128_enc_multiple(key, L, key_len);
    memcpy(subkey.sk1, L, key_len);

    if( (subkey.sk1[0] & 128) == 0 ){
        cmac_lshift(subkey.sk1, 16);
    }
    else{
        cmac_lshift(subkey.sk1, 16);
        cmac_xor_const(subkey.sk1, Rb, 16);
    }

    memcpy(subkey.sk2, subkey.sk1, key_len);
    if( (subkey.sk2[0] & 128) == 0 ){
        cmac_lshift(subkey.sk2, 16);
    }
    else{
        cmac_lshift(subkey.sk2, 16);
        cmac_xor_const(subkey.sk2, Rb, 16);        
    }

    return subkey;

}

void cmac_auth(uint8_t *T, uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *message,
                uint8_t mac_len, uint8_t msg_len, uint8_t key_len){
    
    // If msg_len = 0, let n = 1; else, let n = msg_len/blocksize (in bytes)
    uint8_t n = ((msg_len == 0)?1:(msg_len/16));
    uint8_t M[msg_len];

    memcpy(M, message, msg_len); // Creates a copy of our message in M

    // We assume that our message is composed entirely of complete blocks,
    // specially the last one, so we can XOR the most significant block of 
    // our message with K1.
    cmac_xor(M, subkeys->sk1, key_len);

    // Makes sure C is at least 1 block bigger than our message to avoid overflows
    uint8_t C[msg_len+BLOCK_SIZE] = {0};

    // CBC of a single block
    // TODO: allow multiple blocks
    cmac_xor(C, M, 16);
    aes128_enc_single(key, C);
    
    
    for(uint8_t i = 0; i < mac_len; i++){
        T[i] = C[i];
    }
    
}

bool cmac_verify(uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *rec_message,
                uint8_t *rec_mac, uint8_t mac_len,
                uint8_t msg_len, uint8_t key_len){

}