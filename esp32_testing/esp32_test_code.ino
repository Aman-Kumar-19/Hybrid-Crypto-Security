#include <Arduino.h>
#include <WiFi.h>              // Include Wi-Fi library
#include <ThingSpeak.h>         // Include ThingSpeak library
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <algorithm>

// Wi-Fi and ThingSpeak credentials
const char *ssid = "pkamble_EXT";   // Your Wi-Fi SSID
const char *password = "OmJ5cPPq";  // Your Wi-Fi password
unsigned long channelID = 2958566;  // ThingSpeak channel ID
const char *writeAPIKey = "BJ5C06TJ9ED86NEV";  // ThingSpeak Write API Key

WiFiClient client;

// DES S-Box Generation
std::vector<int> generate_des_sbox() {
    std::vector<int> des_sbox(256);
    for (int i = 0; i < 256; ++i) {
        des_sbox[i] = i ^ 0xBA;
    }
    return des_sbox;
}

std::vector<int> des_sbox = generate_des_sbox();
std::map<int, int> inverse_des_sbox;

void generate_inverse_des_sbox() {
    for (int i = 0; i < 256; ++i) {
        inverse_des_sbox[des_sbox[i]] = i;
    }
}

// DES S-Box Substitution
int des_sbox_substitution(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    return (des_sbox[byte1] << 8) | des_sbox[byte2];
}

int inverse_des_sbox_substitution(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    return (inverse_des_sbox[byte1] << 8) | inverse_des_sbox[byte2];
}

// DES Permutation
int des_permutation(int value) {
    int permuted = 0;
    std::vector<int> permutation_table = {15, 6, 11, 3, 8, 0, 12, 4, 7, 14, 1, 10, 2, 9, 13, 5};
    for (size_t i = 0; i < permutation_table.size(); ++i) {
        if (value & (1 << permutation_table[i])) {
            permuted |= (1 << i);
        }
    }
    return permuted;
}

int inverse_des_permutation(int value) {
    int inverse_permuted = 0;
    std::vector<int> permutation_table = {15, 6, 11, 3, 8, 0, 12, 4, 7, 14, 1, 10, 2, 9, 13, 5};
    for (size_t i = 0; i < permutation_table.size(); ++i) {
        if (value & (1 << i)) {
            inverse_permuted |= (1 << permutation_table[i]);
        }
    }
    return inverse_permuted;
}

int des_key_mixing(int value, int round_key) {
    return value ^ round_key;
}

// AES Operations
std::vector<int> aes_sbox(256);
std::map<int, int> inv_aes_sbox;

void generate_aes_sbox() {
    for (int i = 0; i < 256; ++i) {
        aes_sbox[i] = i ^ 0xA5;
        inv_aes_sbox[aes_sbox[i]] = i;
    }
}

uint16_t aes_substitute(uint16_t value) {
    return (aes_sbox[(value >> 8) & 0xFF] << 8) | aes_sbox[value & 0xFF];
}

uint16_t inverse_aes_substitute(uint16_t value) {
    return (inv_aes_sbox[(value >> 8) & 0xFF] << 8) | inv_aes_sbox[value & 0xFF];
}

int aes_shift_rows(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    return (byte2 << 8) | byte1;
}

int inverse_aes_shift_rows(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    return (byte1 << 8) | byte2;
}

int gf_mult(int a, int b) {
    int p = 0;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) p ^= a;
        bool hi_bit_set = a & 0x80;
        a <<= 1;
        if (hi_bit_set) a ^= 0x1B;
        b >>= 1;
    }
    return p & 0xFF;
}

int aes_mix_columns(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    int mixed1 = gf_mult(byte1, 2) ^ gf_mult(byte2, 3);
    int mixed2 = gf_mult(byte2, 2) ^ gf_mult(byte1, 3);
    return (mixed1 << 8) | mixed2;
}

int inverse_aes_mix_columns(int value) {
    int byte1 = (value >> 8) & 0xFF;
    int byte2 = value & 0xFF;
    int inv_mixed1 = gf_mult(byte1, 0x0E) ^ gf_mult(byte2, 0x0B) ^ gf_mult(byte1, 0x0D) ^ gf_mult(byte2, 0x09);
    int inv_mixed2 = gf_mult(byte2, 0x0E) ^ gf_mult(byte1, 0x0B) ^ gf_mult(byte2, 0x0D) ^ gf_mult(byte1, 0x09);
    return ((inv_mixed1 & 0xFF) << 8) | (inv_mixed2 & 0xFF);
}

// Generate Round Keys
std::vector<uint16_t> generate_round_keys(uint16_t base_key, int num_rounds = 12) {
    std::vector<uint16_t> keys;
    keys.push_back(base_key);

    for (int i = 1; i < num_rounds; ++i) {
        uint16_t prev_key = keys[i - 1];

        // Introduce non-linearity using AES S-Box
        uint16_t high_byte = aes_substitute((prev_key >> 8) & 0xFF);
        uint16_t low_byte = aes_substitute(prev_key & 0xFF);

        // Rotate bits and XOR with a constant
        uint16_t new_key = ((low_byte << 8) | high_byte) ^ (i * 0x9F37);
        keys.push_back(new_key & 0xFFFF);
    }
    return keys;
}

// RSA Key Generation and Operations
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        uint64_t q = a / m;
        uint64_t temp = m;
        m = a % m;
        a = temp;
        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }
    return (x1 + m0) % m0;
}

uint32_t aes_des_encrypt(uint32_t data, std::vector<uint16_t>& round_keys) {
    uint16_t left = (data >> 16) & 0xFFFF;
    uint16_t right = data & 0xFFFF;
    for (int round = 0; round < 12; round++) {
        left = aes_substitute(left);
        left = aes_shift_rows(left);
        left = aes_mix_columns(left);
        left ^= round_keys[round];
        right = des_sbox_substitution(right);
        right = des_permutation(right);
        right = des_key_mixing(right, round_keys[round]);
        std::swap(left, right);
    }
    return (left << 16) | right;
}

uint32_t aes_des_decrypt(uint32_t data, std::vector<uint16_t>& round_keys) {
    uint16_t left = (data >> 16) & 0xFFFF;
    uint16_t right = data & 0xFFFF;
    for (int round = 11; round >= 0; round--) {
        std::swap(left, right);
        right = des_key_mixing(right, round_keys[round]);
        right = inverse_des_permutation(right);
        right = inverse_des_sbox_substitution(right);
        left ^= round_keys[round];
        left = inverse_aes_mix_columns(left);
        left = inverse_aes_shift_rows(left);
        left = inverse_aes_substitute(left);
    }
    return (left << 16) | right;
}

std::tuple<uint64_t, uint64_t, uint64_t> generate_rsa_keys() {
    uint64_t p = 1048573, q = 999331;
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    uint64_t e = 65537;
    uint64_t d = mod_inverse(e, phi);
    return {n, e, d};
}

uint64_t rsa_encrypt(uint64_t data, uint64_t e, uint64_t n) {
    data = data % n;  // Ensure data is smaller than n
    uint64_t result = 1;
    while (e) {
        if (e & 1) result = (result * data) % n;
        data = (data * data) % n;
        e >>= 1;
    }
    return result;
}

uint64_t rsa_decrypt(uint64_t data, uint64_t d, uint64_t n) {
    data = data % n;  // Prevent incorrect decryption
    uint64_t result = 1;
    while (d) {
        if (d & 1) result = (result * data) % n;
        data = (data * data) % n;
        d >>= 1;
    }
    return result;
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);

    // Generate S-Boxes
    generate_inverse_des_sbox();
    generate_aes_sbox();

    // RSA Key Pair Generation
    auto [n, e, d] = generate_rsa_keys();
    Serial.print("Modulus (n): ");
    Serial.println(n, HEX);

    // Generate AES-DES Round Keys
    uint16_t base_key = 0x9F37;  // Example base key
    std::vector<uint16_t> round_keys = generate_round_keys(base_key, 12);

    // Example Data
    uint32_t plaintext = 0x1268;
    Serial.print("Original Data: ");
    Serial.println(plaintext, HEX);

    // AES-DES Encryption
    uint32_t encrypted = aes_des_encrypt(plaintext, round_keys);
    Serial.print("AES-DES Encrypted Data: ");
    Serial.println(encrypted, HEX);

    // RSA Encryption
    uint64_t rsa_encrypted = rsa_encrypt(encrypted, e, n);
    Serial.print("RSA Encrypted Data: ");
    Serial.println(rsa_encrypted, HEX);

    // RSA Decryption
    uint64_t rsa_decrypted = rsa_decrypt(rsa_encrypted, d, n);
    Serial.print("RSA Decrypted Data: ");
    Serial.println(rsa_decrypted, HEX);

    // AES-DES Decryption
    uint32_t decrypted = aes_des_decrypt(encrypted, round_keys);
    Serial.print("Final Decrypted Data: ");
    Serial.println(decrypted, HEX);

    // Validate correctness
    assert(decrypted == plaintext);
    Serial.println("Decryption successful! ✅");
        Serial.println("\n=== Bit-length Encryption/Decryption Timing Test ===");

    for (int bitLength = 8; bitLength <= 128; bitLength += 8) {
        int totalChunks = ceil(bitLength / 32.0);
        std::vector<uint32_t> inputChunks;

        // Generate random input data split into 32-bit chunks
        for (int i = 0; i < totalChunks; ++i) {
            inputChunks.push_back((uint32_t)random(0xFFFFFFFF));
        }

        // Measure encryption time
        unsigned long encStart = millis();
        std::vector<uint32_t> encryptedChunks;
        for (uint32_t chunk : inputChunks) {
            encryptedChunks.push_back(aes_des_encrypt(chunk, round_keys));
        }
        unsigned long encEnd = millis();
        unsigned long encTime = encEnd - encStart;

        // Measure decryption time
        unsigned long decStart = millis();
        std::vector<uint32_t> decryptedChunks;
        for (uint32_t chunk : encryptedChunks) {
            decryptedChunks.push_back(aes_des_decrypt(chunk, round_keys));
        }
        unsigned long decEnd = millis();
        unsigned long decTime = decEnd - decStart;

        // Validate decrypted output
        bool valid = true;
        for (int i = 0; i < totalChunks; ++i) {
            if (inputChunks[i] != decryptedChunks[i]) {
                valid = false;
                break;
            }
        }

        // Prepare encrypted data as a string
        String encryptedStr = "";
        for (uint32_t chunk : encryptedChunks) {
            encryptedStr += String(chunk, HEX);
            encryptedStr += " ";
        }

        // Send to ThingSpeak and measure transmission time
        unsigned long sendStart = millis();
        ThingSpeak.setField(1, bitLength);
        ThingSpeak.setField(2, encryptedStr);
        int result = ThingSpeak.writeFields(channelID, writeAPIKey);
        unsigned long sendEnd = millis();
        unsigned long sendTime = sendEnd - sendStart;

        // Output results to Serial
        Serial.println("----------------------------------------");
        Serial.print("Bit Length: ");
        Serial.println(bitLength);
        Serial.print("Chunks: ");
        Serial.println(totalChunks);
        Serial.print("Encryption Time (ms): ");
        Serial.println(encTime);
        Serial.print("Decryption Time (ms): ");
        Serial.println(decTime);
        Serial.print("Decryption Valid: ");
        Serial.println(valid ? "YES ✅" : "NO ❌");
        Serial.print("Transmission Time (ms): ");
        Serial.println(sendTime);
        Serial.print("ThingSpeak Upload: ");
        Serial.println(result == 200 ? "Success ✅" : "Fail ❌");

        delay(15000);  // wait before next message
    }

}

void loop() {
    // Nothing to do in the loop
}