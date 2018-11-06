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
static volatile bool isr_gate;


/******************************************************************************
*                               Local Procedures
******************************************************************************/

static void btn_A_isr( void );


/******************************************************************************
*                                 Procedures
******************************************************************************/

/**********************************************************
*   rf_drvr_init
*       Init the rf driver. Setup pins and vars.
**********************************************************/
void rf_drvr_init( void )
{
	btn_A_pressed = false;
	isr_gate = false;

	pinMode( RF_DRVR_BTN_A_PIN, INPUT );

	// Attach interupt service routine.
	attachInterrupt( digitalPinToInterrupt( RF_DRVR_BTN_A_PIN ), btn_A_isr, CHANGE );
}


/**********************************************************
*   rf_drvr_btn_A_pressed
*		Returns whether a button has been pressed or not.
*		Resets the button pressed flag.
**********************************************************/
bool rf_drvr_btn_A_pressed( void )
{
	bool tmp = btn_A_pressed;
	btn_A_pressed = false;
	return tmp;
}


/**********************************************************
*   btn_A_isr
*		Interrupt service routine for the button.
**********************************************************/
void btn_A_isr( void )
{
	// isr_gate is to prevent proccessing interupts that were flaged before 
	// 	the isr was attached. I could clear the flag in a register somewhere
	//  before attaching the isr but I would have to find the data sheet for 
	//  the microprocessor and that's too much work.
	if( isr_gate )
	{
		btn_A_pressed = true;
	}
	else
	{
		isr_gate = true;
	}
}
