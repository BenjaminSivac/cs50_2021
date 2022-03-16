#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc(3 * sizeof(int)); // make an array of size 3. 
    if (list == NULL) // error-checking
    {
        return 1;
    }
    
    // *list = 1; // "go to that address and put the value 1"
    
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    
    int *tmp = realloc(list, 4 * sizeof(int)); // add a fourth number to the already allocated array called list
    if (tmp == NULL) // error-checking
    {
        free(list);
        return 1;
    }
    
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    
    tmp[3] = 4;
    
    free(list);
    
    list = tmp;
    
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }
    
    free(list);
}