/******************************************************************************************
 *
 * NAME:            Barryn Chun
 *
 * HOMEWORK:        Project 2
 *
 * CLASS:           ICS 212
 *
 * INSTRUCTOR:      Ravi Narayan
 *
 * DATE:            November 27, 2014
 *
 * FILE:            record.h
 *
 * DESCRIPTION:     header file for the declaration of a record structure
 *
 *****************************************************************************************/

struct record
{
    char name[25];
    char address[80];
    int yearofbirth;
    char telno[15];
    struct record* next;
};
