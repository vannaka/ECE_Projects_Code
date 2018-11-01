#include <Arduino.h>

#ifndef SMRT_LCK_PIN_DEFS
#define SMRT_LCK_PIN_DEFS


/******************************************************************************
*                               Global Constants
******************************************************************************/

#define MTR_CNTRL_LEFT_HIGH_SIDE 	5
#define MTR_CNTRL_RIGHT_HIGH_SIDE 	3
#define MTR_CNTRL_LEFT_LOW_SIDE 	10
#define MTR_CNTRL_RIGHT_LOW_SIDE 	11

#define MTR_CNTRL_LIMIT_PIN A0

// Pins with interrupt support
// Uno: pins 2, 3
// Due: All digital pins
#define PZ_DRVR_PIN		  A1
#define RF_DRVR_BTN_A_PIN 2

#endif
