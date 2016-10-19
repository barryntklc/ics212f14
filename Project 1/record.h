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
* FILE:             record.h
*
* DESCRIPTION:      This file contains struct definition for a "record"
*
*****************************************************************************/

struct record
{
    char name[25];
    char address[80];
    int yearofbirth;
    char telno[15];
    struct record* next;
};

