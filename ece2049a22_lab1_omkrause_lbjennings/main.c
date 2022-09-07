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
enum GameState{Welcome, CountDown, DrawAliens, CheckKeypad, GameOver};

// Main
void main(void)

{
    unsigned char currKey=0, dispSz = 3;
    unsigned char dispThree[3];
    //unsigned char state = 0;

    enum GameState state;
    state = Welcome;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired


    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display

    while(1)
    {
        switch(state)
        {
        case Welcome://welcome screen
            Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            break;
        case CountDown://count down
            //count down to game start trigger alien drawing
            break;
        case DrawAliens://draw aliens
            //draw aliens on screen and move them
            break;
        case CheckKeypad://check keypad
            //if(key == '*') {state = newGame; }
            //check keypad for button presses and remove appropriate aliens
            break;
        case GameOver://game over
            //print("GAME OVER");
            //count some number of loops
            //state = 0;
            //display game over and allow for restart
            break;
        }
    }

}
