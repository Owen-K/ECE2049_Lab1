#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Function Prototypes
void swDelay(char numLoops);

// Declare globals here

// Main
void main(void)

{
    unsigned char currKey=0, dispSz = 3;
    unsigned char dispThree[3];
    unsigned char state = 0;


    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display

    while(1)
    {
        switch(state)
        {
        case 0://welcome screen
            Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            break;
        case 1://count down
            //count down to game start trigger alien drawing
            break;
        case 2://draw aliens
            //draw aliens on screen and move them
            break;
        case 3://check keypad
            //check keypad for button presses and remove appropriate aliens
            break;
        case 4://game over
            //display game over and allow for restart
            break;
        }
    }

}
