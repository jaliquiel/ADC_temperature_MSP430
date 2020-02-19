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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// Function Prototypes
void swDelay(char numLoops);
//void getMonth(unsigned int days, char *s);
//void displayTime(long unsigned int seconds);
//void displayTemp(float inAvgTempC);
//void makeDate(long unsigned int month, long unsigned int days, char *s);


// Declare globals here
long unsigned int timer_cnt = 0;
int i;
long unsigned int seconds;

#define secondsInDay 86400
#define secondsInHour 3600
#define secondsInMinute 60
#define minutesInHour 60
#define hoursInDays 24
#define daysInYear 365

#define daysTilJanEnd 31
#define daysTilFebEnd 31+28
#define daysTilMarEnd 31+28+31
#define daysTilAprEnd 31+28+31+30

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

    seconds = 3500000;

    while (1)    // Forever loop
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        seconds++;
        displayTime(seconds);

    }  // end while (1)
}   //end main

int getMonth(unsigned int *days, char *s){
    if(days <= daysTilJanEnd){
        s[0] = 'J';
        s[1] = 'A';
        s[2] = 'N';
    }else if(days > daysTilJanEnd && days <= daysTilFebEnd){
        s[0] = 'F';
        s[1] = 'E';
        s[2] = 'B';
        days = days - daysTilJanEnd;
    }else if(days > daysTilFebEnd && days <= daysTilMarEnd){
        s[0] = 'M';
        s[1] = 'A';
        s[2] = 'R';
        days = days - daysTilFebEnd;
    }else if(days > daysTilMarEnd && days <= daysTilAprEnd){
        s[0] = 'A';
        s[1] = 'P';
        s[2] = 'R';
        days = days - daysTilMarEnd;
    }else if(days > daysTilAprEnd && days <= 151){
        s[0] = 'M';
        s[1] = 'A';
        s[2] = 'Y';
        days = days - daysTilAprEnd;
    }else if(days > 151 && days <= 181){
        s[0] = 'J';
        s[1] = 'U';
        s[2] = 'N';
        days = days - 151;
    }else if(days > 181 && days <= 212){
        s[0] = 'J';
        s[1] = 'U';
        s[2] = 'L';
        days = days - 181;
    }else if(days > 212 && days <= 243){
        s[0] = 'A';
        s[1] = 'U';
        s[2] = 'G';
        days = days - 212;
    }else if(days > 243 && days <= 273){
        s[0] = 'S';
        s[1] = 'E';
        s[2] = 'P';
        days = days - 243;
    }else if(days > 273 && days <= 304){
        s[0] = 'O';
        s[1] = 'C';
        s[2] = 'T';
        days = days - 273;
    }else if(days > 304 && days <= 334){
        s[0] = 'N';
        s[1] = 'O';
        s[2] = 'V';
        days = days - 304;
    }else if(days > 334 && days <= 365){
        s[0] = 'D';
        s[1] = 'E';
        s[2] = 'C';
        days = days - 334;
    }else{
        days = 0;
    }
}

void displayTime(long unsigned int seconds){
    long unsigned int months, days, hours, min, sec, currSeconds;
    char time[9];
    char date[7];

    // save our current time
    currSeconds = seconds;

//    // 1 month ~ 87763132800 ticks
//    months = timer_cnt / 87763132800;

    days = (int)(currSeconds / secondsInDay) % daysInYear;

    hours = (int)(currSeconds / secondsInHour) % hoursInDays;
 
    min = (int)(currSeconds / secondsInMinute) % minutesInHour;
   
    sec = (int)(currSeconds % secondsInMinute);

    // Make strings
    makeDate(days, date);
    makeTime(hours, min, sec, time);

    char t[8] = "08:45:00";

    // Display Strings
    Graphics_drawStringCentered(&g_sContext, date, AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, t, AUTO_STRING_LENGTH, 48, 65, TRANSPARENT_TEXT);
    //refreshes display
    Graphics_flushBuffer(&g_sContext);
    
}

void displayTemp(float inAvgTempC){
    char cString[8];
    char fString[8];

    // get copy of float
    float celciusTemp = inAvgTempC;

    // Convert celcius to fahrenheit
    float fahrenTemp = 1.8 * (celciusTemp) + 32;
    
    // Make strings
    makeTemp(celciusTemp, cString, true);
    makeTemp(fahrenTemp, fString, false);

    // Display Strings
    Graphics_drawStringCentered(&g_sContext, cString, AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, fString, AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
    //refreshes display
    Graphics_flushBuffer(&g_sContext);

}

// String functions
void makeDate(long unsigned int days, char *s){
    // ..
    getMonth(&days, s);
    s[4] = ' ';
    s[5] = days % 10 + '0';
    s[6] = (int)(days / 10) % 10 + '0';
    s[7] = '\0';
}

void makeTime(long unsigned int hours, long unsigned int min, long unsigned int sec, char *s)
{
    // ..
    char hourString[3];
    char minString[3];
    char secString[3];
}

void makeTemp(float temperature, char * s, bool isCelsius)
{
    // ..
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
