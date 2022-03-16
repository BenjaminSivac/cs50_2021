#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int main(void)
{
    string s = get_string("Text: "); // Asking for a string input
    
    // Our variables
    int lcount = 0;
    int wcount = 1;
    int scount = 0;

//Loop for letters, words and sentences for each 'if' condition, respectively.
    for (int i = 0; i < strlen(s); i++)
    {
       if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
       {
           lcount++;
       }
       else if (s[i] == ' ')
       {
           wcount++;
       }
       else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
       {
           scount++;
       }
    }
    // printf("letters: %i; words: %i; sentences: %i\n", letterscount, wordcount, sentencecount);
    
    //     
    float grade = 0.0588 * (100 * (float) lcount / (float) wcount) - 0.296 * (100 * (float) scount / (float) wcount) - 15.8;
    
    if (grade < 16 && grade >= 0)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}