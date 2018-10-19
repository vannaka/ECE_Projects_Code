#include <Arduino.h>

#include "rf_drvr.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                                   Types
******************************************************************************/


/******************************************************************************
*                               Global Variables
******************************************************************************/

static volatile bool btn_A_pressed;


/******************************************************************************
*                               Local Procedures
******************************************************************************/

static void btn_A_isr( void );


/******************************************************************************
*                                 Procedures
******************************************************************************/


void rf_drvr_init( void )
{
	pinMode( RF_DRVR_BTN_A_PIN, INPUT );
	attachInterrupt( digitalPinToInterrupt( RF_DRVR_BTN_A_PIN ), btn_A_isr, RISING );
}


bool rf_drvr_btn_A_pressed( void )
{
	bool tmp = btn_A_pressed;
	btn_A_pressed = false;
	return tmp;
}


void btn_A_isr( void )
{
	btn_A_pressed = true;
}
