#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define DATA_SIZE 256  // Define DATA_SIZE as 256

// Block structure
typedef struct {
    int index;
    time_t timestamp;
    char data[DATA_SIZE];
    char prev_hash[65];
    char curr_hash[65];
} Block;

// Function to convert the hash to a hexadecimal string
void to_hex(unsigned char *hash, char *output) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';  // Null-terminate the string
}

// Function to calculate the SHA-256 hash of a block
void calc_hash(Block *block, char *output) {
    char input[512];  // Create a string for concatenating block data
    snprintf(input, sizeof(input), "%d%ld%s%s", block->index, block->timestamp, block->data, block->prev_hash);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, input, strlen(input));
    SHA256_Final(hash, &sha256Ctx);

    to_hex(hash, output);
}

// Function to initialize a block
void init_block(Block *block, int index, const char *data, const char *prev_hash) {
    block->index = index;
    block->timestamp = time(NULL);  // Set the current timestamp
    strncpy(block->data, data, DATA_SIZE - 1);  // Copy data into the block
    block->data[DATA_SIZE - 1] = '\0';  // Ensure null-termination
    strncpy(block->prev_hash, prev_hash, 65);  // Copy the previous hash
    block->prev_hash[64] = '\0';  // Ensure null-termination

    // Calculate and store the current hash of the block
    calc_hash(block, block->curr_hash);
}

// Function to verify the integrity of the blockchain
int verify_chain(Block *chain, int size) {
    for (int i = 1; i < size; i++) {
        // Verify that the previous hash of the current block matches the current hash of the previous block
        if (strcmp(chain[i].prev_hash, chain[i - 1].curr_hash) != 0) {
            return 0;  // Chain is broken
        }
    }
    return 1;  // Chain is intact
}

int main() {
    // Initialize the genesis hash
    const char *genesis_hash = "0000000000000000000000000000000000000000000000000000000000000000";

    // Create the blockchain array directly in the main function
    Block chain[3];

    // Initialize each block with the respective data and previous hash
    init_block(&chain[0], 0, "First block data", genesis_hash);
    init_block(&chain[1], 1, "Second block data", chain[0].curr_hash);
    init_block(&chain[2], 2, "Third block data", chain[1].curr_hash);

    // Print block details
    for (int i = 0; i < 3; i++) {
        printf("Block %d: Data = %s, prevHash = %s, currHash = %s\n", 
                chain[i].index, chain[i].data, chain[i].prev_hash, chain[i].curr_hash);
    }

    // Verify chain integrity
    if (verify_chain(chain, 3)) {
        printf("Chain integrity verified\n");
    } else {
        printf("Chain integrity broken\n");
    }

    // Tampering with block 1's hash
    printf("\nTampering with block 1's Hash\n");
    strcpy(chain[1].curr_hash, "1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef");

    // Re-verify chain integrity after tampering
    if (verify_chain(chain, 3)) {
        printf("Chain integrity verified\n");
    } else {
        printf("Chain broken at block 2!\n");
    }

    return 0;
} 