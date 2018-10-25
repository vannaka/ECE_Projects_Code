#include <Arduino.h>

#include "rf_drvr.h"
#include "mtr_cntrl.h"
#include "lck_cntrlr.h"

/******************************************************************************
*                                 Procedures
******************************************************************************/

void setup()
{
    mtr_cntrl_init();
    lck_cntrlr_init();
    rf_drvr_init();

    Serial.begin( 9600 );
}

void loop() 
{
	// Unlock the lock
	if( rf_drvr_btn_A_pressed() )
		{
		lck_cntrlr_set_state( LCK_CNTRLR_STATE_UNLOCKED );
		}

    lck_cntrlr_proc();


}
