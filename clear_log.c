/*
 * File:   clear_log.c
 * Author: shara
 *
 * Created on 25 January, 2025, 10:04 PM
 */

#include <xc.h>
#include "black_box.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"
#include "UART.h"

void clear_log(void)
{
    CLEAR_DISP_SCREEN; // Clear the display
    clcd_print(" CLEARING...", LINE1(0)); // Display clearing message
    for(unsigned long long int delay = 100000; delay--;); // Delay to show message
    
    // Reset event-related variables
    event_count = 0;
    address = 0;
    //event_store_index = 0;
    
    CLEAR_DISP_SCREEN; // Clear the display again
    state = e_main_menu; // Return to the main menu
}
