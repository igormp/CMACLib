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

struct cmac_subkeys_t cmac_generate_subkeys(uint8_t *key, uint8_t key_len){
    struct cmac_subkeys_t subkey;

    // Rb value according to section 5.3 of the NIST doc
    const uint8_t Rb = 135;

    // Does L = CIPHk(0b) 
    uint8_t L[key_len] = {0};
    aes128_enc_multiple(key, L, key_len);
    memcpy(subkey.sk1, L, key_len);

    if( (subkey.sk1[0] & 128) == 0 ){
        cmac_lshift(subkey.sk1, BLOCK_SIZE);
    }
    else{
        cmac_lshift(subkey.sk1, BLOCK_SIZE);
        subkey.sk1[key_len-1] ^= Rb;
    }

    memcpy(subkey.sk2, subkey.sk1, key_len);
    if( (subkey.sk2[0] & 128) == 0 ){
        cmac_lshift(subkey.sk2, BLOCK_SIZE);
    }
    else{
        cmac_lshift(subkey.sk2, BLOCK_SIZE);
        subkey.sk2[key_len-1] ^= Rb;
    }

    return subkey;

}

void cmac_auth(uint8_t *T, uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *message,
                uint8_t mac_len, uint8_t msg_len, uint8_t key_len){
    
    // If msg_len = 0, let n = 1; else, let n = ceil(msg_len/blocksize) (in bytes)
    uint8_t n = ((msg_len == 0)?1:(1 + ((msg_len - 1) / BLOCK_SIZE)));
    uint8_t remainder = ((msg_len%BLOCK_SIZE == 0)?0:(BLOCK_SIZE-(msg_len%BLOCK_SIZE)));
    
    uint8_t M[(n*BLOCK_SIZE)] = {0};

    if(msg_len != 0){
        memcpy(M, message, msg_len); // Creates a copy of our message in M
    }

    if(remainder != 0){
        M[msg_len] = 128;
    }
    if(msg_len == 0){
        M[0] = 128;
    }

    if(remainder == 0 && msg_len != 0){
        cmac_xor((M+((n-1)*BLOCK_SIZE)), subkeys->sk1, key_len);
    } else {
        cmac_xor((M+((n-1)*BLOCK_SIZE)), subkeys->sk2, key_len);
    }

    uint8_t C[BLOCK_SIZE] = {0};
    
    for(uint8_t i = 0; i < n; i++){
        cmac_xor(C, (M+(i*BLOCK_SIZE)), BLOCK_SIZE);
        aes128_enc_single(key, C);
    }
    
    for(uint8_t i = 0; i < mac_len; i++){
        T[i] = C[i];
    }
    
}

bool cmac_verify(uint8_t *key, struct cmac_subkeys_t *subkeys, uint8_t *rec_message,
                uint8_t *rec_mac, uint8_t mac_len,
                uint8_t msg_len, uint8_t key_len){
                    
    uint8_t Ttemp[mac_len];

    cmac_auth(Ttemp, key, subkeys, rec_message, mac_len);

    for(uint8_t i = 0; i < mac_len; i++){
        if(Ttemp[i] != rec_mac[i]){
            return false;
        }
    }

    return true;

}