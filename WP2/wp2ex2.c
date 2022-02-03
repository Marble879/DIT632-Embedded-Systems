// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 2
// Submission code: 941100 (provided by your TA-s)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#### Constants #####
#define MAX 5
#define MAX_RANDOM_NUMBER 101             // Defines the maximum value that a number can be in the node
#define NEW_FIRST 45                      // Defines the number that the new first node will have
#define LINE "\n----------------------\n" // Defines the line for readability
// ##### typedefs ####
typedef struct q
{
    int number;
    struct q *next;
    struct q *prev;
} REGTYPE;

// ##### Function declarations #####
REGTYPE *random_list(void);
REGTYPE *add_first(REGTYPE *temp, int data);

//###### Main program #######
int main(int argc, char *argv[])
{
    int nr = 0;
    REGTYPE *act_post, *head = NULL;
    srand(time(0)); // Random seed
    head = random_list();
    act_post = head;
    while (act_post != NULL)
    {
        nr++;
        printf("\n Post nr %d : %d", nr, act_post->number);
        act_post = act_post->next;
    }

    // Print line for readability
    printf(LINE);
    // Test the add_first method with the NEW_FIRST number
    head = add_first(head, NEW_FIRST);

    // Reset act-post to the beginning of the list
    act_post = head;
    nr = 0; // reset the nr counter
    // Loop until the null node is reached
    while (act_post != NULL)
    {
        // Add one to the counter
        nr++;
        // Print the number at the positions in the linked list
        printf("\n Post nr %d : %d", nr, act_post->number);
        // Move act-post to the next node
        act_post = act_post->next;
    }

    // --- Free the allocated memory ---
    while ((act_post = head) != NULL)
    {
        head = act_post->next;
        free(act_post);
    }

    return 0;
}

// ==== End of main ======================================

// Function implementation for REGTYPE *random_list(void)
REGTYPE *random_list(void)
{
    int nr; // Declare the random number

    REGTYPE *top, *old, *item; // Declare the three pointers: top for the head, old for the previous node, and item for the current node

    // Allocate memory on the heap with size of REGTYPE, and assign the memory location to top.
    top = malloc(sizeof(REGTYPE));

    // Calculates a random number in the range of 0 - 100. Reference: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx.
    nr = rand() % MAX_RANDOM_NUMBER;
    // Assign the previous node as null
    top->prev = NULL;
    // Assign the random number to the head node
    top->number = nr;
    // Assign the next node as null
    top->next = NULL;

    // Point old to the same node as top
    old = top;

    // Loops until the remaining 4 number of nodes have been created
    for (int i = 0; i < MAX - 1; i++)
    {
        item = malloc(sizeof(struct q)); // Point item to new node
        old->next = item;                // The next of the previous node should point to new node
        item->prev = old;                // The new node should point to previous old node
        item->next = NULL;               // The item should point to next
        nr = rand() % MAX_RANDOM_NUMBER; // Calculates a random number in the range of 0 - 100. Reference: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx.
        item->number = nr;               // Assign the random number to the item number
        old = item;                      // Assign the item to the old node
    }

    // Return the head node
    return (top);
}
//==========================================================
// Function implementation for REGTYPE *add_first(REGTYPE *temp, int data)
REGTYPE *add_first(REGTYPE *temp, int data)
{
    REGTYPE *newTop;                  // define a new pointer that points to a REGTYPE
    newTop = malloc(sizeof(REGTYPE)); // Allocate the appropriate size in the heap and assign memory location to pointer
    newTop->number = data;            // Assign data value to the node's number
    newTop->next = temp;              // Make the next node of the new head the previous head
    newTop->prev = NULL;              // Make the previous node of the new head NULL
    temp->prev = newTop;              // Make the previous head have the new head as its previous node
    return newTop;                    // return new head
}