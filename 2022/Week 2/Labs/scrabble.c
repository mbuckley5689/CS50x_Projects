#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// The purpose of this code is to complete the "scrabble" assignment from the week 2 lab for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/labs/2/

// A has int value 65, a has int value 97
// Consult the ASCII chart for additional integer values of characters.

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

// Convert a word into points using scrabble's rules
// Two players will submit their words of choice and "main" will decide the winner
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int letter;     // specific letter of the word being scored
    int score = 0;  // score of the word being analyzed
    int char_count = strlen(word);  // character count of the word being analyzed
    // scores the word of choice
    for (int i = 0; i < char_count; i++)
    {
        letter = word[i];

        if (islower(letter) != false)   // converts lowercase letters to uppercase letters
        {
            letter -= 32;
        }

        if (isalpha(letter) != 0)   // scores the indexed letter of the word (ommitting symbols)
        {
            letter -= 65;
            score += POINTS[letter];
        }

    }

    return score; // returns the total score of the word used as the argument
}
