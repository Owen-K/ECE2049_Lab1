#include <msp430.h>
#include <stdlib.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

#define ALIENS_ROW 10
#define ALIENS_COL 5
#define LOOP_MAX 4000 //4,000

// Function Prototypes
void swDelay(char numLoops);

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

// Declare globals here

//enumeration of all the gamestates
enum GameState{Welcome, CheckStart, CountDown, MoveAliens, GenAliens, DrawAliens, CheckEnd, ShootColumn, CheckKeypad, GameOver, NewLevel};

//method to reset the aliens array
void resetAliens(unsigned char aliens[ALIENS_ROW][ALIENS_COL]){
    int i, j;
    for(i = 0; i < ALIENS_ROW; i++){
        for(j = 0; j < ALIENS_COL; j++){
            aliens[i][j] = 0;
        }
    }
}

//scans up a column to see if has a
/*int shootColumn(unsigned char currKey, unsigned char aliens[ALIENS_ROW][ALIENS_COL]){
    int i;
    int j = currKey - '1';
    for(i = ALIENS_ROW-1; i>= 0; i--){
        if(aliens[i][j] == currKey){
            aliens[i][j] = 0;
            return 1;
        }
    }
    return 0;
    //aliens[ALIENS_ROW][j] = '0';
}*/

// Main
void main(void)

{
    unsigned char currKey=0;//, dispSz = 3;
    //unsigned char dispThree[3];

    //array of characters representing the aliens
    unsigned char aliens[ALIENS_ROW][ALIENS_COL];

    //enumeration representing game state, initially set to display welcome screen.
    enum GameState state;
    state = Welcome;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired

    //config methods
    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display
    int i , j; //loop variables used at various points
    int level =     1; //level representing current difficulty
    int numAliens = 0; //amount of aliens created during current level
    int numShot   = 0; //amount of aliens successfully eliminated

    //long int counting the number of loops passed through
    long unsigned int loopCounter = 0;

    while(1)
    {
        switch(state)
        {
        case Welcome://displays welcome screen
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            state = CheckStart;

            break;
        case CheckStart:
            //checks to see if * key has been pressed to start
            //distinct from CheckKeypad to avoid being triggered by the loop counter
            if(getKey() == '*'){
                loopCounter = 0;
                state = CountDown;
            }
            break;
        case CountDown:
            //resets game state
            //display 3 2 1 countdown
            resetAliens(aliens);
            numAliens = 0;
            numShot = 0;
            //count down to game start trigger alien drawing
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

            break;

        case MoveAliens:
            //moves all aliens down one row.
            //works by overwriting the one below with the one above
            //first row is an edge case: is left unchanged, duplicated below
            //designed to be overwritten in next function
            for(i = ALIENS_ROW-2; i > 0; i--){
                for(j = 0; j<ALIENS_COL; j++){
                    aliens[i][j] = aliens[i-1][j];
                }
            }
            state = GenAliens;

            break;

        case GenAliens:
            //randomly generates aliens on first row of screen
            //see lab report for detailed explanation on how it works
            for(i = 0; i < ALIENS_COL; i++){
                if(rand() % 5 + 1 <= level && numAliens < level * 5){
                    aliens[0][i] = '1' + i;
                    numAliens++;
                }else{
                    aliens[0][i] = 0;
                }
            }
            //state = CheckKeypad;
            state = CheckEnd;
            break;

        case CheckEnd:
            //checks end conditions of program

            //checks to see if game over has been reached
            //scans bottom row to see if any aliens have reached it
            for (i = 0; i < ALIENS_COL; i++){
                if(aliens[ALIENS_ROW-2][i] != 0){
                    state = GameOver;
                    break;
                }else{
                    state = DrawAliens;
                }
            }

            //checks if player has shot all of the aliens
            //moves to next level if so
            if(numShot == level * 5)
                state = NewLevel;

            break;

        case DrawAliens://draw aliens
            Graphics_clearDisplay(&g_sContext);

            //goes through entire array and prints out each character
            //characters are spaced 16 pixels apart horizontally
            //characters are spaced 8 characters apart vertically, with a initial vertical offset of 4 pixels
            //screen is 96 x 96 pixels, we thought this was appropriate
            for(i = 0; i < ALIENS_ROW; i++){
                for(j = 0; j<ALIENS_COL; j++ ){
                    //function only accepts a string, will not print properly if null terminator is not present
                    unsigned char curr[2] = aliens[i][j] + '\0';

                    //16 = horizontal spacer
                    //8  = vertical spacer
                    //4 = initial vertical offset
                    Graphics_drawStringCentered(&g_sContext, curr, AUTO_STRING_LENGTH, 16 * (j+1), 4 + i * 8, TRANSPARENT_TEXT);
                }
            }

            Graphics_flushBuffer(&g_sContext);

            state = CheckKeypad;
            break;

        case ShootColumn:
            //eliminates first alien it finds in column pressed
            ; //this is an empty statement to avoid C complaining about a declaration after a label
            int index = currKey - '1';
            for(i = ALIENS_ROW-1; i>= 0; i--){
                if(aliens[i][index] == currKey){
                    aliens[i][index] = 0;
                    numShot++;
                    break;
                }
            }
            //This displays a 0 under the column the player last shot
            //It looks nice
            //this for loop wipes the bottom row
            for (i = 0; i < ALIENS_COL; i++){
                aliens[ALIENS_ROW-1][i] = 0;
            }
            //sets appropriate index to display a 0
            aliens[ALIENS_ROW-1][currKey-'1'] = '0';
            state = DrawAliens;
            break;

        case CheckKeypad://check keypad, usual state for program
            //checks if time to update aliens
            if(loopCounter > LOOP_MAX/level){
                state = MoveAliens;
                loopCounter = 0;
                break;
            }

            currKey = getKey();

            //goes through possible entries for a key pressed
            if(currKey == '*')
                //resets and starts new game
                state = CountDown;
            else if(currKey <= '5' && currKey >= '1'){
                //if key is between 1 and 5, shoots up that column
                state = ShootColumn;
            }


            break;

        case GameOver://game over
            //displays game over screen
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "YOU SUCK", AUTO_STRING_LENGTH, 48, 58, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

            swDelay(3);
            //reset level
            level = 1;
            state = Welcome;
            //display game over and allow for restart
            break;
        case NewLevel:
            //level completed, display screen and increase level
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "YOU WIN", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "NEW LEVEL", AUTO_STRING_LENGTH, 48, 58, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(3);
            //increment level
            level++;
            state = CountDown;
            break;
        }

            loopCounter++;
    }

}
