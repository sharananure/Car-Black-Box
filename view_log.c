/*
 * File:   view_log.c
 * Author: SHARAN
 *
 * Created on 22 January, 2025
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "black_box.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"

// Global variables
unsigned char read_ev[10][15]; // Array to store event log data
int read_add = 0, view_log_ind = 0; // Variables for address and log index
unsigned int ind; // Index variable for loop

// Function to display the event log
void view_log(void) 
{
    // If no event data is found, display a message and return to the main menu
    if(event_count == 0) 
    {
        clcd_print(" NO DATA FOUND...", LINE1(0)); // Display no data message
        for(unsigned long long int delay = 100000; delay--;); // Delay for a brief moment
        state = e_main_menu; // Change state to main menu
        CLEAR_DISP_SCREEN; // Clear the display screen
        return;
    }
    
    read_event(); // Read event data from external EEPROM
    
    // Display the event log header and current log index
    clcd_print("# TIME     EV SP", LINE1(0)); 
    clcd_putch(view_log_ind + '0', LINE2(0)); // Display the current log index
    clcd_print(read_ev[view_log_ind], LINE2(2)); // Display the current event log data
    
    // If SW2 is pressed, navigate to the next log entry
    if(key == MK_SW2) 
    {
        if(view_log_ind < ind - 1) // If there are more logs to view, increment the index
            view_log_ind++;
        key = 0; // Reset the key
    }
    
    // If SW1 is pressed, navigate to the previous log entry
    if(key == MK_SW1) 
    {
        if(view_log_ind >= 1) // If not at the first log, decrement the index
            view_log_ind--;
        key = 0; // Reset the key
    }
    
    // If SW12 is pressed, return to the main menu
    if(key == MK_SW12) 
    {
        state = e_main_menu; // Change state to main menu
        key = 0; // Reset the key
        view_log_ind = 0; // Reset the log index
        CLEAR_DISP_SCREEN; // Clear the display screen
    }
}

// Function to read event data from external EEPROM and store it in read_ev array
void read_event(void)
{
    read_add = 0; // Reset the address pointer

    // Loop through the event count to read event data
    for(ind = 0; ind < event_count; ind++)
    {
        // Loop through each character of the event log
        for(int j = 0; j < 14; j++)
        {
            // Set spaces at positions 8 and 11 for formatting
            if(j == 8 || j == 11)
            {
                read_ev[ind][j] = ' ';
            }
            else
            {
                // Read a byte from the external EEPROM and store it in read_ev array
                read_ev[ind][j] = read_external_eeprom(read_add++);
            }
        }

        // Null-terminate the event string
        read_ev[ind][14] = '\0';
    }
}
