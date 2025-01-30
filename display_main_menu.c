/*
 * File:   display_main_menu.c
 * Author: shara
 *
 * Created on 16 January, 2025, 10:48 AM
 */

#include <xc.h>
#include "black_box.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"

// Variables to track menu navigation
unsigned int star = 0; // Indicates which line the selection star is on
unsigned int count = 0; // Tracks the current menu option index

// Menu options
char log[][13] = {"View log    ", "Clear log   ", "Download log", "Set time    "};

void display_main_menu(void)
{
    // Check if the 'down' button is pressed
    if(key == MK_SW2) // Move down in the menu
    {
        star = 1; // Move the selection star to the second line
        if(count < 3) // Ensure we don't go beyond available options
        {
            count++; // Increment menu index
        }
        key = 0; // Reset key press
    }    
    
    // Check if the 'up' button is pressed
    if(key == MK_SW1) // Move up in the menu
    {
        star = 0; // Move the selection star to the first line
        if(count > 0) // Ensure we don't go below available options
        {
             count--; // Decrement menu index
        }
        key = 0; // Reset key press
    }
    
    // Display menu with selection star on the first line
    if(star == 0) // Star on the first line
    {
        clcd_print("* ", LINE1(0)); // Star on first line
        clcd_print("  ", LINE2(0)); // Clear second line star position
        clcd_print("  ", LINE2(14)); // Clear unnecessary spaces
        clcd_print(log[count], LINE1(2)); // Print current option on first line
        clcd_print(log[count + 1], LINE2(2)); // Print next option on second line
    }
    else // Display menu with selection star on the second line
    {
        clcd_print("  ", LINE1(0)); // Clear first line star position
        clcd_print("* ", LINE2(0)); // Star on second line
        clcd_print("  ", LINE2(14)); // Clear unnecessary spaces
        clcd_print(log[count - 1], LINE1(2)); // Print previous option on first line
        clcd_print(log[count], LINE2(2)); // Print current option on second line
    }
    
    // Handle return to dashboard
    if(key == MK_SW12) // Return to dashboard
    {
        state = e_dashboard; // Set state to dashboard
        star = 0; // Reset selection star
        count = 0; // Reset menu index
        key = 0; // Reset key press
        CLEAR_DISP_SCREEN; // Clear display
    }

    // Handle selection of menu option
    if (key == MK_SW11) // Check if SW11 is pressed
    {
        CLEAR_DISP_SCREEN; // Clear display before transition
        key = 0; // Reset key press
        switch (count)  // Determine selected option
        {
            case 0:
                state = e_view_log; // Navigate to View Log
                break;
            case 1:
                state = e_clear_log; // Navigate to Clear Log
                break;
            case 2:
                state = e_download_log; // Navigate to Download Log
                break;
            case 3:
                state = e_set_time; // Navigate to Set Time
                break;
        }
    }
}
