#include <stdio.h>
#include <cs50.h>

// The purpose of this code is to complete the "hello" assignment from the week 1 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/1/hello/

// prompt the user for their name, and then welcome them using their name.
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
