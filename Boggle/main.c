#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

// Function to initialize a new trie node
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        int i;
        newNode->isEndOfWord = false;
        for (i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Function to insert a word into the trie
void insertWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    int index;

    while (*word) {
        index = *word - 'a';  // Assuming uppercase letters only
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
        word++;
    }

    current->isEndOfWord = true;
}

// Function to search for a word in the trie
bool searchWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    int index;

    while (*word) {
        index = *word - 'a';  // Assuming uppercase letters only
        index = *word - 'a';  // Assuming uppercase letters only
        if (!current->children[index]) {
            return false;  // Word not found
        }
        current = current->children[index];
        word++;
    }

    return current && current->isEndOfWord;
}

// Function to free the memory used by the trie
void freeTrie(struct TrieNode* root) {
    if (!root) return;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(root->children[i]);
    }

    free(root);
}

int main() {
    struct TrieNode* root = createNode();

    char buffer[32];
    FILE *fin = fopen("bogglelist.txt", "r");
    while (fscanf(fin, "%s", buffer) == 1){
        // Inserting words into the trie
        insertWord(root, buffer);
    }

    printf("SEARCH FOR WORD; \n");

    // Freeing memory used by the trie
    freeTrie(root);

    return 0;
}
