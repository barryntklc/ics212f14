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
* FILE:             database.c
*
* DESCRIPTION:      This file contains the database function definitions for 
*                   AddressBook
*
*****************************************************************************/

#import <stdio.h>
#import <string.h>
#import <stdlib.h>
#import "record.h"
#import "userinterface.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

/*****************************************************************************
*
* Function name:        addRecord
*
* DESCRIPTION:          given a location for an array of records, makes space for
*                       a new record at the end of the array, and copies info into
*                       the space from the given fields
*
* Parameters:           start - a given location for an array of records
*                       name - a given name
*                       address - a given address
*                       yearofbirth - a given year of birth
*                       telno - a given telephone number
*
* Return values:        found - whether or not a matching name was found
*
*****************************************************************************/

int addRecord (struct record **start, char name[], char address[], int yearofbirth, char telno[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] addRecord called\n");
        printf("name:\n%s\n", name);
        printf("address:\n%s\n", address);
        printf("yearofbirth:\n%d\n", yearofbirth);
        printf("telno:\n%s\n", telno);
        printf("\n");
    }
    
    struct record *current;

    if (*start == NULL)
    {
        (*start) = (struct record *) malloc(sizeof(struct record));
        strcpy((*start)->name, name);
        strcpy((*start)->address, address);
        (*start)->yearofbirth = yearofbirth;
        strcpy((*start)->telno, telno);
    }
    else
    {
        current = *start;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = (struct record *) malloc(sizeof(struct record));
        current = current->next;
        strcpy(current->name, name);
        strcpy(current->address, address);
        current->yearofbirth = yearofbirth;
        strcpy(current->telno, telno);
    }
    return 0;
}

/*****************************************************************************
*
* Function name:        deleteRecord
*
* DESCRIPTION:          given a location for an array of records, takes each
*                       record with a matching name and frees its space
*
* Parameters:           start - a given location for an array of records
*                       name - a given name (to be searched for)
*
* Return values:        found - whether or not a matching name was found
*
*****************************************************************************/

int deleteRecord(struct record **start, char name[])
{   
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] deleteRecord called\n");
        printf("name:\n%s\n", name);
        printf("\n");
    }
    
    int returnval = 0;
    int found = FALSE;
    
    struct record *previous;
    struct record *current;
    struct record *delete;
    previous = *start;
    current = *start;
    
    if ((*start) == NULL)
    {
        returnval = ERROR;
    }
    else
    {
        while(current != NULL)
        {
            while(current != NULL && strcmp(current->name, name) == 0)
            {
                if (current == *start)
                {
                    (*start) = (*start)->next;
                }
                previous->next = current->next;
                delete = current;
                current = previous->next;
                free(delete);
                found = TRUE;
            }
            previous = current;
            if (current != NULL) 
            {
                current = current->next;
            }
        }
    }
    
    return found;
}

/*****************************************************************************
*
* Function name:        modifyRecord
*
* DESCRIPTION:          given a location for an array of records, takes each
*                       record with a matching name and sets its address and tel
*                       number to those given
*
* Parameters:           start - a given location for an array of records
*                       name - a given name (to be searched for)
*                       address - a given address
*                       telno - a given telephone number
*
* Return values:        counter - the number of records found with matching name
*
*****************************************************************************/

int modifyRecord (struct record *start, char name[], char address[], char telno[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] modifyRecord called\n");
        printf("name:\n%s\n", name);
        printf("address:\n%s\n", address);
        printf("telno:\n%s\n", telno);
        printf("\n");
    }
    
    struct record *current;
    current = start;
    int counter = 0;
    
    if (start == NULL)
    {
        counter = ERROR;
    }
    else
    {
        while(current != NULL)
        {
            if (strcmp(current->name, name) == 0)
            {
                strcpy(current->address, address);
                strcpy(current->telno, telno);
                counter++;
            }
                
            current = current->next;
        }
    }
    
    return counter;
}

/*****************************************************************************
*
* Function name:        cleanup
*
* DESCRIPTION:          given a location for an array of records, takes each
*                       record and frees it
*
* Parameters:           start - a given location for an array of records
*
* Return values:        none
*
*****************************************************************************/

void cleanup(struct record **start)
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] cleanup called\n");
        printf("\n");
    }

    struct record *current;
    struct record *delete;
    current = *start;

    if (*start != NULL)
    {
        while(current != NULL)
        {
            delete = current;
            current = current->next;
            free(delete);
        }
    }
}

/*****************************************************************************
*
* Function name:        readfile
*
* DESCRIPTION:          given a location for an array of records and a filename, 
*                       allocates space for and copies each set of information
*                       from the file to the location
*
* Parameters:           start - a given location for an array of records
*                       filename - a given filename
*
* Return values:        1 (TRUE), indicating that the function has executed
*
*****************************************************************************/

int readfile(struct record ** start, char filename[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] readfile called\n");
        printf("filename:\n%s\n", filename);
        printf("\n");
    }
    
    FILE *file = fopen(filename,"r");
    
    struct record *current;
        
    char name[25];
    char address[80];
    int yearofbirth = 0;
    char telno[15];

    int reading_field;
    int end_of_file = FALSE;
    char finput;
    int index;
    fpos_t position;

    if (file != NULL)
    {
        while(end_of_file == FALSE)
        {
            fgetpos(file, &position);
            finput = fgetc(file);
            
            if (finput == -1)
            {
                end_of_file = TRUE;
            }
            else
            {
                
                /*Resets all fields to zero*/
                memset(name, 0, sizeof(name));
                memset(address, 0, sizeof(address));
                yearofbirth = 0;
                memset(telno, 0, sizeof(telno));
                
                fsetpos(file, &position);
                index = 0;
                fgets(name, 25, file);
                
                index = 0;
                reading_field = TRUE;
                while(reading_field == TRUE && index < sizeof(address))
                {
                    finput = fgetc(file);
                    address[index] = finput;
                    index++;
                    if (finput == 10)
                    {
                        //get the current buffer position
                        fgetpos(file, &position);
                        //if the next character is a return space
                        if (fgetc(file) == 10)
                        {
                            //indicate that we are no longer reading the address field
                            reading_field = FALSE;
                        } 
                        else 
                        {
                            //set the buffer position back to the previous
                            fsetpos(file, &position);
                        }
                    }
                }
                
                fscanf(file, "%d", &yearofbirth);
                fgetc(file); /*Removes the return space after int*/
                                
                fgets(telno, 15, file);
                
                /*Removes the return spaces from fields*/
                name[strlen(name) - 1] = '\0';
                address[strlen(address) - 1] = '\0';
                telno[strlen(telno) - 1] = '\0';
                
                if (debug == TRUE)
                {
                    printf("read Name from file: %s\n", name);
                    printf("read Address from file:\n%s", address);
                    printf("read YearofBirth from file: %d\n", yearofbirth);
                    printf("read TelNumber from file: %s\n", telno);
                    printf("\n");
                }
                
                if (*start == NULL)
                {
                    (*start) = (struct record *) malloc(sizeof(struct record));
                    strcpy((*start)->name, name);
                    strcpy((*start)->address, address);
                    (*start)->yearofbirth = yearofbirth;
                    strcpy((*start)->telno, telno);
                }
                else
                {
                    current = *start;
                    while(current->next != NULL)
                    {
                        current = current->next;
                    }
                    current->next = (struct record *) malloc(sizeof(struct record));
                    current = current->next;
                    strcpy(current->name, name);
                    strcpy(current->address, address);
                    current->yearofbirth = yearofbirth;
                    strcpy(current->telno, telno);
                }
                
            }
        }
    }
    fclose(file);
    return TRUE;
}

/*****************************************************************************
*
* Function name:        writefile
*
* DESCRIPTION:          given a location for an array of records and a filename, 
*                       writes information from that array to a file of the given 
*                       filename
*
* Parameters:           start - a given location for an array of records
*                       filename - a given filename
*
* Return values:        none
*
*****************************************************************************/

void writefile(struct record * start, char filename[])
{
    if (debug == TRUE)
    {
        printf("\n");
        printf("[DEBUG] writefile called\n");
        printf("filename:\n%s\n", filename);
        printf("\n");
    }
    
    struct record *current;
    current = start;
    FILE *file = fopen(filename,"w");
    
    while(current != NULL)
    {    
        fprintf(file, "%s\n", current->name);
        fprintf(file, "%s\n\n", current->address);
        fprintf(file, "%d\n", current->yearofbirth);
        fprintf(file, "%s\n", current->telno);
        
        current = current->next;
    }
    
    fclose(file);
}

