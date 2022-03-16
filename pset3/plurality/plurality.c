#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{   
    for (int i = 0; i < candidate_count; i++) // For-loop that runs equal to candidate count.
    {
        if (strcmp(candidates[i].name, name) == 0) // if a string has 0 differences to a name in the array
        {
            candidates[i].votes++; // Add +1 to the vote.
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int maxvotes = 0; // Starting value for maxvotes.
    
    for (int i = 0; i < candidate_count; i++) // For-loop that runs equal to candidate count.
    {
        if (candidates[i].votes > maxvotes) // if candidate votes is more than current maxvotes
        {
            maxvotes = candidates[i].votes; // Then maxvotes are assigned the same value as count of votes.
            
        }
    }
    
    for (int i = 0; i < candidate_count; i++) // For-loop that runs equal to candidate count.
    {
        if (candidates[i].votes == maxvotes) // After the first loop is done, if a candidates votes is equal to the maxvotes, it has won.
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

