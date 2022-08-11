#include <stdio.h>
#include <cs50.h>

// prompt the user for their name, and then welcome them using their name.
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
