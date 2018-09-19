#include <AESLib.h>
#include <CMACLib.h>


// 16 bytes key
uint8_t key[] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

// struct for holding the subkeys that are derived from our key
struct cmac_subkeys_t subkeys;

void setup() {
    Serial.begin(57600);

    // actual subkey generation. This is done in setup() because it'll be used during the whole lifespan of the key
    subkeys = cmac_generate_subkeys(key);
}

void loop(){
    // array meant to hold the generated MAC tag, 8 bytes (64 bits) one in this example
    uint8_t MACTag[8];

    // our data array containing 16 bytes
    uint8_t data[] = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96, 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A};

    // actual authentication tag generation, with the pointer to where to save the tag, the key to be used,
    // the subkeys previously generated and the pointer to the actual message data
    cmac_auth(MACTag, key, &subkeys, data);

    // prints the resulting mac tag
    Serial.println("MAC Tag:");
    for(int i = 0; i < 8; i++){
        Serial.print(MACTag[i], HEX);
        Serial.print(' ');
    }
    Serial.println();

    bool check;
    // function to check if the message is actually valid.
    check = cmac_verify(key, &subkeys, data, MACTag);

    Serial.print("Message is valid: ");
    Serial.println(check?"Yes":"No");
}