#include <cs50.h>
#include <stdio.h>

// The purpose of this code is to complete the "more comfortable" version of the "mario" assignment from the week 1 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/1/mario/more/

int main(void)
{
    int state = 1;
    while (state == 1)
    {
        // request a height for the mario blocks
        int height = get_int("Input an integer between 1 and 8 (including those numbers): \n");

        // initialize a variable to properly space the mario blocks
        int spaces = height - 1;

        // run the mario block loop
        if (height > 0 || height < 9)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = spaces; i < j; j--)
                {
                    printf(" ");
                }

                for (int j = 0; j <= i; j++)
                {
                    printf("#");
                }

                printf("  ");

                for (int j = 0; j <= i; j++)
                {
                    printf("#");
                }

                printf("\n");
            }
            state = 0;
        }

        // explain to the user that they incorrectly answered the prompt.
        // the while-loop will now repeat and ask the user for a height again.
        else
        {
            printf("Your input was invalid. Please follow the prompt.\n");
        }
    }
}
