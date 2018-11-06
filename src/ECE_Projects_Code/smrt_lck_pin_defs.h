#include <Arduino.h>

#ifndef SMRT_LCK_PIN_DEFS
#define SMRT_LCK_PIN_DEFS


/******************************************************************************
*                               Global Constants
******************************************************************************/

/**********************************************************
*	Digital pins
**********************************************************/
#define MTR_CNTRL_LEFT_HIGH_SIDE 	5
#define MTR_CNTRL_RIGHT_HIGH_SIDE 	3
#define MTR_CNTRL_LEFT_LOW_SIDE 	10
#define MTR_CNTRL_RIGHT_LOW_SIDE 	11

/**********************************************************
*	Analog pins
**********************************************************/
#define MTR_CNTRL_LIMIT_PIN A0
#define PZ_DRVR_PIN		  A1

/**********************************************************
*	Interupt Pins
*		NOTE: Uno: pins 2, 3 have interrupt support
**********************************************************/
#define RF_DRVR_BTN_A_PIN 2

#endif
