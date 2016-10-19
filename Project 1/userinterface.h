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
* FILE:             userinterface.h
*
* DESCRIPTION:      This file contains the main/GUI/user-input-checking 
*                   function declarations for AddressBook
*
*****************************************************************************/

int main_menu();
void option1();
void option2();
void option3();
void option4();
void option5();
void print_menu();
int getint(char *, int);
int printRecord (struct record *, char []);
char* getfield();
void printAllRecords(struct record *);

extern int debug;
