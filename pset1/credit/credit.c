#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    //Prompt for credit card number
    long ccnumber = get_long("ccnumber: ");
    
    // count length of number
    int length = 0;
    long cc = ccnumber;
    while(cc > 0)
    {
        cc = cc / 10;
        length++;
    }
    // Check for valid length
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    // Calculate checksum
    int sum1 = 0;
    int sum2 = 0;
    long digit = ccnumber;
    int total = 0;
    int mod1;
    int mod2;
    int d1;
    int d2;
    
    do
    {
        //Removing last didigt of our ccnumber, then add to sum1
        mod1 = digit % 10;
        digit = digit / 10;
        sum1 = sum1 + mod1;
        
        // Removing second last digit
        mod2 = digit % 10;
        digit = digit / 10;
        
        // Doubling the second last digit, then add digits to sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10; // i.e. m0d2 = 14 becomes d1 = 1 & d2 = 4
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    while (digit > 10);
    
    total = sum1 + sum2 + digit;
    
    // Check Luhn Algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // Final check for type of card
    long start = ccnumber;
    do
    {
        start = start / 10;
    }
    while (start > 100);
    
    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}   