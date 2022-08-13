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
int check_mastercard(long sixteen_digit_number);
int check_amex(long sixteen_digit_number);
int check_visa(long sixteen_digit_number);

int main(void)
{
    printf("\n");
    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq_amex = 15;
    int digitreq_mastercard = 16;
    int digitreq_visa_one = 13;
    int digitreq_visa_two = 16;
    // define minimum and maximum credit card numbers
    long amex_min = pow(base, digitreq_amex);
    long amex_max = pow(base, digitreq_amex + 1) - 1;
    long mastercard_min = pow(base, digitreq_mastercard);
    long mastercard_max = pow(base, digitreq_mastercard + 1) - 1;
    long visa_one_min = pow(base, digitreq_visa_one);
    long visa_one_max = pow(base, digitreq_visa_one + 1) - 1;
    long visa_two_min = pow(base, digitreq_visa_two);
    long visa_two_max = pow(base, digitreq_visa_two + 1) - 1;

    // ask the user for their credit card number.
    // repeat the inquiry if they input an invalid number.
    long ccnumber = get_long("Please enter your credit card number: \n");

    // verify whether the credit card number is valid or not via Luhn's Algorithm
    // luhns integer indicates the number that the algorithm must output for the
    // credit card number to be valid
    int luhns_modulo = 10;
    int verify_luhns = luhns(ccnumber);
    //printf("luhns number: %i\n", verify_luhns);

    if (verify_luhns % luhns_modulo == 0)
    {
        // check to see if the credit card may be an American Express
        int verify_amex = check_amex(ccnumber);
        if (verify_amex == 1)
        {
            printf("AMEX\n");
        }
        // check to see if the credit card may be a Mastercard
        int verify_mastercard = check_mastercard(ccnumber);
        if (verify_mastercard == 1)
        {
            printf("MASTERCARD\n");
        }

        // check to see if the credit card may be a VISA
        int verify_visa = check_visa(ccnumber);
        if (verify_visa == 1)
        {
            printf("VISA\n");
        }

        // check to see if the credit card is valid or not
        if (verify_amex != 1 && verify_mastercard != 1 && verify_visa != 1)
        {
            printf("INVALID\n");
        }
    }

    if (verify_luhns % luhns_modulo != 0)
    {
        printf("INVALID\n");
    }


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
    while (check >= 0)
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
        //printf("current index: %i\n", i);
        // initializes the current credit card number in the sweep
        int current_index = indexdigit(sixteen_digit_number, i);
        //printf("index value: %i\n", current_index);

        // enters the condition for doing operations on every-other number
        // in the credit card number, if you started counting from the right-side of the number.
        // note that the loop actually counts from the left but indexes the correct numbers.

        // this loop will multiply every other number by two. each digit of each of those products
        // are to then added to the "checker" total.
        if ((ccnumber_max_index % 2 != 0 && i % 2 != 0) || (ccnumber_max_index % 2 == 0 && i % 2 != 0))
        {
            int intermediate_addition = current_index * 2;
            //printf("intermediate addition: %i\n", intermediate_addition);
            int intermediate_max_index = digitcount(intermediate_addition) - 1;
            //printf("intermediate max index: %i\n", intermediate_max_index);
            for (int j = intermediate_max_index; j > -1; j--)
            {
                int intermediate_index = indexdigit(intermediate_addition, j);
                //printf("intermediate index: %i\n", intermediate_index);
                total = total + intermediate_index;
                //printf("total: %i\n", total);
            }
        }
        // for all indices excluded in the previous "every-other" indexing and summing,
        // add each individually to the "checker" sum.
        else
        {
            total = total + current_index;
            //printf("total: %i\n", total);
        }
    }
    return total;
}

// check to see if a sixteen digit credit card number is a mastercard
// (assuming the number passes Luhn's Algorithm)
int check_mastercard(long sixteen_digit_number)
{
    int index_one = 15;
    int index_two = 14;
    int verify_mastercard = 0;
    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq_mastercard = 16;
    // define minimum and maximum credit card numbers
    long mastercard_min = pow(base, digitreq_mastercard - 1);
    long mastercard_max = pow(base, digitreq_mastercard);
    //printf("mastercard min: %lu\n", mastercard_min);
    //printf("mastercard max: %lu\n", mastercard_max);

    int digit_one = indexdigit(sixteen_digit_number, index_one);
    int digit_two = indexdigit(sixteen_digit_number, index_two);
    if (digit_one == 5 && (digit_two == 1 || digit_two == 2 || digit_two == 3 || digit_two == 4 || digit_two == 5))
    {
        verify_mastercard = 1;
    }

    if (sixteen_digit_number < mastercard_min || sixteen_digit_number >= mastercard_max)
    {
        verify_mastercard = 0;
    }

    return verify_mastercard;
}

// check to see if a sixteen digit credit card number is an american express
// (assuming the number passes Luhn's Algorithm)
int check_amex(long sixteen_digit_number)
{
    int index_one = 14;
    int index_two = 13;
    int verify_amex = 0;
    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq_amex = 15;
    // define minimum and maximum credit card numbers
    long amex_min = pow(base, digitreq_amex - 1);
    long amex_max = pow(base, digitreq_amex);

    int digit_one = indexdigit(sixteen_digit_number, index_one);
    //printf("Digit 1: %i\n", digit_one);
    int digit_two = indexdigit(sixteen_digit_number, index_two);
    //printf("Digit 2: %i\n", digit_two);
    if (digit_one == 3 && (digit_two == 4 || digit_two == 7))
    {
        verify_amex = 1;
    }

    if (sixteen_digit_number < amex_min || sixteen_digit_number >= amex_max)
    {
        verify_amex = 0;
    }
    return verify_amex;
}

// check to see if a sixteen digit credit card number is an american express card
// (assuming the number passes Luhn's Algorithm)
int check_visa(long sixteen_digit_number)
{
    int verify_visa = 0;
    int index_one = digitcount(sixteen_digit_number) - 1;
    int index_two = index_one - 1;

    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq_visa_one = 13;
    int digitreq_visa_two = 16;
    // define minimum and maximum credit card numbers
    long visa_one_min = pow(base, digitreq_visa_one - 1);
    long visa_one_max = pow(base, digitreq_visa_one);
    long visa_two_min = pow(base, digitreq_visa_two - 1);
    long visa_two_max = pow(base, digitreq_visa_two);

    int digit_one = indexdigit(sixteen_digit_number, index_one);
    if (digit_one == 4)
    {
        verify_visa = 1;
    }
    if ((sixteen_digit_number < visa_one_min || sixteen_digit_number >= visa_one_max) &&
        (sixteen_digit_number < visa_two_min || sixteen_digit_number >= visa_two_max))
    {
        verify_visa = 0;
    }

    return verify_visa;
}
