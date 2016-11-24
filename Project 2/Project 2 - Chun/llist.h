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
 * FILE:            llist.h
 *
 * DESCRIPTION:     header file for a declaration of a linked list of records
 *
 *****************************************************************************************/

#include "record.h"

//I assume I can define something like this here to control debug mode for all cpp files
//#define DEBUG

class llist
{
    friend std::ostream & operator<<(std::ostream&, llist&);
    
    private:
        record * start;
        char filename[16];
    
        int readfile();
        int writefile();
        record * reverse(record *);
        void cleanup();
    
    public:
        llist( );
        llist(char []);
        ~llist( ); //what's this? -- the deconstructor: put something like frees in here
        int addRecord(char[], char[], int, char[]);
        int printRecord(char [ ]);
        int modifyRecord(char[], char[], char[]);
        void printAll();
        int deleteRecord(char []);
        void reverse();
    
        int isEmpty(); //you said I could add this for user convenience.
    
};
