#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{   
    // Prompt for starting size
    int n;
  
    do
    {
        n = get_int("Starting population size: ");
    }
    while (n < 9);

    // Prompt for end size
    int i;
  
    do
    {
        i = get_int("Ending population size: ");
    }
    while (i < n);

    // Calculate number of years until we reach threshold
    int new_n = n;
    int years = 0;
    while (new_n < i)
    {
        new_n = round(new_n + new_n / 3 - new_n / 4);
        years++;
    }
    // Print number of years
    printf("Years: %i \n", years);

}
