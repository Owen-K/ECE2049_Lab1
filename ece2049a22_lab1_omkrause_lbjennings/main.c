#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

#define ALIENS_ROW 10
#define ALIENS_COL 5

// Function Prototypes
void swDelay(char numLoops);

// Declare globals here
enum GameState{Welcome, CountDown, DrawAliens, MoveAliens, GenAliens, CheckKeypad, GameOver};

void resetAliens(unsigned char aliens[ALIENS_ROW][ALIENS_COL]){
    int i, j;
    for(i = 0; i < ALIENS_ROW; i++){
        for(j = 0; j < ALIENS_COL; j++){
            aliens[i][j] = '0';
        }
    }
}

// Main
void main(void)

{
    unsigned char currKey=0, dispSz = 3;
    unsigned char dispThree[3];

    unsigned char aliens[ALIENS_ROW][ALIENS_COL];


    enum GameState state;
    state = Welcome;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired


    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display
    int i , j; //loop variables used at various points
    int level = 1;
    while(1)
    {
        switch(state)
        {
        case Welcome://welcome screen
            resetAliens(aliens);
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            state = CheckKeypad;

            break;
        case CountDown://count down
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(1);
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(1);
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(1);

            state = GenAliens;
            //count down to game start trigger alien drawing
            break;
        case MoveAliens:
            swDelay(2);
            for(i = ALIENS_ROW; i > 0; i--){
                for(j = 0; j<ALIENS_COL; j++){
                    aliens[i][j] = aliens[i-1][j];
                }
            }
            state = GenAliens;

            //if reached end condition
            for (i = 0; i < ALIENS_COL; i++){
                if(aliens[ALIENS_ROW][i] != '0'){
                    state = GameOver;
                }
            }
            break;
        case GenAliens:
            for(i = 0; i < ALIENS_COL; i++){
                if(rand() % 5 + 1 <= level){
                    aliens[0][i] = '1' + i;
                }else{
                    aliens[0][i] = '0';
                }
            }
            //state = CheckKeypad;
            state = DrawAliens;
            break;
        case DrawAliens://draw aliens
            Graphics_clearDisplay(&g_sContext);

            for(i = 0; i < ALIENS_ROW; i++){
                for(j = 0; j<ALIENS_COL; j++ ){
                    unsigned char curr[2] = aliens[i][j] + '\0';

                    //16 = horizontal spacer
                    //8  = vertical spacer
                    Graphics_drawStringCentered(&g_sContext, curr, AUTO_STRING_LENGTH, 16 * (j+1), 4 + i * 8, TRANSPARENT_TEXT);
                }
            }

            Graphics_flushBuffer(&g_sContext);

            //state = CheckKeypad;
            state = MoveAliens;
            break;
        case CheckKeypad://check keypad
            currKey = getKey();

            if(currKey == '*')
                state = CountDown;
            //if(key == '*') {state = newGame; }
            //check keypad for button presses and remove appropriate aliens
            break;
        case GameOver://game over
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "YOU SUCK", AUTO_STRING_LENGTH, 48, 58, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            swDelay(3);
            state = Welcome;
            //display game over and allow for restart
            break;
        }
    }

}

void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2021

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
