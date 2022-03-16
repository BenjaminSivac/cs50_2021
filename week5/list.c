#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL; // no assigned value would cause segmentation error, as it would point to an garbage value
    
    node *n = malloc(sizeof(node)); // figures out how much memory is required by the structure definition we've made. 
    if (n = NULL)
    {
        return 1;
    }
    n->number = 1; // go into the node n and assign 1 to the number field
    n->number = NULL; // next pointer to NULL.
    list = n;
    
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;
    
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    
    while (list != NULL)
    {
        node *tmp = list -> next;
        free(list);
        list = tmp;
    }
}