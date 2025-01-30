/*
 * File:   External_EEPROM.c
 * Author: sharan
 *
 * Created on 24 January, 2025, 8:47 AM
 */

#include <xc.h>
#include "I2C.h"
#include "External_EEPROM.h"

void write_external_eeprom(unsigned char address, unsigned char data)
{
    i2c_start(); // Start I2C communication
    i2c_write(SLAVE_WRITE_EEPROM); // Send EEPROM write command
    i2c_write(address); // Send memory address to write to
    i2c_write(data); // Send data to be written
    i2c_stop(); // Stop I2C communication
    
    for(unsigned int delay = 3000 ; delay-- ; ); // Delay for write cycle completion
}

unsigned char read_external_eeprom(unsigned char address)
{
    unsigned char data;

    i2c_start(); // Start I2C communication
    i2c_write(SLAVE_WRITE_EEPROM); // Send EEPROM write command
    i2c_write(address); // Send memory address to read from
    i2c_rep_start(); // Restart I2C for read operation
    i2c_write(SLAVE_READ_EEPROM); // Send EEPROM read command
    data = i2c_read(); // Read data from EEPROM
    i2c_stop(); // Stop I2C communication

    return data; // Return the read data
}
