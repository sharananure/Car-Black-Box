/*
 * File:   set_time.c
 * Author: shara
 *
 * Created on 26 January, 2025, 8:09 PM
 */

#include <xc.h>
#include "black_box.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "DS1307.h"
#include "I2C.h"
#include "External_EEPROM.h"

unsigned int hrs = 0, min = 0, sec = 0;
unsigned int field = 0;
unsigned long int delay = 1000;
int flag = 0;

void update_time_field(unsigned int *value, unsigned int max)
{
    *value = (*value + 1) % max;
}

void blink_field(unsigned int field, char *time)
{
    if (field == 0) // Blink hours
    {
        time[0] = 255;
        time[1] = 255;
    }
    else if (field == 1) // Blink minutes
    {
        time[3] = 255;
        time[4] = 255;
    }
    else if (field == 2) // Blink seconds
    {
        time[6] = 255;
        time[7] = 255;
    }
}

void update_time_string(void)
{
    time[0] = (hrs / 10) + '0';
    time[1] = (hrs % 10) + '0';
    
    time[3] = (min / 10) + '0';
    time[4] = (min % 10) + '0';
    
    time[6] = (sec / 10) + '0';
    time[7] = (sec % 10) + '0';
}

void set_time(void)
{
    if (flag == 0) // Initialize time values from RTC
    {
        get_time();
        hrs = ((time[0] - '0') * 10) + (time[1] - '0');
        min = ((time[3] - '0') * 10) + (time[4] - '0');
        sec = ((time[6] - '0') * 10) + (time[7] - '0');

        clcd_print("    HH:MM:SS    ", LINE1(0)); // Display header
        clcd_print(time, LINE2(4)); // Display initial time
        flag = 1;
    }

    if (key == MK_SW2) // Change field (hours, minutes, seconds)
    {
        field = (field + 1) % 3;
        key = 0;
    }
    else if (key == MK_SW1) // Increment selected field
    {
        if (field == 0)
            update_time_field(&hrs, 24);
        else if (field == 1)
            update_time_field(&min, 60);
        else if (field == 2)
            update_time_field(&sec, 60);

        key = 0;
    }

    update_time_string();

    if (delay <= 500) // Blink the selected field
    {
        blink_field(field, time);
    }

    if (delay-- == 0)
        delay = 1000; // Reset delay counter

    clcd_print(time, LINE2(4)); // Display updated time

    if (key == MK_SW12) // Cancel time setting and return to dashboard
    {
        state = e_dashboard;
        key = 0;
        flag = 0;
        field = 0;
        CLEAR_DISP_SCREEN;
    }
    else if (key == MK_SW11) // Save time to RTC and return to dashboard
    {
        write_ds1307(HOUR_ADDR, ((hrs / 10) << 4) | (hrs % 10));
        write_ds1307(MIN_ADDR, ((min / 10) << 4) | (min % 10));
        write_ds1307(SEC_ADDR, ((sec / 10) << 4) | (sec % 10));

        state = e_dashboard;
        key = 0;
        flag = 0;
        field = 0;
        CLEAR_DISP_SCREEN;
    }
}