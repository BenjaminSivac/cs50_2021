#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// ASCII capital letters, add 32 for small letters.
int c_letters[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

int new_points[] = {}; //temporary points for the loop process

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins with %i points\n", score1);
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins with %i points\n", score2);
    }
    else
    {
        printf("Tie, both scoring %i points\n", score1);
    }
}

int compute_score(string word)
{
    int current_score = 0; // starting value
    
    for (int i = 0; i < strlen(word); i++) // proccessing each letter 1-by-1, as many times as the length of the word
    {
        if (isupper(word[i]))
        {
            for (int j = 0; j < sizeof(c_letters); j++) // limiting the word to the data size
            {
                if (word[i] == c_letters[j]) // if found, award points according to the index and add onto current score
                {
                    new_points[i] = POINTS[j];
                    current_score += new_points[i];
                }
            }
        }
        else if (islower(word[i]))
        {
            for (int j = 0; j < sizeof(c_letters); j++)
            {
                if (word[i] == c_letters[j]+32)
                {
                    new_points[i] = POINTS[j];
                    current_score += new_points[i];
                }
            }
        }
        else // skip words or signs outside the alphabet
        {
            i = i + 1;
        }
    }
    return current_score; // self-explanatory
}
