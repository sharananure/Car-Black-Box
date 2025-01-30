/*
 * File:   internal_eeprom_store.c
 * Author: shara
 *
 * Created on 16 January, 2025, 9:29 AM
 */

#include <xc.h>
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"
#include "black_box.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"

unsigned int address = 0x00;
unsigned int event_count = 0;
unsigned int stored_event_index = 0;

void external_eeprom_store(void)
{
    unsigned int temp = address;
    event_count++;
    
    // If event count exceeds 10, overwrite older events
    if(event_count > 10)
    {
        event_count = 10;
        address = 0;
        read_add = 12;

        // Shift stored events to make room for the latest event
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 12; j++)
            {
                write_external_eeprom(address++, read_external_eeprom(read_add++)); 
            }
        }
    }
    
    // Write timestamp to EEPROM
    for(int i = 0; i < 8; i++)
    {
        if(i == 2 || i == 5)  // Skip separators (':' or '-')
        {
            ///continue;
        }
        write_external_eeprom(address++, time[i]); 
    }
    
    // Write event type to EEPROM
    for(int i = 0; i < 2; i++)
    {
        write_external_eeprom(address++, event[event_index][i]); 
    }
    
    // Write speed data to EEPROM
    write_external_eeprom(address++, (speed / 10) + '0'); // Store tens digit
    write_external_eeprom(address++, (speed % 10) + '0'); // Store units digit
}
