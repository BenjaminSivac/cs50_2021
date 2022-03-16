// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000; // Likely change it to something larger!

// Hash table
node *table[N]; // Global pointer array, used for keeping track of words in the dictionary.

int word_count = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // 
    int hash_number = hash(word); // get a hash number from each word
    node *pointer = table[hash_number]; // access the linked list by creating a pointer
    while (pointer != NULL) // Making sure it points to a node, and not the end of the chain. 
    {
        if (strcasecmp(word, pointer->word) == 0) // case-insensitive string comparisons
        {
            return true;
        }
        pointer = pointer->next; // put the pointer to the next node
    }
    
    return false;
}

// Hashes word to a number(index)
unsigned int hash(const char *word)
{
    // modified djib2, http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);
    
    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word ++;
        c = tolower(c);
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1]; // space for each word read
    while (fscanf(file, "%s", word) != EOF) // scan for strings until end of file
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word); // copy word into n.word of type node.
        int hash_number = hash(word); // hash the word into a number.
        n->next = table[hash_number]; // Insert the node into hash table by setting new pointer,
        table[hash_number] = n; // then set the first node to the new pointer.
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) // loops through all buckets
    {
        node *pointer = table[i]; // pointing towards the table array, with current loop iteration in mind.
        
        while (pointer != NULL) // while not at the end of array
        {
            node *tmp = pointer; // assign another pointer to the same node
            pointer = pointer->next; //point the first pointer onto the next node
            free(tmp); // free the first node
        }
        if (i == N - 1 && pointer == NULL) // searched complete.
        {
            return true;
        }
    }
    return false;
}
