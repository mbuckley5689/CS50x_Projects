#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

// The purpose of this code is to complete the "credit" assignment from the week 1 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/1/credit/

int digitcount(long number);
long indexdigit(long number, int index);
int luhns(long sixteen_digit_number);

int main(void)
{
    printf("\n");
    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq = 16;
    // define minimum and maximum credit card numbers
    long ccmin = pow(base, digitreq);
    long ccmax = pow(base, digitreq + 1);
    ccmax = ccmax - 1;
    // ask the user for their credit card number.
    // repeat the inquiry if they input an invalid number.
    //long ccnumber = get_long("Please enter your credit card number: \n");
    long ccnumber = 4003600000000014;
    while (ccnumber < 1000000000000000 || ccnumber > 9999999999999999)
    {
        ccnumber = get_long("Please enter your credit card number: \n");
    }

    int verify_twenty = luhns(ccnumber);
    printf("Verification Number: %i\n", verify_twenty);
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS DEFINED TO COMPUTE LUHN'S ALGORITHM & VERIFY THE CREDIT CARD VENDOR
////////////////////////////////////////////////////////////////////////////////

// function to count the number of digits in a positive integer
int digitcount(long number)
{
    long check = 1;
    int digit = 0;
    long base = 10;
    long base_now = base;
    while (check > 0)
    {
        digit = digit + 1;
        check = number;
        check = check - base_now;
        base_now = base_now * base;
    }
    return digit;
}

// index a digit in a positive integer
// the function uses 0-indexing
long indexdigit(long number, int index)
{
    long subtract_number;
    long indexed_output;
    int base = 10;
    long divisor;

    long number_of_digits = digitcount(number);

    for (int i = number_of_digits; i > index; i--)
    {
        divisor = pow(base, i - 1);
        subtract_number = number % divisor;
        indexed_output = (number - subtract_number) / divisor;
        number = subtract_number;
    }
    return indexed_output;
}

// check to see if a credit card is verified by Luhn's Algorithm.
// the credit card is verified if the algorithm outputs the number "20"
int luhns(long sixteen_digit_number)
{
    // establish the maximum index of the credit card number
    int ccnumber_max_index = digitcount(sixteen_digit_number) - 1;
    // initializes Luhn's Algorithm's "checker". this number should equal "20" at the end of the algorithm
    int total = 0;
    // loop that sweeps through each index of the credit card.
    // the loop starts at the left-most digit and ends with the right-most
    for (int i = ccnumber_max_index; i > -1; i--)
    {
        // initializes the current credit card number in the sweep
        int current_index = indexdigit(sixteen_digit_number, i);

        // enters the condition for doing operations on every-other number
        // in the credit card number, if you started counting from the right-side of the number.
        // note that the loop actually counts from the left but indexes the correct numbers.

        // this loop will multiply every other number by two. if one of those numbers has greater than one digit,
        // then add each of its digits together.
        // add all of these numbers together, not including the two-digit numbers themselves
        if (i % 2 != 0)
        {
            int intermediate_addition = current_index * 2;
            int intermediate_max_index = digitcount(intermediate_addition) - 1;
            if (intermediate_max_index > 0)
            {
                for (int j = intermediate_max_index; j > -1; j--)
                {
                int intermediate_index = indexdigit(intermediate_addition, j);
                total = total + intermediate_index;
                }
            }

            else
            {
                total = total + intermediate_addition;
            }

        }
        // for all indices excluded in the previous "every-other" indexing and summing,
        // add each individually to the "checker" sum.
        else
        {
            total = total + current_index;
        }
    }
    return total;
}
