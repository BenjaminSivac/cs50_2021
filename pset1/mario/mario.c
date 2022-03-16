#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    //Prompt for Height
    int height;
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); //It will keep repeating while this condition is met.
    
    for (int i = 0; i < height; i++) 
    {
        for (int j = height - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 1; k <= i + 1; k++)
        {
            printf("#");
        }
        {
            printf("  ");
        }
        for (int l = 1; l <= i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}