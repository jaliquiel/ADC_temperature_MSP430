/************** ECE2049 DEMO CODE ******************/
/**************  13 March 2019   ******************/
/***************************************************/

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
long unsigned int timer_cnt = 0;
int i;

// Main
void main(void)

{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired


    // Useful code starts here
    initLeds();

    configDisplay();
    configKeypad();

    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    // Write some text to the display
    Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "ECE2049-C20!", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
    //refreshes display
    Graphics_flushBuffer(&g_sContext);

    while (1)    // Forever loop
    {



    }  // end while (1)
}   //end main

void getMonth(unsigned int days){
    if(days <= 31)
        monthString = "JAN";
    if(days > 31 && days <= 59)
        monthString = "FEB";
    if(days > 59 && days <= 90)
        monthString = "MAR";
    if(days > 90 && days <= 120)
        monthString = "APR";
    if(days > 120 && days <= 151)
        monthString = "MAY";
    if(days > 151 && days <= 181)
        monthString = "JUN";
    if(days > 181 && days <= 212)
        monthString = "JUL";
    if(days > 212 && days <= 243)
        monthString = "AUG";
    if(days > 243 && days <= 273)
        monthString = "SEP";
    if(days > 273 && days <= 304)
        monthString = "OCT";
    if(days > 304 && days <= 334)
        monthString = "NOV";
    if(days > 334 && days <= 365)
        monthString = "DEC";
    else
        days = 0;
}

void displayTime(void){
    //...
}

void displayTemp(void){
    //...
}

void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent removal in optimization
			                    // by compiler. Functionally this is useless code

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void runTimerA2(){
    TA2CTL = TASSEL_1 + ID_0 + MC_1;
    TA2CCR0 = 163; // interrupt every 0.005
    TA2CCTL0 = CCIE;
}

void stopTimerA2(int reset){
    TA2CTL = MC_0; // stop timer
    TA2CCTL0 &= ~CCIE; // TA2CCR0 interrupt disabled
    if(reset)
        timer_cnt=0;
}

//------------------------------------------------------------------------------
// Timer2 A2 Interrupt Service Routine
//------------------------------------------------------------------------------
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER_A2_ISR (void)
{
    // Display is using Timer A1
    // Not sure where Timer A1 is configured?
//    Sharp96x96_SendToggleVCOMCommand();  // display needs this toggle < 1 per sec
    timer_cnt++;

}
