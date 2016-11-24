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
 * FILE:                TempConverter.cpp
 *
 * DESCRIPTION:         C++ rework of ABook
 *
 *****************************************************************************************/

#include <iostream>
#include <iomanip>
#include <ios>
#include <string>

#include "llist.h"

llist mylist;

char version_no[] = "2.0";

void print_menu(std::string);
void print_usage();
int main_menu();
void option1();
void option2();
void option3();
void option4();
void option5();
void option6();
int getint(std::string, int);
std::string getlines(std::string);
char * convert_string(std::string);

/******************************************************************************************
 *
 * Function name:       main
 *
 * DESCRIPTION:         the main function
 *
 * Parameters:          argc        the number of arguments
 *                      argv        a character array of arguments
 *
 * Return values:       returnval   true if the program runs
 *                                  false if arguments are incorrect
 *
 *****************************************************************************************/

int main(int argc, const char * argv[])
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] main called\n";
    std::cout << "\n";
#endif
    
    int returnval = false;
    
    if (argc == 1)
    {
        main_menu();
        returnval = true;
    }
    else
    {
        print_usage();
        returnval = false;
    }
    
    return returnval;
}

/******************************************************************************************
 *
 * Function name:       print_menu
 *
 * DESCRIPTION:         prints the menu of ABook, with an inserted message
 *
 * Parameters:          message - a message string
 *
 * Return values:       none
 *
 *****************************************************************************************/

void print_menu(std::string message)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] print_menu called\n";
    std::cout << "message:\n" << message << "\n";
    std::cout << "\n";
#else
    system("clear");
#endif
    
    std::cout << "---------------------------------------------------------------------------" << '\n';
    std::cout << "[AddressBook] version " << version_no << "\n";
    std::cout << "\n";
    std::cout << message << "\n";
    std::cout << "\n";
    std::cout << "\t(1) Add a Contact\n";
    std::cout << "\t(2) Delete a Contact\n";
    std::cout << "\t(3) Edit a Contact\n";
    std::cout << "\t(4) View a Contact's Info\n";
    std::cout << "\t(5) List All Contacts\n";
    std::cout << "\t(6) Reverse Contact List\n";
    std::cout << "\t(7) Exit\n";
    std::cout << "\n";
    std::cout << "Select any one of the options above by entering the number next to it.\n";
    
}

/******************************************************************************************
 *
 * Function name:       print_usage
 *
 * DESCRIPTION:         prints the usage errors for ABook if arguments are invalid
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void print_usage()
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] print_usage called\n";
    std::cout << "\n";
#endif
    
    std::cout << "usage:\t./ABook\n";
    std::cout << "    \t./ABook debug\n";
}

/******************************************************************************************
 *
 * Function name:       main_menu
 *
 * DESCRIPTION:         runs the main menu in a loop, collects the user's choices,
 *                      and selects an option accordingly
 *
 * Parameters:          none
 *
 * Return values:       1 (TRUE), indicating that the function has executed
 *
 *****************************************************************************************/

int main_menu()
{
    
    int exit_status = false;
    
#ifdef DEBUG
        std::cout << "\n";
        std::cout << "[DEBUG] main_menu called\n";
        std::cout << "\n";
        print_menu("Welcome! Debug Mode active.");
#else
        print_menu("Welcome!");
#endif
    
    int input = 0;
    while(exit_status == false)
    {
        input = getint(": ", 1); //REMOVE COLON
        
        if (input == 7) //exit
        {
#ifndef DEBUG
        system("clear");
#endif
            exit_status = true;
        }
        else if (input == 6) //reverse
        {
            option6();
        }
        else if (input == 5) //listall
        {
            option5();
        }
        else if (input == 4) //view
        {
            option4();
        }
        else if (input == 3) //edit
        {
            option3();
        }
        else if (input == 2) //delete
        {
            option2();
        }
        else if (input == 1) //add
        {
            option1();
        }
        else
        {
            print_menu("[ERROR]: Invalid command. Please choose from options 1-6.");
        }
    }
    return true;
}

/******************************************************************************************
 *
 * Function name:       option1
 *
 * DESCRIPTION:         data collection for option 1 (add)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option1()//add
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option1 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    std::string name;
    std::string address;
    int yob;
    std::string telno;
    
    std::cout << "[Adding new contact...]----------------------------------------------------" << '\n';
    
    std::cout << "Enter NAME: " << '\n' << ": ";
    std::getline(std::cin, name);
    
    std::cout << "Enter ADDRESS (press enter twice to continue): " << '\n';
    address = getlines(": ");
    
    std::cout << "Enter BIRTH YEAR: " << '\n'; //move colon to check valid input
    yob = getint(": ", 0);
    
    std::cout << "Enter PHONE #: " << '\n' << ": ";
    std::getline(std::cin, telno);
    
    mylist.addRecord(convert_string(name), convert_string(address), yob, convert_string(telno));
    
    print_menu("Contact added."); //TODO CHANGE
}

/******************************************************************************************
 *
 * Function name:       option2
 *
 * DESCRIPTION:         data collection for option 2 (delete)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option2()//delete
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option2 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    if (mylist.isEmpty() == true)
    {
        print_menu("You have no contacts to delete!"); //TODO CHANGE
    }
    else
    {
        std::string name;
        
        int found = false;
    
        std::cout << "[Deleting a contact...]------------------------------------------------" << '\n';
    
        std::cout << "Enter NAME to delete: ";
        std::getline(std::cin, name);
        
        found = mylist.deleteRecord(convert_string(name)); //DOES NOT DETECT NAME? wait, remove the return space.
        
        if (found == true)
        {
            print_menu("Contact(s) deleted.");
        }
        else
        {
            print_menu("No such contact found, no contacts deleted.");
        }
    }
}

/******************************************************************************************
 *
 * Function name:       option3
 *
 * DESCRIPTION:         data collection for option 3 (edit)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option3()//edit
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option3 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    if (mylist.isEmpty() == true)
    {
        print_menu("You have no contacts to edit!"); //TODO CHANGE
    }
    else
    {
        std::string name;
        std::string address;
        std::string telno;
        
        int found = false;
        
        std::cout << "[Editing a contact...]-----------------------------------------------------" << '\n';
        
        std::cout << "Enter NAME: " << '\n' << ": ";
        std::getline(std::cin, name);
        
        std::cout << "Enter ADDRESS (press enter twice to continue): " << '\n';
        address = getlines(": ");
        
        std::cout << "Enter PHONE #: " << '\n' << ": ";
        std::getline(std::cin, telno);
        
        found = mylist.modifyRecord(convert_string(name), convert_string(address), convert_string(telno));
        
        if (found == true)
        {
            print_menu("Info of contact(s) edited.");
        }
        else
        {
            print_menu("No matching contacts found, no contacts edited.");
        }
    }
}

/******************************************************************************************
 *
 * Function name:       option4
 *
 * DESCRIPTION:         data collection for option 4 (print)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option4()//print
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option4 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    if (mylist.isEmpty() == true)
    {
        print_menu("You have no contacts to look for!"); //TODO CHANGE
    }
    else
    {
        std::string name;
        
        int found = false;
        
        std::cout << "[Looking for a contact...]-------------------------------------------------" << '\n';
        
        std::cout << "Enter NAME to search for: ";
        std::getline(std::cin, name);
        
        found = mylist.printRecord(convert_string(name));
        
        getlines(": ");
        print_menu("");
    }
}

/******************************************************************************************
 *
 * Function name:       option5
 *
 * DESCRIPTION:         operations for option 5 (print all)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option5()//printAll
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option5 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    if (mylist.isEmpty() == true)
    {
        print_menu("You have no contacts to show!");
    }
    else
    {
        std::cout << mylist;
        getlines(": ");
        print_menu("");
    }
}

/******************************************************************************************
 *
 * Function name:       option6
 *
 * DESCRIPTION:         operations for option 6 (reverse)
 *
 * Parameters:          none
 *
 * Return values:       none
 *
 *****************************************************************************************/

void option6()//reverse
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] option6 called\n";
    std::cout << "\n";
#endif
    
#ifndef DEBUG
    system("clear");
#endif
    if (mylist.isEmpty() == true)
    {
        print_menu("You have no contacts to reorder!");
    }
    else
    {
        mylist.reverse();
        print_menu("Contact list reversed.");
    }
}

/******************************************************************************************
 *
 * Function name:       getint
 *
 * DESCRIPTION:         gets a valid integer for input
 *
 * Parameters:          msg - an input message
 *                      usage - what getint is to be used for (input mode)
 *                          0 - for getting a valid int in general
 *                          1 - for getting a valid int for a menu option
 *
 * Return values:       input - a validated integer
 *
 *****************************************************************************************/

int getint(std::string msg, int usage)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] getint called\n";
    std::cout << "msg: " << msg << "\n";
    std::cout << "usage: " << usage << "\n";
    std::cout << "\n";
#endif
    
    int input = 0;
    int validNumber = false;
    
    while (validNumber == false)
    {
        std::cout << msg;
        
        std::cin >> input;
        
        if (!std::cin)
        {
            if (usage == 0)
            {
                std::cout << "[ERROR]: Please enter a valid number." << '\n';
            }
            else if (usage == 1)
            {
                print_menu("[ERROR]: Invalid command. Please choose from options 1-7.");
            }
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            std::cin.ignore(INT_MAX, '\n');
            
            if (input > 0) {
                validNumber = true;
            }
            else
            {
                if (usage == 0)
                {
                    std::cout << "[ERROR]: Please provide a number greater than zero." << '\n';
                }
                else if (usage == 1)
                {
                    print_menu("[ERROR]: Invalid command. Please choose from options 1-7.");
                }
            }
        }
    }
    
    return input;
}


/******************************************************************************************
 *
 * Function name:       getlines
 *
 * DESCRIPTION:         gets multiple lines of user input
 *
 * Parameters:          msg - a message printed before user input
 *
 * Return values:       buffer - a string buffer containing total user input
 *
 *****************************************************************************************/

std::string getlines(std::string msg)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] getlines called\n";
    std::cout << "msg: " << msg << "\n";
    std::cout << "\n";
#endif
    
    std::string input = "";
    std::string buffer = "";
    
    int exit_status = false;
    
    while (exit_status == false)
    {
        std::cout << msg;
        std::getline(std::cin, input);
        
        if (input != "")
        {
            buffer.append(input);
            buffer.append("\n");
        }
        else
        {
            if (buffer != "")
            {
                buffer.erase(buffer.end() - 1);
            }
            exit_status = true;
        }
    }
    return buffer;
}

/******************************************************************************************
 *
 * Function name:       convert_string
 *
 * DESCRIPTION:         converts a string to a (character *) or (character[])
 *
 * Parameters:          string - a string object
 *
 * Return values:       chararray - a char pointer
 *
 *****************************************************************************************/

char * convert_string(std::string string)
{
#ifdef DEBUG
    std::cout << "\n";
    std::cout << "[DEBUG] convert_string called\n";
    std::cout << "string: " << string << "\n";
    std::cout << "\n";
#endif
    
    char * chararray = new char[string.size() + 1];
    std::copy(string.begin(), string.end(), chararray);
    chararray[string.size()] = '\0';
    
    return chararray;
}

