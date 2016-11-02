/*****************************************************************************
 *
 * NAME:             Barryn Chun
 *
 * HOMEWORK:         Homework 7b
 *
 * CLASS:            ICS 212
 *
 * INSTRUCTOR:       Ravi Narayan
 *
 * DATE:             November 7, 2014
 *
 * FILE:             header.c
 *
 * DESCRIPTION:      Contains the header struct for Assignment 7b
 *
 *****************************************************************************/

struct header_contents
{
    
    unsigned short source_port;
    unsigned short destination_port;
    unsigned long sequence_number;
    unsigned long acknowledgement_number;
    unsigned short data_offset;
    unsigned short reserved;
    
    unsigned char URG;
    unsigned char ACK;
    unsigned char PSH;
    unsigned char RST;
    unsigned char SYN;
    unsigned char FIN;
    
    unsigned short window;
    unsigned short checksum;
    unsigned short urgent_pointer;
    
};
