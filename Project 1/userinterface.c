/*****************************************************************************
*
* NAME:             Barryn Chun
*
* HOMEWORK:         Project 1
*
* CLASS:            ICS 212
*
* INSTRUCTOR:       Ravi Narayan
*
* DATE:             October 21, 2014
*
* FILE:             userinterface.c
*
* DESCRIPTION:      This file contains the main/GUI/user-input-checking 
*                   function definitions for AddressBook
*
*****************************************************************************/

#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import "record.h"
#import "userinterface.h"
#import "database.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

struct record *start = NULL;

char version_no[] = "1.0";
int debug = FALSE;

/*****************************************************************************
*
* Function name:        main
*
* DESCRIPTION:          the main function. Also checks for additional arguments,
*                       and runs the program accordingly
*
* Parameters:           argc - a given number of arguments
*                       argv - a given pointer to an array of argument strings
*
* Return values:        returnval
*                           1 - normal mode initialized
*                           2 - debug mode initialized
*                           0 - program not initialized, invalid arguments
*
*****************************************************************************/

int main(int argc, char *argv[]) 
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] main called\n");
        printf("argc:\n%d\n", argc);
        printf("\n");
    }
    
    int returnval;
    
    if (argc == 1)
    {
        printf("Loading Contacts...\n");
        readfile(&start, "save.txt");
        main_menu();
        printf("Saving Contacts...\n");
        writefile(start, "save.txt");
        printf("Contacts Saved.\n");
        returnval = 1;
    }
    else if (argc == 2 && strcmp(argv[1],"debug") == 0)
    {
        debug = 1;
        printf("Loading Contacts...\n");
        readfile(&start, "save.txt");
        main_menu();
        printf("Saving Contacts...\n");
        writefile(start, "save.txt");
        printf("Contacts Saved.\n");
        returnval = 2;
    }
    else
    {
        printf("usage:\t./ABook\n");
        printf("    \t./ABook debug\n");
        returnval = 0;
    }
    cleanup(&start);
    return returnval;
}

/*****************************************************************************
*
* Function name:        main_menu
*
* DESCRIPTION:          runs the main menu in a loop, collects the user's choices,
*                       and selects an option accordingly
*
* Parameters:           none
*
* Return values:        1 (TRUE), indicating that the function has executed
*
*****************************************************************************/

int main_menu() 
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] main_menu called\n");
        printf("\n");
    }
    
    int exit = FALSE;
    
    if (debug == FALSE)
    {
        print_menu("Welcome!");
    }
    else
    {
        print_menu("Welcome! Debug Mode active.");
    }
    while(exit == FALSE)
    {
        int input = getint(": ", 1);
        
        if (input == 6)
        {
            if (debug == FALSE)
            {
                system("clear");
            }
            exit = TRUE;
        }
        else if (input == 5)
        {
            option5();
        }
        else if (input == 4)
        {    
            option4();
        }
        else if (input == 3)
        {
            option3();
        } 
        else if (input == 2)
        {
            option2();
        } 
        else if (input == 1)
        {
            option1();
        } 
        else
        {
            print_menu("[ERROR]: Invalid command. Please choose from options 1-6.");
        }
    }
    return TRUE;
}

/*****************************************************************************
*
* Function name:        option1
*
* DESCRIPTION:          runs the specifics for addRecord
*
* Parameters:           none
*
* Return values:        none
*
*****************************************************************************/

void option1()
{    
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] option1 called\n");
        printf("\n");
    }
    
    if (debug == FALSE)
    {
        system("clear");
    }
    
    char name[100] = "";
    char* address;
    int yearofbirth;
    char telnumber[100] = "";
    
    printf("[Adding record...]-------------------------------------------\n");
    printf("Name: ");
    fgets(name, 100, stdin);
    printf("Address (multi-line input, press \"enter\" twice to complete):\n");
    address = getfield();
    yearofbirth = getint("Year of Birth: ", 0);
    printf("Phone Number: ");
    fgets(telnumber, 100, stdin);
    name[strlen(name) - 1] = '\0';
    telnumber[strlen(telnumber) - 1] = '\0';
    printf("-------------------------------------------------------------\n");
    
    addRecord(&start, name, address, yearofbirth, telnumber);
    
    print_menu("Record Added.");
}

/*****************************************************************************
*
* Function name:        option2
*
* DESCRIPTION:          runs the specifics for deleteRecord
*
* Parameters:           none
*
* Return values:        none
*
*****************************************************************************/

void option2()
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] option2 called\n");
        printf("\n");
    }
    
    if (start == NULL)
    {
        print_menu("[ERROR]: There's no one in your AddressBook to delete!");
    }
    else 
    {    
        if (debug == FALSE)
        {
            system("clear");
        }
    
        char name[100] = "";
        
        printf("[Deleting record...]-----------------------------------------\n");
        printf("Name: ");
        fgets(name, 100, stdin);
        name[strlen(name) - 1] = '\0';
        printf("-------------------------------------------------------------\n");
        
        int status = deleteRecord(&start, name);
    
        if (status == TRUE)
        {
            print_menu("Record(s) Deleted.");
        }
        else
        {
            print_menu("No such record found.");
        }
    }
}

/*****************************************************************************
*
* Function name:        option3
*
* DESCRIPTION:          runs the specifics for modifyRecord
*
* Parameters:           none
*
* Return values:        none
*
*****************************************************************************/

void option3()
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] option3 called\n");
        printf("\n");
    }
    
    int number_of_matches = 0;
    if (start == NULL)
    {
        print_menu("[ERROR]: There's no one in your AddressBook to change!");
    }
    else
    {
        if (debug == FALSE)
        {
            system("clear");
        }
        
        char name[100] = "";
        char* address;
        char telnumber[100] = "";
        
        printf("[Editing record...]------------------------------------------\n");
        printf("Name: ");
        fgets(name, 100, stdin);
        printf("Address (multi-line input, press \"enter\" twice to complete):\n");
        address = getfield();
        printf("Phone Number: ");
        fgets(telnumber, 100, stdin);
        name[strlen(name) - 1] = '\0';
        telnumber[strlen(telnumber) - 1] = '\0';
        printf("-------------------------------------------------------------\n");
        
        number_of_matches = modifyRecord(start, name, address, telnumber);
        
        if (number_of_matches > 0)
        {
            print_menu("Record info modified.");
        }
        else
        {
            print_menu("No matching records found, no records modified.");
        }
    }
}

/*****************************************************************************
*
* Function name:        option4
*
* DESCRIPTION:          runs the specifics for printRecord
*
* Parameters:           none
*
* Return values:        none
*
*****************************************************************************/

void option4()
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] option4 called\n");
        printf("\n");
    }
    
    int number_of_matches = 0;
    char c;
    if (start == NULL)
    {
        print_menu("[ERROR]: You have no one to look up!");
    }
    else 
    {
        if (debug == FALSE)
        {
            system("clear");
        }
        
        char name[100] = "";
        
        printf("[Searching for record...]------------------------------------\n");
        printf("Name: ");
        fgets(name, 100, stdin);
        name[strlen(name) - 1] = '\0';
        printf("-------------------------------------------------------------\n");
        
        while(c != '\n')
        {
            if (debug == FALSE)
            {
                system("clear");
            }
    
            number_of_matches = printRecord(start, name);
            printf("%d matching record(s) found.\n", number_of_matches);
            printf("[Hit enter twice in a row to return to the main menu.]-------\n");
            printf(": ");
            
            c = fgetc(stdin);
            while(fgetc(stdin) != '\n')
            {
            }
        }
        print_menu("List Closed.");
    }
}

/*****************************************************************************
*
* Function name:        option5
*
* DESCRIPTION:          runs the specifics for printAllRecords
*
* Parameters:           none
*
* Return values:        none
*
*****************************************************************************/

void option5()
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] option5 called\n");
        printf("\n");
    }
    
    char c;
    if (start == NULL)
    {
        print_menu("[ERROR]: You have no one to look up!");
    }
    else 
    {
        while(c != '\n')
        {
            if (debug == FALSE)
            {
                system("clear");
            }

            printAllRecords(start);
            printf("[Hit enter twice in a row to return to the main menu.]-------\n");
            printf(": ");
            
            c = fgetc(stdin);
            while(fgetc(stdin) != '\n')
            {
            }
        }
        print_menu("List Closed.");
    }
}

/*****************************************************************************
*
* Function name:        print_menu
*
* DESCRIPTION:          prints the main menu to the screen
*
* Parameters:           message - a given message to be printed between the title
*                       and options (ex. an error message)
*
* Return values:        none
*
*****************************************************************************/

void print_menu(char message[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] print_menu called\n");
        printf("message:\n%s\n", message);
        printf("\n");
    }
    
    if (debug == FALSE)
    {
        system("clear");
    }
    
    printf("-------------------------------------------------------------\n");
    printf("[AddressBook] version %s\n", version_no);
    printf("\n");
    printf("%s\n", message);
    printf("\n");
    printf("\t(1) Add a Contact\n");
    printf("\t(2) Delete a Contact\n");
    printf("\t(3) Edit a Contact\n");
    printf("\t(4) View a Contact's Info\n");
    printf("\t(5) List All Contacts\n");
    printf("\t(6) Exit\n");
    printf("\n");
    printf("Select any one of the options above by entering the number next to it.\n");
}

/*****************************************************************************
*
* Function name:        getint
*
* DESCRIPTION:          collects a validated integer that is above zero from user
*                       input
*
* Parameters:           str - a message printed before input
*                       usage - makes the getint function multipurpose
*                           0 - getting an integer normally
*                           1 - getting an integer for the main menu input
*
* Return values:        input - a validated integer
*
*****************************************************************************/

int getint(char str[100], int usage)
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] getint called\n");
        printf("str:\n%s\n", str);
        printf("usage:\n%d\n", usage);
        printf("\n");
    }
    
    int input;
    int valid = FALSE;
    while (valid == FALSE)
    {
        printf("%s", str);

        if(fscanf(stdin,"%d", &input)) 
        {
            if(fgetc(stdin) == '\n')
            {
                if(input >= 0)
                {
                    valid = TRUE;
                }
                else
                {
                    if (usage == 0)
                    {
                        printf("[ERROR]: Please enter a number 0 or above.\n");
                    }
                    else if (usage == 1)
                    {
                        print_menu("[ERROR]: Please enter a number 0 or above.");
                    }
                }
            }
            else
            {
                while(fgetc(stdin) != '\n')
                {
                }
                if (usage == 0)
                {
                    printf("[ERROR]: Please enter a valid number.\n");
                }
                else if (usage == 1)
                {
                    print_menu("[ERROR]: Please enter a valid number.");
                }
            }
        }
        else
        {
            while(fgetc(stdin) != '\n')
            {
            }
            if (usage == 0)
            {
                printf("[ERROR]: Please enter a valid number.\n");
            }
            else if (usage == 1)
            {
                print_menu("[ERROR]: Please enter a valid number.");
            }
        }
    }
    return input;
}

/*****************************************************************************
*
* Function name:        getfield
*
* DESCRIPTION:          collects a multi-line string of input, until enter is
*                       pressed twice
*
* Parameters:           none
*
* Return values:        storage - a multi-line string
*
*****************************************************************************/

char* getfield()
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] getfield called\n");
        printf("\n");
    }
    
    char *storage = malloc(sizeof(char) * 1000);
    char bigbuffer[1000] = "";
    char buffer[100] = "";
    int reading_input = TRUE;

    while(reading_input == TRUE)
    {
        fgets(buffer, 100, stdin);

        if(strcmp(buffer, "\n") != 0)
        {
            strcat(bigbuffer, buffer);
        }
        else
        {
            reading_input = FALSE;
            strcat(storage, "\0");
        }
    }
    bigbuffer[strlen(bigbuffer) - 1] = '\0';

    strcpy(storage, bigbuffer);

    return storage;
}

/*****************************************************************************
*
* Function name:        printRecord
*
* DESCRIPTION:          given a location for an array of records, prints out all
*                       records with a matching name, and their information
*
* Parameters:           start - a given location for an array of records
*                       name - a give name (to be searched for)
*
* Return values:        counter - the number of records found with matching name
*
*****************************************************************************/

int printRecord (struct record *start, char name[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] printRecord called\n");
        printf("name:\n%s\n", name);
        printf("\n");
    }
    
    printf("[Finding records...]-----------------------------------------\n");
    
    int counter = 0;
    struct record *current;
    current = start;

    if (start == NULL)
    {
        printf("[ERROR]: You do not have any records in your addressbook!\n");
        counter = ERROR;
    }
    else
    {
        while(current != NULL)
        {
            if (strcmp(current->name, name) == 0)
            {
                printf("(> %s <)\n", current->name);
                printf("[Address]:\n%s\n", current->address);
                printf("[Year of Birth]: %d\n", current->yearofbirth);
                printf("[Tel Number]: %s\n", current->telno);
                printf("-------------------------------------------------------------\n");
                counter++;
            }

            current = current->next;
        }
    }

    return counter;
}

/*****************************************************************************
*
* Function name:        printAllRecords
*
* DESCRIPTION:          given a location for an array of records, prints out all
*                       records and their information
*
* Parameters:           start - a given location for an array of records
*
* Return values:        none
*
*****************************************************************************/

void printAllRecords(struct record *start)
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] printAllRecords called\n");
        printf("\n");
    }
    
    printf("[Listing all records...]-------------------------------------\n");
    
    struct record *current;
    current = start;

    if (current == NULL)
    {
        printf("[ERROR]: You do not have any records in your addressbook!\n");
    }
        else
        {
            while(current != NULL)
            {
                printf("(> %s <)\n", current->name);
                printf("[Address]:\n%s\n", current->address);
                printf("[Year of Birth]: %d\n", current->yearofbirth);
                printf("[Tel Number]: %s\n", current->telno);
                printf("-------------------------------------------------------------\n");

                current = current->next;
            }
        }
}
