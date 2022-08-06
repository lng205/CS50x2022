#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get input
    long num = get_long("Number: ");

    //calc
    int pointer = 0, digit = 0, digitbuf = 0, sum = 0;
    while (num > 0)
    {
        digitbuf = digit;
        digit = num % 10;
        pointer++;
        if (pointer % 2 == 0)
        {
            sum += (digit * 2) % 10 + (digit * 2) / 10;
        }
        else
        {
            sum += digit;
        }
        num = num / 10;
    }

    //output
    string cardtype = "INVALID";
    if (sum % 10 == 0)
    {
        switch (digit)
        {
            case 3:
                if (pointer == 15 && (digitbuf == 4 || digitbuf == 7))
                {
                    cardtype = "AMEX";
                }
                break;

            case 4:
                if (pointer == 13 || pointer == 16)
                {
                    cardtype = "VISA";
                }
                break;

            case 5:
                if (pointer == 16 && (digitbuf > 0 && digitbuf < 6))
                {
                    cardtype = "MASTERCARD";
                }
                break;

            default:
                break;
        }
    }
    printf("%s\n", cardtype);
}