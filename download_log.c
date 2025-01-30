/*
 * File:   download_log.c
 * Author: shara
 *
 * Created on 25 January, 2025, 10:34 AM
 */


#include <xc.h>
#include "black_box.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"
#include "UART.h"

void download_log(void)
{
    // Check if there is any event data available
    if(event_count == 0)
    {
        clcd_print(" NO DATA FOUND...", LINE1(0)); // Display message on LCD
        for(unsigned long long int delay = 100000; delay--;); // Small delay for user readability
        state = e_main_menu; // Return to main menu
        CLEAR_DISP_SCREEN; // Clear LCD screen
        puts("\n\rNO DATA FOUND...\n\r"); // Print message to serial output
        return; // Exit function
    }
    
    read_event(); // Read event data from memory
    CLEAR_DISP_SCREEN; // Clear display before showing download status
    
    clcd_print("Downloading..." ,LINE1(0)); // Display downloading message
    for(unsigned long long int delay = 100000; delay--;); // Delay to simulate downloading process
    
    puts("  TIME   EV SP\n\n\r"); // Print column headers to serial output
    
    // Iterate through all events and print them via UART
    for(int i = 0; i < event_count; i++)
    {
        puts(read_ev[i]); // Send event data via UART
        puts("\n\r"); // New line for better readability
    }
    
    CLEAR_DISP_SCREEN; // Clear display after download
    state = e_main_menu; // Return to main menu
}
