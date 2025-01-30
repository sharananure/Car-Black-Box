/*
 * File:   main.c
 * Author: SHARAN
 *
 * Created on 12 February 2025, 5:40 PM
 */

// Include necessary header files
#include <xc.h>
#include "black_box.h"       // Project-specific definitions
#include "adc.h"             // ADC module functions
#include "clcd.h"            // Character LCD functions
#include "matrix_keypad.h"   // Keypad input handling
#include "UART.h"            // UART communication functions
#include "DS1307.h"          // Real-Time Clock (RTC) functions
#include "I2C.h"             // I2C communication protocol
#include "External_EEPROM.h" // External EEPROM functions

// Global variables for time and date storage
unsigned char clock_reg[3];  // Stores raw hour, minute, second from RTC
unsigned char calender_reg[4]; // Stores raw date, month, year from RTC (not used in current code)
unsigned char time[9];       // Formatted time string (HH:MM:SS)
unsigned char date[11];      // Formatted date string (not used in current code)

State_t state;               // Current system state
unsigned char key = 0;       // Stores the last pressed key value

// Function to initialize system components
void init_config() 
{
    state = e_dashboard;     // Initial state is dashboard view
    
    // Initialize peripherals
    init_matrix_keypad();    // Set up keypad for input
    init_clcd();             // Initialize character LCD
    init_adc();              // Configure ADC for sensor readings
    init_uart();             // Set up UART for serial communication
    init_i2c();              // Initialize I2C communication
    init_ds1307();           // Configure DS1307 RTC module
    
    CLEAR_DISP_SCREEN;       // Macro to clear LCD display
}

// Main program loop
void main(void) 
{
    init_config();           // Initialize system configuration
  
    while(1) 
    {               // Infinite loop for continuous operation
        get_time();          // Update current time from RTC
        
        // Detect key press (state change detection)
        key = read_switches(STATE_CHANGE);
        
        // State machine handling
        switch (state) 
        {
            case e_dashboard:
                // Display main dashboard with sensor data
                view_dashboard();
                break;
            
            case e_main_menu:
                // Show main menu options on LCD
                display_main_menu();
                break;
            
            case e_view_log:
                // Display stored logs from EEPROM
                view_log();
                break;
                 
            case e_download_log:
                // Transfer logs via UART to external device
                download_log();
                break;
                
            case e_clear_log:
                // Erase all logs from EEPROM
                clear_log();
                break;
                         
            case e_set_time:
                // Set RTC time through keypad interface
                set_time();
                break;      
        }    
    } 
}

// Function to get current time from RTC and format it
void get_time(void) 
{
    // Read raw time values from DS1307
    clock_reg[0] = read_ds1307(HOUR_ADDR);  // Hour register
    clock_reg[1] = read_ds1307(MIN_ADDR);   // Minute register
    clock_reg[2] = read_ds1307(SEC_ADDR);   // Second register

    // Convert hour to 12-hour format if necessary
    if (clock_reg[0] & 0x40)    // Check 12-hour format flag (bit 6)
    {  
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);  // Extract 12-hour tens digit
        time[1] = '0' + (clock_reg[0] & 0x0F);         // Extract 12-hour units digit
    } else 
    {
        // 24-hour format conversion
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);  // Extract 24-hour tens digit
        time[1] = '0' + (clock_reg[0] & 0x0F);         // Extract 24-hour units digit
    }
    
    // Build time string with separators
    time[2] = ':';  // Hour-minute separator
    
    // Convert and format minutes
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);  // Minute tens digit
    time[4] = '0' + (clock_reg[1] & 0x0F);         // Minute units digit
    time[5] = ':';  // Minute-second separator
    
    // Convert and format seconds
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);  // Second tens digit
    time[7] = '0' + (clock_reg[2] & 0x0F);         // Second units digit
    time[8] = '\0'; // Null terminator for string
}