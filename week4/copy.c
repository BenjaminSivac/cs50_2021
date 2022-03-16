#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");
    
    char *t = malloc(strlen(s) + 1); // memory allocation
    
    if (t == NULL) // address 0.
    {
        return 1;
    }
    
    for (int i = 0, n = strlen(s); i <= n; i++) // or strcpy(t, s);
    {
        t[i] = s[i]; // or *(t+i) = *(s+i)
    }
    
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }
    
    printf("s: %s\n", s);
    printf("t: %s\n", t);
    
    free(t); // free the space allocated by the malloc function.
}