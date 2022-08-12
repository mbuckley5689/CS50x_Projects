#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

// The purpose of this code is to complete the "credit" assignment from the week 1 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/1/credit/


int digitcount(long number);
long indexdigit(long number, int index);

int main(void)
{
    // define the base of the number system being used.
    int base = 10;
    // define the amount of digits required for a credit card number
    int digitreq = 16;
    // define minimum and maximum credit card numbers
    long ccmin = pow(base, digitreq);
    long ccmax = pow(base, digitreq + 1);
    ccmax = ccmax - 1;
    printf("%lu\n", ccmin);
    printf("%lu\n", ccmax);
    // ask the user for their credit card number.
    // repeat the inquiry if they input an invalid number.
    //long ccnumber = get_long("Please enter your credit card number: \n");
    long ccnumber = 4003600000000014;
    while (ccnumber < 1000000000000000 || ccnumber > 9999999999999999)
    {
        ccnumber = get_long("Please enter your credit card number: \n");
    }

    // check to see if the credit card number is valid via Luhn's Algorithm.
    long even_digit;
    long even_multiply;
    long even_total;
    long subtract_number;
    long iteration = 0;
    long base_now;
    long ccnumber_now = ccnumber;
    //printf("iteration: %lu\n", iteration);
    //printf("base_now: %lu\n", base_now);
    //printf("even_digit: %lu\n", even_digit);
    //printf("even_multiply: %lu\n", even_multiply);
    //printf("even_total: %lu\n", even_total);
    //printf("subtract_number: %lu\n", subtract_number);

    for (int even_position = digitreq - 1; even_position > 0; even_position = even_position - 1)
    {
        iteration++;
        printf("iteration: %lu\n", iteration);
        printf("ccnumber_now: %lu\n", ccnumber_now);
        base_now = pow(base, even_position);
        subtract_number = ccnumber_now % base_now;
        even_digit = (ccnumber_now - subtract_number) / base_now;
        ccnumber_now = subtract_number;
        even_multiply = even_digit * 2;
        if (even_position % 2 == 1)
        {
            even_total = even_total + even_multiply;
        }

        printf("even_position: %i\n", even_position);
        printf("base_now: %lu\n", base_now);
        printf("even_digit: %lu\n", even_digit);
        printf("even_multiply: %lu\n", even_multiply);
        printf("even_total: %lu\n", even_total);
        printf("subtract_number: %lu\n", subtract_number);
    }
    printf("This is the even total: %lu\n", even_total);
    int integer = 521;
    int digitcheck = digitcount(integer);
    printf("Number of digits: %i\n", digitcheck);
    long indexcheck = indexdigit(ccnumber, 2);
    printf("Indexed digit: %lu\n", indexcheck);
}

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
