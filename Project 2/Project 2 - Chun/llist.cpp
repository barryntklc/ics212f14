/******************************************************************************************
 *
 * NAME:                Barryn Chun
 *
 * HOMEWORK:            Project 2
 *
 * CLASS:               ICS 212
 *
 * INSTRUCTOR:          Ravi Narayan
 *
 * DATE:                November 27, 2014
 *
 * FILE:                llist.cpp
 *
 * DESCRIPTION:         C++ file containing the function definitions for the llist class
 *
  *****************************************************************************************/

#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <fstream>

#include "llist.h"

/******************************************************************************************
 *
 * Function name:       operator<<
 *
 * DESCRIPTION:         allows llist to be printed out with the << operator
 *
 * Parameters:          stream - an output stream
 *                      list - a reference to a linked list
 *
 * Return values:       stream - the output stream
 *
 *****************************************************************************************/

std::ostream & operator<<(std::ostream& stream, llist& list)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] operator<< called\n";
    std::cout << "\n";
#endif
    
    record * current = list.start;
    
    stream << "[Listing all contacts...]--------------------------------------------------" << '\n';
    
    while (current != 0)
    {
        stream << '\n';
        stream << "(> " << current->name << " <)" << '\n';
        stream << "[Address]" << '\n';
        stream << current->address << '\n';
        stream << "[Birth Year]" << '\n';
        stream << current->yearofbirth << '\n';
        stream << "[Phone #]" << '\n';
        stream << current->telno << '\n';
        
        current = current->next;
    }
    
    stream << '\n' << "---------------------------------------------------------------------------" << '\n';
    stream << "[Press enter to return to the main menu...]--------------------------------" << '\n';
    
    return stream;
}

/******************************************************************************************
 *
 * Function name:       readfile
 *
 * DESCRIPTION:         gets data from a file, and adds records to the list with 
 *                      corresponding data
 *
 * Parameters:          none
 *
 * Return values:       true if successful, false otherwise
 *
 *****************************************************************************************/

int llist::readfile()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] readfile called\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    
    std::ifstream file;
    
    std::string name;
    std::string address_input;
    std::string address;
    int yearofbirth;
    std::string telno;
    
    int address_input_status = false;
    int exit_status = false;
    
    try
    {
        file.open(filename);
     
        if (file.peek() != EOF)
        {
        
            while (exit_status == false)
            {
                name = "";
                address = "";
                yearofbirth = 0;
                telno = "";
                address_input_status = false;
                
                getline(file, name); //GET NAME
        
                while(address_input_status == false) //GET ADDRESS
                {
            
                    getline(file, address_input);
            
                    if (address_input.compare(std::string("")) == 0)
                    {
                        if (address != "")
                        {
                            address.erase(address.end() - 1);
                        }
                        address_input_status = true;
                    }
                    else
                    {
                        address.append(address_input);
                        address.append("\n");
                    }
                }
                
                file >> yearofbirth; //GET YOB
            
                file.ignore(); //removes the return space after YOB
            
                getline(file, telno); //GET TELNO
            
                //CONVERT
                
                char * name_array = new char[name.size() + 1];
                std::copy(name.begin(), name.end(), name_array);
                name_array[name.size()] = '\0';
                
                char * address_array = new char[address.size() + 1];
                std::copy(address.begin(), address.end(), address_array);
                address_array[address.size()] = '\0';
                
                char * telno_array = new char[telno.size() + 1];
                std::copy(telno.begin(), telno.end(), telno_array);
                telno_array[telno.size()] = '\0';
                
                //ADD
                addRecord(name_array, address_array, yearofbirth, telno_array);
                
                if (file.peek() == EOF) //CHECK IF NEXT CHAR IS EOF
                {
                    exit_status = true;
                }
            
    #ifdef DEBUG
                std::cout << "Record " << name << " read from file:" << '\n';
                std::cout << "address - " << address << '\n';
                std::cout << "yob - " << yearofbirth << '\n';
                std::cout << "telno - " << telno << '\n';
                std::cout << "exit status - " << exit_status << '\n';
    #endif
            }
        }
        
        file.close();
        returnval = true;
    }
    catch (std::ifstream::failure e)
    {
        returnval = false;
        std::cout << "No save file found." << '\n';
    }
    
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       writefile
 *
 * DESCRIPTION:         writes data to a savefile
 *
 * Parameters:          none
 *
 * Return values:       true if successful, false otherwise
 *
 *****************************************************************************************/

int llist::writefile()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] writefile called\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    
    record * current = start;
    std::ofstream file;
    
    try
    {
        file.open(filename);
        std::cout << "Saving contacts to " << filename << "..." << '\n';
        while (current != 0)
        {
            file << current->name << '\n';
            file << current->address << '\n' << '\n';
            file << current->yearofbirth << '\n';
            file << current->telno << '\n';
            
            current = current->next;
        }
        std::cout << "Save complete." << '\n';
        
        file.close();
        returnval = true;
    }
    catch (std::ofstream::failure e)
    {
        returnval = false;
        
    }
    
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       reverse
 *
 * DESCRIPTION:         recursive function that reverses the linked list
 *
 * Parameters:          start - a given record
 *
 * Return values:       start - a new starting point at the end of the list
 *                      new_start - a new starting point
 *
 *****************************************************************************************/

record * llist::reverse(record * start)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] reverse (recursive) called\n";
    std::cout << "\n";
#endif
    
    record * new_start = 0; //a new start
    record * current = 0;
    record * returnval = 0;
    
    if (start->next == 0)
    {
        returnval = start;
    }
    else
    {
        new_start = reverse(start->next);
        
        current = new_start;
        while (current->next != 0)
        {
            current = current->next;
        }
        start->next = 0; //sets next to zero so the list will not accidentally loop
        current->next = start;
        
        returnval = new_start;
    }
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       cleanup
 *
 * DESCRIPTION:         removes all records from the list
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void llist::cleanup()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] cleanup called\n";
    std::cout << "\n";
#endif
    
    record * removal;
    
    while(start != 0)
    {
        removal = start;
        start = start->next;
        delete(removal);
    }
}

//PUBLIC FUNCTIONS

/******************************************************************************************
 *
 * Function name:       llist
 *
 * DESCRIPTION:         constructor for llist, sets filename to load to "save.txt"
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

llist::llist()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] llist constructor called\n";
    std::cout << "\n";
#endif
    
    std::string FILENAME("save.txt");
    FILENAME.copy(filename, 16, 0);
    
    //readfile filename
    llist::readfile();
}

/******************************************************************************************
 *
 * Function name:       llist
 *
 * DESCRIPTION:         constructor, sets filename to load to a given filename
 *
 * Parameters:          filename - a given file name
 *
 * Return values:       none
 *
 *****************************************************************************************/

llist::llist(char filename[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] llist constructor called\n";
    std::cout << "filename: " << filename << "\n";
    std::cout << "\n";
#endif
    
    std::string FILENAME(filename);
    FILENAME.copy(this->filename, 16, 0);
    
    //readfile filename
    llist::readfile();
}

/******************************************************************************************
 *
 * Function name:       ~llist
 *
 * DESCRIPTION:         deconstructor (called automatically)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

llist::~llist()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] llist deconstructor called\n";
    std::cout << "\n";
#endif
    
    writefile();
    
    cleanup();
    
}

/******************************************************************************************
 *
 * Function name:       addRecord
 *
 * DESCRIPTION:         adds a record to the linked list
 *
 * Parameters:          name - a given name
 *                      address - a given address
 *                      yob - a given birth year
 *                      telno - a given telephone number
 *
 * Return values:       true if a record is successfully added
 *
 *****************************************************************************************/

int llist::addRecord(char name[], char address[], int yob, char telno[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] addRecord called\n";
    std::cout << "name: " << name << "\n";
    std::cout << "address: " << address << "\n";
    std::cout << "yob: " << yob << "\n";
    std::cout << "telno: " << telno << "\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    std::string NAME(name);
    std::string ADDRESS(address);
    std::string TELNO(telno);
    
    if (this->start == 0) //if no record exists
    {
        this->start = new record;
        
        NAME.copy(this->start->name, 25, 0);
        ADDRESS.copy(this->start->address, 80, 0);
        this->start->yearofbirth = yob;
        TELNO.copy(this->start->telno, 15, 0);
        this->start->next = 0;
        
        returnval = true;
    }
    else //if a record already exists
    {
        record * current = this->start;
        int exit_status = false;
        
        while (exit_status == false)
        {
            if (current->next != 0) //if there is another record
            {
                current = current->next;
            }
            else //if there isn't another record
            {
                current->next = new record;
                current = current->next;
                
                NAME.copy(current->name, 25, 0);
                ADDRESS.copy(current->address, 80, 0);
                current->yearofbirth = yob;
                TELNO.copy(current->telno, 15, 0);
                current->next = 0;
                exit_status = true;
            }
        }
        
        returnval = true;
    }
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       deleteRecord
 *
 * DESCRIPTION:         deletes all records in the linked list with a given name
 *
 * Parameters:          name - a given name
 *
 * Return values:       true if a matching record is found and deleted, false otherwise
 *
 *****************************************************************************************/

int llist::deleteRecord(char name[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] deleteRecord called\n";
    std::cout << "name: " << name << "\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    
    record * previous = 0;
    record * removal = 0;
    record * current = this->start;
    
    if (this->start == 0) //if no record exists
    {
        std::cout << "[ERROR]: list is empty" << '\n';
        returnval = false;
    }
    else //if a record already exists
    {
        while (current != 0)
        {
            while ((current != 0) && (strcmp(name, current->name) == 0))
            {
                if (current == start)
                {
                    removal = start;
                    start = start->next;
                    
                    delete(removal);
                    
                    previous = start;
                    current = start;
                    
                    returnval = true;
                }
                else
                {
                    removal = current;
                    previous->next = current->next;
                    current = previous->next;
                    
                    delete(removal);
                    
                    returnval = true;
                }
            }
            previous = current;
            if (current != 0)
            {
                current = current->next;
            }
        }
    }
    
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       modifyRecord
 *
 * DESCRIPTION:         edits all records in the linked list with a given name using the
 *                      given details
 *
 * Parameters:          name - a given name
 *                      address - a given address
 *                      telno - a given telephone number
 *
 * Return values:       0 if list is empty, number above 0 if something is found
 *
 *****************************************************************************************/

int llist::modifyRecord(char name[], char address[], char telno[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] modifyRecord called\n";
    std::cout << "name: " << name << "\n";
    std::cout << "address: " << address << "\n";
    std::cout << "telno: " << telno << "\n";
    std::cout << "\n";
#endif
    
    int returnval = 0;
    
    std::string NAME(name);
    std::string ADDRESS(address);
    std::string TELNO(telno);
    
    if (this->start == 0) //if no record exists
    {
        std::cout << "[ERROR]: list is empty" << '\n';
        returnval = 0;
    }
    else
    {
        record * current = start;
        
        int counter = 0;
        
        while (current != 0)
        {
            
            if (strcmp(name, current->name) == 0)
            {
                NAME.copy(current->name, 25, 0);
                ADDRESS.copy(current->address, 80, 0);
                TELNO.copy(current->telno, 15, 0);
                
                counter++;
            }
            
            current = current->next;
        }
        returnval = counter;
    }
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       printRecord
 *
 * DESCRIPTION:         print all records with a given name to the screen
 *
 * Parameters:          name - a given name
 *
 * Return values:       0 if list is empty, number above 0 if something is found
 *
 *****************************************************************************************/

int llist::printRecord(char name[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] printRecord called\n";
    std::cout << "name: " << name << "\n";
    std::cout << "\n";
#endif
    
    int returnval = 0;
    
    if (this->start == 0) //if no record exists
    {
        std::cout << "[ERROR]: list is empty" << '\n';
        returnval = 0;
    }
    else
    {
        record * current = start;
        
        int counter = 0;
        
        std::cout << "[Listing matching contacts...]---------------------------------------------" << '\n';
        while (current != 0)
        {
            if (strcmp(name, current->name) == 0)
            {
                std::cout << '\n';
                std::cout << "(> " << current->name << " <)" << '\n';
                std::cout << "[Address]" << '\n';
                std::cout << current->address << '\n';
                std::cout << "[Birth Year]" << '\n';
                std::cout << current->yearofbirth << '\n';
                std::cout << "[Phone #]" << '\n';
                std::cout << current->telno << '\n';
                
                counter++;
            }
            current = current->next;
        }
        returnval = counter;
        std::cout << '\n' << "---------------------------------------------------------------------------" << '\n';
        std::cout << counter << " matching contact(s) found." << '\n';
        std::cout << "[Press enter to return to the main menu...]--------------------------------" << '\n';
    }
    
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       printAll
 *
 * DESCRIPTION:         backup function to print everything in the linked list
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void llist::printAll()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] printAll called\n";
    std::cout << "\n";
#endif
    
    if (this->start == 0) //if no record exists
    {
        std::cout << "[ERROR]: list is empty" << '\n';
    }
    else
    {
        record * current = start;
        
        std::cout << "[Listing all contacts...]--------------------------------------------------" << '\n';
        while (current != 0)
        {
            std::cout << '\n';
            std::cout << "(> " << current->name << " <)" << '\n';
            std::cout << "[Address]" << '\n';
            std::cout << current->address << '\n';
            std::cout << "[Birth Year]" << '\n';
            std::cout << current->yearofbirth << '\n';
            std::cout << "[Phone #]" << '\n';
            std::cout << current->telno << '\n';
            
            current = current->next;
        }
        std::cout << '\n' << "---------------------------------------------------------------------------" << '\n';
        std::cout << "[Press enter to return to the main menu...]--------------------------------" << '\n';
    }
}

/******************************************************************************************
 *
 * Function name:       reverse
 *
 * DESCRIPTION:         calls the recursive reverse function
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void llist::reverse()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] reverse called\n";
    std::cout << "\n";
#endif
    
    if (start != 0)
    {
        start = reverse(start);
    }
}

/******************************************************************************************
 *
 * Function name:       isEmpty
 *
 * DESCRIPTION:         Convenience function not used anywhere in this file. Created so 
 *                      that ABook can actually check if the list is empty, so that the 
 *                      user doesn't have to enter information only to discover they can't
 *                      find/delete/edit anything because the list is empty.
 *
 * Parameters:          none
 *
 * Return values:       true if the array is empty
 *
 *****************************************************************************************/

/*
 * This is so that the user won't have to type a bunch of info in fields just to find that 
 * the list is empty.
 * (I believe I checked for this in my C version of the program anyway.)
 */

int llist::isEmpty()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] isEmpty called\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    
    if(start == 0)
    {
        returnval = true;
    }
    else
    {
        returnval = false;
    }
    return returnval;
}
