// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void freelinklist(node *n);

// Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26 + 26;

// Hash table
node *table[N];

// Counter of the words in table
unsigned int nwords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *tmp = table[hash(word)];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) < 3 || word[1] == '\'' || word[2] == '\'')
    {
        return tolower(word[0]) - 'a' + 17576;
    }
    return (tolower(word[0]) - 'a') * 676 + (tolower(word[1]) - 'a') * 26 + tolower(word[2]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("could not open %s.\n", dictionary);
        return false;
    }

    // Read the entire file(Assume the file is smaller than 1MB)
    char *buffer = malloc(NMEMB);
    if (buffer == NULL)
    {
        printf("insufficient memory.");
        fclose(file);
        return false;
    }
    const unsigned int FileSize = fread(buffer, 1, NMEMB, file);
    fclose(file);

    // Build table
    node *n = malloc(sizeof(node));
    n->next = NULL;
    node *tmp = NULL;
    for (int i = 0, j = 0, k; i < FileSize; i++)
    {
        // Read the next word
        if (buffer[i] != '\n')
        {
            n->word[j] = buffer[i];
            j++;
            continue;
        }
        n->word[j] = '\0';
        j = 0;

        // Add the word
        k = hash(n->word);
        if (table[k] == NULL)
        {
            table[k] = n;
        }
        else
        {
            tmp = table[k];
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = n;
        }

        // Create a new node(Assume sufficient memory)
        n = malloc(sizeof(node));
        n->next = NULL;

        // Count the number of words in table
        nwords++;
    }

    //Exit
    free(n);
    free(buffer);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return nwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        freelinklist(table[i]);
    }
    return true;
}

void freelinklist(node *n)
{
    if (n == NULL)
    {
        return;
    }
    free(n->next);
    free(n);
}