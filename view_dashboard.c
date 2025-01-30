/*
 * File:   view_dashboard.c
 * Author: shara
 *
 * Created on 15 January, 2025, 9:52 AM
 */

#include <xc.h>
#include "black_box.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"

// Function prototypes
void event_set();
void speed_set();

// Event-related variables
unsigned char event[9][3] = {"ON","GN","G1","G2","G3","G4","G5","GR","C "}; // Event names
int event_index = 0; // Current event index
unsigned int collision = 0; // Flag for collision
unsigned int speed = 00; // Speed value
unsigned int data_has_changed = 1; // Data change flag

unsigned int flag1; // Flag for external EEPROM storage

// Main function to display the dashboard on LCD
void view_dashboard(void)
{
    clcd_print("TIME     EV   SPEED",LINE1(0)); // Display the labels on the first line
    
    event_set(); // Set the event based on user input
    speed_set(); // Set the speed based on ADC input
    
    // If flag1 is 0, store data to external EEPROM and set flag1 to 1
    if(flag1 == 0)
    {
        external_eeprom_store(); 
        flag1 = 1;
    }
    
    // If a key is pressed, store data to EEPROM and reset key
    if (key == MK_SW1 || key == MK_SW2 || key == MK_SW3)
    {
        external_eeprom_store(); 
        key = 0;
    }
    
    // If SW11 is pressed, clear the display and go to the main menu
    if(key == MK_SW11)
    {
        CLEAR_DISP_SCREEN;
        __delay_us(500); // Delay to allow screen clearing
        state = e_main_menu; // Change state to main menu
    }
    
    // Display the current time, event, and speed on the second line of the LCD
    clcd_print(time,LINE2(0)); // Display time
    clcd_print(" ",LINE2(8)); // Spacer for alignment
    clcd_print(event[event_index],LINE2(9)); // Display current event
    clcd_print("   ",LINE2(11)); // Spacer for alignment
    clcd_putch((speed/10) + '0',LINE2(14)); // Display the first digit of speed
    clcd_putch((speed%10) + '0',LINE2(15));  // Display the second digit of speed
}

// Function to handle event setting based on user input
void event_set(void)
{  
    // If SW1 is pressed, set event to "C " and set collision flag
    if(key == MK_SW1)
    {
        event_index = 8;
        collision = 1;
    }
    
    // If collision flag is set and SW2 or SW3 is pressed, reset event and collision
    if(collision == 1)
    {
        if(key == MK_SW2 || key == MK_SW3)
        {
            event_index = 1; // Set event to "GN"
            collision = 0; // Reset collision flag
        }
    }
    else
    {
        // If SW2 is pressed and event is not "GR", increment event index
        if(key == MK_SW2 && event_index != 7)
        {
            event_index++; // Move to the next event
        }
        // If SW3 is pressed and event index is greater than 1, decrement event index
        if(key == MK_SW3 && event_index > 1)
        {
            event_index--; // Move to the previous event
        }
    }
}

// Function to set the speed based on ADC input
void speed_set(void)
{
    speed = (read_adc(CHANNEL4))/10.24; // Convert ADC value to speed
}
