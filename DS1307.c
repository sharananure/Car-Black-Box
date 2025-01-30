/*
 * File:   DS1307.c
 * Author: shara
 *
 * Created on 24 January, 2025, 8:35 AM
 */


#include "DS1307.h"
#include "I2C.h"
#include <xc.h>

void init_ds1307(void)
{
    unsigned char dummy;

    /* Setting the CH (Clock Halt) bit of the RTC to stop the clock */
    dummy = read_ds1307(SEC_ADDR);
    write_ds1307(SEC_ADDR, dummy | 0x80); 

    /* Setting 12-hour format */
    dummy = read_ds1307(HOUR_ADDR);
    write_ds1307(HOUR_ADDR, dummy | 0x40); 

    /* 
     * Configure Control Register of DS1307
     * Bit 7 - OUT (Output Control)
     * Bit 6 - 0 (Reserved)
     * Bit 5 - OSF (Oscillator Stop Flag)
     * Bit 4 - SQWE (Square Wave Enable)
     * Bit 3 - 0 (Reserved)
     * Bit 2 - 0 (Reserved)
     * Bit 1 - RS1 (Rate Select 1)
     * Bit 0 - RS0 (Rate Select 0)
     * 
     * Setting RS0 and RS1 to 11 to achieve SQW output at 32.768 KHz
     */ 
    write_ds1307(CNTL_ADDR, 0x93); 

    /* Clearing the CH bit to start the clock */
    dummy = read_ds1307(SEC_ADDR);
    write_ds1307(SEC_ADDR, dummy & 0x7F); 
}

void write_ds1307(unsigned char address, unsigned char data)
{
    i2c_start(); // Start I2C communication
    i2c_write(SLAVE_WRITE); // Send slave write address
    i2c_write(address); // Send register address
    i2c_write(data); // Send data to be written
    i2c_stop(); // Stop I2C communication
}

unsigned char read_ds1307(unsigned char address)
{
    unsigned char data;

    i2c_start(); // Start I2C communication
    i2c_write(SLAVE_WRITE); // Send slave write address
    i2c_write(address); // Send register address
    i2c_rep_start(); // Restart I2C communication
    i2c_write(SLAVE_READ); // Send slave read address
    data = i2c_read(); // Read data from RTC
    i2c_stop(); // Stop I2C communication

    return data; // Return the read data
}
