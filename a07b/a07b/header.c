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
 * DESCRIPTION:      Contains the functions for Assignment 7b
 *
 *****************************************************************************/

#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import "header.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

int printheader();
int changes();
int readfile(char []);
int writefile(char []);

struct header_contents * header = NULL;
char *filename = NULL;

int main(int argc, char *argv[])
{
    int returnval = FALSE;
    
    if (argc != 2)
    {
        printf("usage:\t./TCPEdit <file path>\n");
        
        printf("\n");
        
        returnval = ERROR;
    }
    else
    {
        //char filename[] = "test1.bin";
        filename = argv[1];
        
        printf("Searching for file \"%s\".\n", filename);
        
        if (readfile(filename) == 1)
        {
            printf("\n[HEADER CONTENTS]:\n");
            //print header info
            printheader();
            
            changes();
            
            char *addition = "_new.bin";
            char *newfilename = malloc(strlen(filename) + strlen(addition));
            strcpy(newfilename, filename);
            strncpy(strrchr(newfilename, '.'), addition, strlen(addition));
            
            //write the bin file
            writefile(newfilename);
            
            readfile(newfilename);
            
            printf("\n[CHANGES APPLIED]:\n");
            printheader();
            
            printf("\n");
            
            returnval = TRUE;
        }
        else
        {
            printf("\n[ERROR]: File not found.\n");
            
            printf("\n");
            
            returnval = ERROR;
        }
    }
    return returnval;
}

int printheader()
{
    printf("Source Port: %u\n", (header->source_port));
    printf("Destination Port: %u\n", (header->destination_port));
    printf("Sequence Number: %lu\n", (header->sequence_number));
    printf("Acknowledgement Number: %lu\n", (header->acknowledgement_number));
    //will need to split these into separate fields later
    //printf("Data Offset/Reserved/Control Bits (Int Value): %u\n", (header->doff_res_control));
    printf("Data Offset: %u\n", (header->data_offset));
    printf("Reserved: %u\n", (header->reserved));
    printf("Control Bits:\n");
    printf("\tURG: %u\n", (header->URG));
    printf("\tACK: %u\n", (header->ACK));
    printf("\tPSH: %u\n", (header->PSH));
    printf("\tRST: %u\n", (header->RST));
    printf("\tSYN: %u\n", (header->SYN));
    printf("\tFIN: %u\n", (header->FIN));
    printf("Window: %u\n", (header->window));
    printf("Checksum: %u\n", (header->checksum));
    printf("Urgent Pointer: %u\n", (header->urgent_pointer));
    return TRUE;
}

//implements changes to the header file
int changes()
{
    unsigned short buffer1 = header->source_port;
    header->source_port = header->destination_port;
    header->destination_port = buffer1;
    
    header->acknowledgement_number = header->sequence_number;
    header->sequence_number++;
    
    if(header->SYN == TRUE)
    {
        header->ACK = TRUE;
    }
    
    header->reserved = 0;
    header->data_offset = 5;
    header->window = 0;
    header->checksum = 65535;
    header->urgent_pointer = 0;
    
    return ERROR;
}

int readfile(char filename[])
{
    
    FILE * file = fopen(filename, "r");
    int returnval = 0;
    
    //check if such a file exists
    if (file == NULL)
    {
        returnval = ERROR;
    }
    else
    {
        unsigned char header_file_input[20];
        
        fread(header_file_input, 1, 20, file);
        
        header = (struct header_contents *) malloc(sizeof(struct header_contents));
        
        header->source_port = header_file_input[0];
        header->source_port = header->source_port << 8;
        header->source_port = header->source_port | header_file_input[1];
        
        header->destination_port = header_file_input[2];
        header->destination_port = header->destination_port << 8;
        header->destination_port = header->destination_port | header_file_input[3];
        
        header->sequence_number = header_file_input[4];
        header->sequence_number = header->sequence_number << 8;
        header->sequence_number = header->sequence_number | header_file_input[5];
        header->sequence_number = header->sequence_number << 8;
        header->sequence_number = header->sequence_number | header_file_input[6];
        header->sequence_number = header->sequence_number << 8;
        header->sequence_number = header->sequence_number | header_file_input[7];
        
        header->acknowledgement_number = header_file_input[8];
        header->acknowledgement_number = header->acknowledgement_number << 8;
        header->acknowledgement_number = header->acknowledgement_number | header_file_input[9];
        header->acknowledgement_number = header->acknowledgement_number << 8;
        header->acknowledgement_number = header->acknowledgement_number | header_file_input[10];
        header->acknowledgement_number = header->acknowledgement_number << 8;
        header->acknowledgement_number = header->acknowledgement_number | header_file_input[11];
        
        unsigned short doff_res_control = 0;
        
        doff_res_control = header_file_input[12];
        doff_res_control = doff_res_control << 8;
        doff_res_control = doff_res_control | header_file_input[13];
        
        //char * data_offset; [4 bits] WORKS
        header->data_offset = doff_res_control;
        unsigned short data_offset_mask = 61440;
        //printf("data_offset_mask: %u\n", data_offset_mask); //TODO REMOVE
        header->data_offset = header->data_offset & data_offset_mask;
        header->data_offset = header->data_offset >> 12;
        
        //char * reserved; [6 bits] WORKS
        header->reserved = doff_res_control;
        unsigned short reserved_mask = 4032;
        //printf("reserved_mask: %u\n", reserved_mask); //TODO REMOVE
        header->reserved = header->reserved & reserved_mask;
        header->reserved = header->reserved >> 6;
        
        unsigned short control_bit_total = 0;
        
        //char * control_bits; [6 bits] WORKS
        control_bit_total = doff_res_control;
        unsigned short control_bit_mask = 63;
        //printf("reserved_mask: %u\n", control_bits_mask); //TODO REMOVE
        control_bit_total = control_bit_total & control_bit_mask;
        
        //URG 00100000
        header->URG = control_bit_total;
        header->URG = header->URG & 32;
        header->URG = header->URG >> 5;
        //ACK 00010000
        header->ACK = control_bit_total;
        header->ACK = header->ACK & 16;
        header->ACK = header->ACK >> 4;
        //PSH 00001000
        header->PSH = control_bit_total;
        header->PSH = header->PSH & 8;
        header->PSH = header->PSH >> 3;
        //RST 00000100
        header->RST = control_bit_total;
        header->RST = header->RST & 4;
        header->RST = header->RST >> 2;
        //SYN 00000010
        header->SYN = control_bit_total;
        header->SYN = header->SYN & 2;
        header->SYN = header->SYN >> 1;
        //FIN 00000001
        header->FIN = control_bit_total;
        header->FIN = header->FIN & 1;
        
        header->window = header_file_input[14];
        header->window = header->window << 8;
        header->window = header->window | header_file_input[15];
        
        header->checksum = header_file_input[16];
        header->checksum = header->checksum << 8;
        header->checksum = header->checksum | header_file_input[17];
        
        header->urgent_pointer = header_file_input[18];
        header->urgent_pointer = header->urgent_pointer << 8;
        header->urgent_pointer = header->urgent_pointer | header_file_input[19];
        
        returnval = TRUE;
        fclose(file);
    }
    
    return returnval;
}

int writefile(char filename[])
{
    FILE * file = fopen(filename, "w");
    
    unsigned char header_file_output[20];
    
    header_file_output[0] = (header->source_port & 65280) >> 8;
    header_file_output[1] = (header->source_port & 255);
    
    header_file_output[2] = (header->destination_port & 65280) >> 8;
    header_file_output[3] = (header->destination_port & 255);
    
    header_file_output[4] = (header->sequence_number & 0xFF000000) >> 24;
    header_file_output[5] = (header->sequence_number & 0xFF0000) >> 16;
    header_file_output[6] = (header->sequence_number & 0xFF00) >> 8;
    header_file_output[7] = (header->sequence_number & 0xFF);
    
    header_file_output[8] = (header->acknowledgement_number & 0xFF000000) >> 24;
    header_file_output[9] = (header->acknowledgement_number & 0xFF0000) >> 16;
    header_file_output[10] = (header->acknowledgement_number & 0xFF00) >> 8;
    header_file_output[11] = (header->acknowledgement_number & 0xFF);
    
    unsigned short doff_res_control = 0;
    
    doff_res_control = doff_res_control | (header->data_offset << 12);
    doff_res_control = doff_res_control | (header->reserved << 6);
    
    unsigned short control_bit_total = 0;
    
    control_bit_total = control_bit_total | (header->URG << 5);
    control_bit_total = control_bit_total | (header->ACK << 4);
    control_bit_total = control_bit_total | (header->PSH << 3);
    control_bit_total = control_bit_total | (header->RST << 2);
    control_bit_total = control_bit_total | (header->SYN << 1);
    control_bit_total = control_bit_total | (header->FIN);
    
    doff_res_control = doff_res_control | (control_bit_total);
    
    header_file_output[12] = (doff_res_control & 65280) >> 8;
    header_file_output[13] = (doff_res_control & 255);
    
    header_file_output[14] = (header->window & 65280) >> 8;
    header_file_output[15] = (header->window & 255);
    
    header_file_output[16] = (header->checksum & 65280) >> 8;
    header_file_output[17] = (header->checksum & 255);
    
    header_file_output[18] = (header->urgent_pointer & 65280) >> 8;
    header_file_output[19] = (header->urgent_pointer & 255);
    
    fwrite(header_file_output, 1, 20, file);
    
    fclose(file);
    
    return TRUE;
}