#include <cs50.h>
#include <stdio.h>

void print_slash(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - 1 - i; j++)
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
}


int main(void)
{
    int height;
    do
    {
        height = get_int("please enter height\n");
    }
    while (height < 1 || height > 8);
    print_slash(height);
}