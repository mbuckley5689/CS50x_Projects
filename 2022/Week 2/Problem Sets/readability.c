#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// The purpose of this code is to complete the "readability" assignment from the week 2 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/2/readability/

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);

// compute a the reading grade level of an inputted text
// via the Coleman-Liau index
int main(void)
{
    string text = get_string("Text: "); // prompt user for text
    float letter_count = count_letters(text); // count the number of letters in the input
    float word_count = count_words(text); // count the number of words in the input
    float sentence_count = count_sentences(text); // count the number of sentences in the input

    float L = letter_count / word_count * 100; // number of letters per 100 words
    float S = sentence_count / word_count * 100; // number of sentences per 100 words

    int grade = round(0.0588 * L - 0.296 * S - 15.8); // compute the Coleman-Liau index

    printf("%f letters\n", letter_count);
    printf("%f words\n", word_count);
    printf("%f sentences\n", sentence_count);
    printf("%.3f letters per 100 words\n", L);
    printf("%.3f sentences per 100 words\n", S);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// counts the number of letters in a string
int count_letters(string input)
{
    int letters = 0;
    int input_length = strlen(input);
    for (int i = 0; i < input_length; i++) // sweeps through characters in a string
    {
        if (isalpha(input[i]) != false) // true if a character is a letter
        {
            letters++;
        }
    }
    return letters;
}

// counts the number of words in a string
int count_words(string input)
{
    int space = 32; // ASCII value for the "space" character
    int first_letter;
    int middle_letter;
    int last_letter;
    int words = 1; // initializes the number of words in the input string as 1
    int input_length = strlen(input);
    int loop_limit = input_length - 2;
    // sets the number of words to zero for strings of length 1 with no letters
    if (input_length == 1)
    {
        if (isalpha(input[0]) == false)
        {
            words = 0;
        }
    }
    // sets the number of words to zero for strings of length 2 with no letters
    else if (input_length == 2)
    {
        if (isalpha(input[0]) == false || isalpha(input[1]) == false)
        {
            words = 0;
        }
    }
    // counts the number of words in the input string, when it is longer than 2 characters
    else
    {
        for (int i = 0; i < loop_limit; i++)
        {
            first_letter = input[i];
            middle_letter = input[i + 1];
            last_letter = input[i + 2];
            // checks for a non-space character, then space, then non-space character
            if (first_letter != space && middle_letter == space && last_letter != space)
            {
                words++;
            }
            // checks for, at the end of the input string, a space, then a non-space character
            if (middle_letter == space && last_letter != space && i == loop_limit - 1)
            {
                words++;
            }
        }
    }
    return words;
}

// counts the number of sentences in a string
int count_sentences(string input)
{
    int first_letter;
    int second_letter;
    int sentences = 0;
    int period = 46; // ASCII value for the "." character
    int question = 63; // ASCII value for the "?" character
    int exclamation = 33; // ASCII value for the "!" character
    int input_length = strlen(input); // number of characters in the input string

    // a sentence is defined as a letter before either a ".", "?", or "!"
    for (int i = 0; i < input_length; i++) // sweeps through input string, checking for sentences
    {
        first_letter = input[i];
        second_letter = input[i + 1];
        if (isalpha(first_letter) != false
            && (second_letter == period || second_letter == question || second_letter == exclamation))
        {
            sentences++;
        }
    }
    return sentences;
}
