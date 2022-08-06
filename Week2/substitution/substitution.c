#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string cipher(string plaintext, string key);
int key_check(string key);
const int ALPHA_SIZE = 26;

int main(int argc, string argv[])
{
    //check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //set key to uppercase
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }

    //key check
    switch (key_check(key))
    {
        case 0:
            break;

        case 1:
            printf("Key must contain 26 characters.\n");
            return 1;
            break;

        case 2:
            printf("Key character must be alphabetical.\n");
            return 1;
            break;

        case 3:
            printf("Key character must be unique.\n");
            return 1;
            break;

        default:
            break;
    }

    //getstring
    string plaintext = get_string("plaintext: ");

    //cipher
    string ciphertext = cipher(plaintext, key);

    //output
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

//check if the key is valid
int key_check(string key)
{
    //length check
    if (strlen(key) != ALPHA_SIZE)
    {
        return 1;
    }

    //check if is alphabetical
    for (int i = 0; i < ALPHA_SIZE; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 2;
        }
    }

    //uniqueness check
    for (int i = 0; i < ALPHA_SIZE - 1; i++)
    {
        for (int j = i + 1; j < ALPHA_SIZE; j++)
        {
            if (key[i] == key[j])
            {
                return 3;
            }
        }
    }

    return 0;
}

//cipher
string cipher(string plaintext, string key)
{
    string ciphertext = plaintext;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = key[plaintext[i] - 'A'];
            }
            else
            {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            }
        }
    }
    return ciphertext;
}