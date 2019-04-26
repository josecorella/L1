//
//  main.c
//  The Book CLub
//
//  Created by Jose Corella on 4/6/17.
//  Copyright © 2017 Jose Corella. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct BOOK //book structure
{
    char title[51]; //holds title
    char stitle[51]; //holds lowercase title
    char author[31]; //holds author
    char sauthor[31]; //holds lowercase author
    char genre[21]; //holds genre
    int rate; //holds rating
    int pgs; //holds number of pages
};

int input(); //asks user if sort or book info
struct BOOK bookinput(int*); //if user needs to input book info
void sort(int*, struct BOOK[]); //prompts user for sort type
void sortauth(int*, struct BOOK[]); //sorts by author's last name
void sortcat(int*, struct BOOK[]); //sorts by genre
void sortpg(int*, struct BOOK[]); //sorts by # of pages
void display(int*, struct BOOK[]); //displays all books

int main (void)
{
    struct BOOK novel[30]; //book info
    int flag = 1, choice , bnum = 0; //keeps track of number of books in program
    int* bnumptr = NULL;  //points to bnum
    bnumptr = &bnum;
    do
    {
        puts("WELCOME TO YOUR LIBRARY!\nTO CONTINUE HIT ONE OF THE FOLLOWING KEYS:\n");
        choice = input(); //gets user input
        switch(choice)
        {
            case 1:
                novel[bnum] = bookinput(bnumptr); //gets book info
                bnum++; //increases number of books in program
                break;
            case 2:
                getchar();//get trash
                sort(bnumptr, novel); //asks sort type
                break;
            case 3:
                getchar();//get trash
                display(bnumptr, novel); //displays all books
                break;
            default:
                flag = 0; //quits program
                printf("\nGoodbye. . . \n\n");
                break; //quits
        }
    }
    while(flag == 1);
    return 0;
}
/****************input() Function*******************/
int input()
{
    int flagi = 1;            //prompts user to enter info or sort
    printf("1: Input Information on a Book\n2: View Sorted List of Books\n3: Display Books\n4: Quit\n");
    scanf("%d", &flagi);
    while((flagi != 1) && (flagi != 2) && (flagi != 3) && (flagi != 4)) //makes sure user gives wanted response
    {
        printf("\n'%d' is not a valid input: ", flagi);
        scanf("%d", &flagi);
    }
    return flagi;
}
/******************bookinput() Function******************/
struct BOOK bookinput(int* bnumptr)
{
    //Declare temp Variables
    struct BOOK inputinfo;          //get information
    int x;
    char first[16];
    char* token;
    
    //get information
    getchar();
    printf("\n--Enter Book Information--");
    printf("\nEnter the Title: ");    //get title
    gets(inputinfo.title);
    printf("\nEnter the Author's Name (Last, First): ");    //get author name
    gets(inputinfo.author);
    printf("\nEnter the genre: "); //get genre
    gets(inputinfo.genre);
    printf("\nEnter the Number of Pages: "); //get number of pages
    scanf("%d", &inputinfo.pgs);
    printf("\nEnter the Rating (1-10): "); //get rating
    scanf("%d", &inputinfo.rate);
    //CHECK FOR SPECIAL CASES FOR AUTHOR AND TITLE FOR SORTING LATER
    
    //CHECK FOR "THE, AN, A" IN TITLE
    //copies inputinfo.title into inputinfo.stitle as lowercase and checks for: the/an/a
    for(x = 0; x < 51; x++ )
        inputinfo.stitle[x] = tolower(inputinfo.title[x]); //give stitle lowercase of title
        
        //remove any the/a/an from beginning of stitle
        if(strstr(inputinfo.stitle, "the ") != NULL) //tests for "the" and moves it to end of string
        {
            for( x = 0; x < 51; x++)
                inputinfo.stitle[x] = inputinfo.stitle[x+4];
            strcat(inputinfo.stitle,", the");
        }
    
    if( strstr(inputinfo.stitle, "an ") != NULL) //tests for "an" and moves it to end of string
    {
        for(x = 0; x < 30; x++)
            inputinfo.stitle[x] = inputinfo.stitle[x+3];
        strcat(inputinfo.stitle,", an");
    }
    
    if(strstr(inputinfo.stitle, "a ") != NULL) //tests for "a" and moves it to end of string
    {
        for(x = 0; x < 30; x++)
            inputinfo.stitle[x] = inputinfo.stitle[x+2];
        strcat(inputinfo.stitle,", a");
    }
    
    //CHECKS FOR LAST/FIRST NAME ORDER --> IF NOT IN ORDER THEN CHANGES LAST, FIRST
    //copies inputinfo.author into inputinfo.sauthor as lowercase and checks for last/first format using commas
    for( x = 0; x < 31; x++)
        inputinfo.sauthor[x] = tolower(inputinfo.author[x]); //give sauthor lowercase of author
        
    /*checks for last/first order in sauthor
     if first name is before last then puts first name after last name*/
        if(strstr(inputinfo.sauthor, ",") == NULL)
        {
            token = strtok(inputinfo.sauthor, " "); //tokenizes inputinfo.sauthor
            strcpy(first, token);                  //gives first variable first name
            token = strtok(NULL, " ");              //gets last name token
            strcpy(inputinfo.sauthor, token);      //gives inputinfo.sauthor last name
            strcat(inputinfo.sauthor, ", ");       //adds ", " to last name for formatting
            strcat(inputinfo.sauthor, first);      //adds first name to sauthor string
        }
    return inputinfo;
}
/*******************sort() Function*******************/
void sort(int* bnumptr, struct BOOK srtbk[30])
{
    int srttype;            //asks for sort type
    printf("\nHow would you like to sort the books?\n1: Author's Last Name\n2: Genre\n3: Number of Pages\n4: Title\n0: Return\n");
    scanf("%d", &srttype);
    
    while((srttype != 1) && (srttype != 2) && (srttype != 3) && (srttype != 4) && (srttype != 0)) //error trap
    {
        printf("\nInvalid Input: "); //checks for valid response
        scanf("%d", &srttype);
    }
    
    switch(srttype) //chooses sort type on  user input
    {
        case 1:
            sortauth(bnumptr, srtbk); //sorts by author's name
            printf("\nSuccessfully Sorted List.\n");
            
            break;
        case 2:
            sortcat(bnumptr, srtbk); //sorts by genre
            printf("\nSuccessfully Sorted List.\n");
            break;
        case 3:
            sortpg(bnumptr, srtbk); //sorts by number of pages
            printf("\nSuccessfully Sorted List.\n");
            break;
        default:
            break;
    }
    return;
}
/*******************sortauth() Function*******************/
void sortauth(int* bnumptr, struct BOOK authbk[30])         //sorts by author name
{
    //Declare Variables
    struct BOOK authtmp;
    int x, y; //index for bubble sort and other for loops
    
    for(y = 0; y < *bnumptr; y++)
        for(x = 0; x < *bnumptr-1; x++)
            if(strcmp(authbk[x].sauthor, authbk[x+1].sauthor) >= 1) //checks which author is bigger
            {
                authtmp = authbk[x];
                authbk[x] = authbk[x+1]; //swaps locations
                authbk[x+1] = authtmp;
            }
    
    return;
}

/*******************sortcat() Function*******************/
void sortcat(int* bnumptr, struct BOOK catbk[30])
{
    //Declare Variables
    struct BOOK cattmp;
    int x, y; //index for bubble sorts
    
    for(y = 0; y < *bnumptr; y++)
        for(x = 0; x < *bnumptr-1; x++)                           //bubble sorts array based on genre
            if(strcmp(catbk[x].genre, catbk[x+1].genre) >= 1)
            {
                cattmp = catbk[x];
                catbk[x] = catbk[x+1];   //swaps locations
                catbk[x+1] = cattmp;
            }
    
    return;
}

/*******************sortpg() Function*******************/
void sortpg(int* bnumptr, struct BOOK pgbk[30])
{
    //Declare Variables
    struct BOOK pgtmp;
    int x, y; //index for bubble sort
    
    for(y = 0; y < *bnumptr; y++)
        for(x = 0; x < *bnumptr-1; x++)               //bubble sorts based on page number
            if(pgbk[x+1].pgs > pgbk[x].pgs)
            {
                pgtmp = pgbk[x];  //swaps locations
                pgbk[x] = pgbk[x+1];
                pgbk[x+1] = pgtmp;
            }
    
    return;
}
/*****************display() Function*********************/
void display(int* bnumptr, struct BOOK novel_[30])
{
    int x; //index for for loop
    if(*bnumptr == 0) //checks to see if books are in program
        printf("\nThere are no Books stored in the program.\n");
    else
    {
        printf("---------------------------------------------------------------------\n");  //output of books in table
        printf("Rating:  # of Pages:  Genre:     Author:          Title:\n");
        for(x = 0; x < *bnumptr; x++) //prints books
            printf("%-8d %-12d %-10s %-16s %s\n", novel_[x].rate, novel_[x].pgs, novel_[x].genre, novel_[x].author, novel_[x].title);
        printf("\n");
    }
    puts("\n");
    return;
}






