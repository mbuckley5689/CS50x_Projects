#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// The purpose of this code is to complete the "substitution" assignment from the week 2 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/2/substitution/

// User enters a single 26-letter key (with no duplicate letters) as a command-line argument
// User enters a string, referred to as "plaintext".
// "main" converts the plaintext to an encrypted "ciphertext" using the key.
// Each element of the key substitutes the letter that is typically used in that index of the alphabet
int main(int argc, string argv[])
{
    // ends program & prints error if the user inputs more or less than one key as a command line argument
    if (argc != 2)
    {
        printf("In addition to -substitution- enter exactly one command line argument as a key.\n");
        return 1;
    }

    // stores and prints user's key
    string key = argv[1];
    for (int i = 0; i < strlen(key); i++) // converts key to uppercase for future processing
    {
        key[i] = toupper(key[i]);
    }

    // ends program & prints error if the key does not contain 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must be exactly 26 characters long\n");
        return 1;
    }

    // ends program & prints error if the key contains a non-letter, or if it contains duplicate letters
    for (int i = 0; i < strlen(key); i++) // indexes each letter in the key
    {
        int duplicate = 0; // (re)initializes a counter for counting duplicates
        if (isalpha(key[i]) == false) // confirms that each key element is a letter
        {
            printf("Key must contain only characters\n");
            return 1;
        }

        for (int j = 0; j < strlen(key); j++) // compares the current key element to every element in the key
        {
            if (key[i] == key[j])
            {
                duplicate++; // counts each duplicate in the key. note it will count the current element once.
            }
            if (duplicate > 1)
            {
                printf("No characters in the key may be duplicates\n");
                return 1;
            }
        }

    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (argc == 2 && isalpha(key[i]) == false)
        {
            printf("Key must contain only characters\n");
            return 1;
        }
    }

    //key = "BCDEFGHIJKLMNOPQRSTUVWXYZA";
    printf("key: %s\n", key);

    // ask the user for a word to be translated into a cipher via the key
    string ptext = get_string("plaintext: ");

    // create an array where each element is a letter of the alphabet
    int alphabet_length = 26; // number of letters in the alphabet
    char alphabet[alphabet_length];
    alphabet[0] = 'A';
  
    for (int i = 0; i < (alphabet_length); i++)
    {
        alphabet[i + 1] = alphabet[i] + 1;
        if (i == (alphabet_length - 1))  // adds null terminator "\0" at the end of the array
        {
            alphabet[i + 1] = '\0';
        }
    }

    // initialize variables relevant to converting plaintext to ciphertext
    string ptext_case; // initiailize the case of the indexed plaintext
    int alphabet_index = 0; // initialize the index of the alphabet according to the indexed plaintext
    string ctext = ptext; // initialize the ciphertext

    // "for loop" to convert plaintext to ciphertext
    for (int i = 0; i < (strlen(ptext)); i++) // index through each character in the plaintext
    {
        // store the case of the indexed plaintext
        if (isupper(ptext[i]))
        {
            ptext_case = "upper";
        }
        if (islower(ptext[i]))
        {
            ptext_case = "lower";
        }

        // identify the index of the alphabet according to the indexed plaintext
        for (int j = 0; j < strlen(alphabet); j++)
        {
            if (toupper(ptext[i]) == alphabet[j])
            {
                alphabet_index = j;
            }
        }

        // check to see if the indexed plaintext is a letter & convert to ciphertext
        if (isalpha(ptext[i]))
        {
            ctext[i] = key[alphabet_index]; // convert plaintext to ciphertext (letter only)

            if (strcmp(ptext_case, "upper") == 0) // convert ciphertext to uppercase, if appropriate
            {
                ctext[i] = toupper(ctext[i]);
            }

            if (strcmp(ptext_case, "lower") == 0) // convert ciphertext to lowercase, if appropriate
            {
                ctext[i] = tolower(ctext[i]);
            }
        }
    }

    printf("ciphertext: %s\n", ctext);
}
