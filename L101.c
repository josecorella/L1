//
//  main.c
//  Lab 101
//
//  Created by Jose Corella on 5/24/17.
//  Copyright © 2017 Jose Corella. All rights reserved.
//

//precompiler directives

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//structure of nodes
struct queuenode
{
    int data;
    struct queuenode *nextptr;
};

//using typedefs for clarity
typedef struct queuenode QUEUENODE;
typedef QUEUENODE * QUEUENODEPTR;

//define enumeration
enum MARBLES {NONE, BLACK, RED};

//function prototypes
int prompt();
int isempty(QUEUENODEPTR);
void enqueue(QUEUENODEPTR *, QUEUENODEPTR *, int [], int[], int *);
void dequeue(QUEUENODEPTR *, int);
void calculations(int, int, int, int, int);
void print();

int main()
{
    //kickstarting random number generator
    srand(time(0));

    //Declarations for placing marbles into lists
    
    int black[500];
    int red[500];
    QUEUENODEPTR headptr = NULL, tailptr = NULL, newptr = NULL;
    int option, i;
    do
    {
        int numb = 0;
        option = prompt();
        switch(option)
        {
            case '1':
                //loading array of marbles
                for (i = 0; i < 500; i++)
                {
                    black[i] = BLACK;
                }
                
                for (i = 0; i < 500; i++)
                {
                    red[i] = RED;
                }
                printf("\nMarbles Filled!\n");
            
                break;
                
            case '2':
                //performing adding and deletion of marbles
                enqueue(&headptr, &tailptr, black, red, &numb);
                dequeue(&headptr, numb);
                
                break;
                
        }
        
    }
    
    while (option != '3');
    while (headptr != NULL)
    {
        newptr = headptr;
        headptr = headptr -> nextptr;
        free(newptr);
    }
    printf("\nNodes have been freed!\n");
    return 0;
}
//prompting the user and returns the response

int prompt()
{
    int response;
    printf("What would you like to do: \n1.) Reset and Fill Marbles\n2.) Pull Marbles out and find statistics\n3.) Exit\n? ");
    response = getchar();
    getchar();
    return response;
}
//checking if there is no list of nodes to begin with
int isempty(QUEUENODEPTR hptr)
{
    return !hptr;
}

//adds a new value into the queue.
void enqueue(QUEUENODEPTR *hptr, QUEUENODEPTR *tptr, int blackmarbles[], int redmarbles[], int *totmarbles)
{
    
    QUEUENODEPTR newptr = NULL;
    int numb;
    int spot;
    int redcount = 0;
    int blackcount = 0;

    do
    {
        numb = ((rand() % 2) + 1);
        spot = ((rand() % 500));
    
        //finding blackmarble when it hasn't been repeated
        if (numb == 1 && blackmarbles[spot] != NONE)
        {
            newptr = malloc(sizeof(QUEUENODE));
            if (newptr)
            {
                //load new “node” with passed information
                newptr -> data = blackmarbles[spot];
                newptr -> nextptr = NULL;
                
                if(isempty(*hptr)) //insert in empty queue *hptr = newptr;
                {
                    *hptr = newptr;
                }
                else
                {
                    (*tptr) -> nextptr = newptr;
                }
                *tptr = newptr;
                blackmarbles[spot] = NONE;
                (*totmarbles)+=1;
                blackcount+=1;
            }
            else
            {
                printf("No memory available.\n");
            }
        }
        //findinng black marble is spot is alrready chosen previously
        else
            if(numb == 1 && blackmarbles[spot] == NONE)
            {
                newptr = malloc(sizeof(QUEUENODE));
                if (newptr)
                {
                    //load new “node” with passed information
                    newptr -> data = blackmarbles[spot];
                    newptr -> nextptr = NULL;
                    
                    if(isempty(*hptr)) //insert in empty queue *hptr = newptr;
                    {
                        *hptr = newptr;
                    }
                    else
                    {
                        (*tptr) -> nextptr = newptr;
                    }
                    *tptr = newptr;
                    (*totmarbles)+=1;
                }
                else
                {
                    printf("No memory available.\n");
                }
            }
            else
                //finding redmarble when it hasn't been repeate
                if (numb == 2 && redmarbles[spot] != NONE)
                {
                    newptr = malloc(sizeof(QUEUENODE));
                    
                    if (newptr)
                        
                    {
                        
                        //load new “node” with passed information
                        
                        newptr -> data = redmarbles[spot];
                        
                        newptr -> nextptr = NULL;
                        
                        if(isempty(*hptr))  //insert in empty queue *hptr = newptr;
                            
                        {
                            
                            *hptr = newptr;
                            
                        }
                        
                        else
                            
                        {
                            
                            (*tptr) -> nextptr = newptr;
                            
                        }
                        
                        *tptr = newptr;
                        
                        redmarbles[spot] = NONE;
                        
                        redcount+=1;
                        
                        (*totmarbles)+=1;
                        
                    }
                    
                    else
                        
                    {
                        
                        printf("Marble not inserted. No memory available.\n");
                        
                    }
                    
                }
        
                else
                    
                    //findinng red marble is spot is already chosen previously
                    
                    if(numb == 2 && redmarbles[spot] == NONE)
                        
                    {
                        
                        //load new “node” with passed information
                        
                        newptr = malloc(sizeof(QUEUENODE));
                        
                        if (newptr)
                            
                        {
                            
                            newptr -> data = redmarbles[spot];
                            
                            newptr -> nextptr = NULL;
                            
                            if(isempty(*hptr)) //insert in empty queue *hptr = newptr;
                                
                            {
                                
                                *hptr = newptr;
                                
                            }
                            
                            else
                                
                            {
                                
                                (*tptr) -> nextptr = newptr;
                                
                            }
                            
                            *tptr = newptr;
                            
                            (*totmarbles)+=1;
                            
                        }
                        
                        else
                            
                        {
                            
                            printf("No memory available.\n");
                            
                        }
                        
                    }
        
                    else
                        
                    {
                        
                        printf("Sorry, you somehow messed up");
                        
                    }
        
    }
    
    while (redcount + blackcount < 1000);
    
    
    
}
//dequeueing marbles

void dequeue(QUEUENODEPTR *hptr, int totmarbles)

{
    
    QUEUENODEPTR tempptr = NULL;
    
    int value = 0;
    
    int black = 0;
    
    int red = 0;
    
    int none = 0;
    
    int i;
    
    
    
    for (i = 1; i <= 10; i++)
        
    {
        
        value = (*hptr) -> data;
        
        tempptr = *hptr;
        
        *hptr = (*hptr) -> nextptr;
        
        free(tempptr);
        
        if (value == 1)
            
        {
            
            black++;
            
        }
        
        else
            
            if (value == 2)
                
            {
                
                red++;
                
            }
        
            else
                
                if (value == 0)
                    
                {
                    
                    none++;
                    
                }
        
    }
    
    print();
    
    calculations(i, black, red, none, totmarbles);
    
    
    
    for (i = 11; i <= 100; i++)
        
    {
        
        value = (*hptr)-> data;
        
        tempptr = *hptr;
        
        *hptr = (*hptr) -> nextptr;
        
        free(tempptr);
        
        if (value == 1)
            
        {
            
            black++;
            
        }
        
        else
            
            if (value == 2)
                
            {
                
                red++;
                
            }
        
            else
                
                if (value == 0)
                    
                {
                    
                    none++;
                    
                }
        
    }
    
    calculations(i, black, red, none, totmarbles);
    
    
    
    for (i = 101; i <= 1000; i++)
        
    {
        
        value = (*hptr) -> data;
        
        tempptr = *hptr;
        
        *hptr = (*hptr) -> nextptr;
        
        free(tempptr);
        
        if (value == 1)
            
        {
            
            black++;
            
        }
        
        else if (value == 2)
            
        {
            
            red++;
            
        }
        
        else if (value == 0)
            
        {
            
            none++;
            
        }
        
    }
    
    calculations(i, black, red, none, totmarbles);
    
    i += 1;
    
    while (!isempty(*hptr))
        
    {
        
        value = (*hptr) -> data;
        
        tempptr = *hptr;
        
        *hptr = (*hptr) -> nextptr;
        
        free(tempptr);
        
        if (value == 1)
            
        {
            
            black++;
            
        }
        
        else if (value == 2)
            
        {
            
            red++;
            
        }
        
        else if (value == 0)
            
        {
            
            none++;
            
        }
        
    }
    
    
    
    calculations(i, black, red, none, totmarbles);
    
    printf("\n");
    
}



//function to calculate exact percentage of each color

void calculations(int i, int black, int red, int none, int totmarbles){
    float blackper = 0.0;
    float redper = 0.0;
    float nonper = 0.0;
    blackper = (float) (black) / (red + black + none);
    redper =  (float) (red) / (red + black + none);
    nonper = (float) (none) / (red + black + none);

    if (i == 11 || i == 101 || i == 1001){
        printf("%12d%12.2f%12.2f%12.2f\n", i-1, redper * 100, blackper * 100, nonper * 100);
    }else{
        printf("%12d%12.2f%12.2f%12.2f\n", totmarbles, redper * 100, blackper * 100, nonper * 100);
    }
}



//function to print first line of text

void print()

{
    
    printf("\n%12s%12s%12s%12s", "# of pulls", "% RED", "% BLACK", "% REPEAT");
    
    printf("\n---------------------------------------------------\n");
    
}


