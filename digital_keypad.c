// Include compiler-specific header and digital keypad definitions
#include <xc.h>
#include "digital_keypad.h"

// Function to initialize digital keypad pins
void init_digital_keypad(void)
{
    // Set TRISC register to configure specified pins as inputs
    // INPUT_PINS is a mask defining which pins are keypad inputs
    TRISC = TRISC | INPUT_PINS;  // Using bitwise OR to preserve existing TRISC settings
}

// Function to read keypad state with different detection methods
unsigned char read_digital_keypad(unsigned char detection_type)
{
    static unsigned char once = 1;  // Static variable for state change detection logic

    if (detection_type == STATE_CHANGE)  // Edge detection mode
    {
        // Check if any key is pressed AND this is first detection (debounce prevention)
        if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
        {
            once = 0;  // Mark detection to prevent repeated triggers
            return (KEY_PORT & INPUT_PINS);  // Return pressed key pattern
        }
        else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)  // All keys released
        {
            once = 1;  // Reset detection flag for next press
        }
    }
    else if (detection_type == LEVEL)  // Immediate level detection mode
    {
        // Return current key states without debounce checking
        return (KEY_PORT & INPUT_PINS);
    }

    // Return 0xFF if:
    // - No key pressed in STATE_CHANGE mode
    // - Invalid detection_type specified
    return 0xFF;
}