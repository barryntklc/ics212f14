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
* FILE:             database.h
*
* DESCRIPTION:      This file contains the database function declarations
*                   for AddressBook
*
*****************************************************************************/

int addRecord (struct record **, char [], char [], int, char []);
int deleteRecord(struct record **, char []);
int modifyRecord (struct record *, char [], char [], char []);
int readfile(struct record **, char []);
void writefile(struct record *, char []);
void cleanup(struct record **);

