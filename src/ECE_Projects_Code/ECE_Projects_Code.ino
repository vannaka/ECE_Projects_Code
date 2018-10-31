#include <Arduino.h>

#include "rf_drvr.h"
#include "mtr_cntrl.h"
#include "lck_cntrlr.h"
#include "pz_drvr.h"

/******************************************************************************
*                                 Procedures
******************************************************************************/

void setup()
{
    mtr_cntrl_init();
    lck_cntrlr_init();
    rf_drvr_init();
	pz_drvr_init();
}

void loop() 
{
	// Unlock the lock
	if( rf_drvr_btn_A_pressed() || pz_drvr_knock_detect() )
		{
		lck_cntrlr_set_state( LCK_CNTRLR_STATE_UNLOCKED );
		}

    lck_cntrlr_proc();
	pz_drvr_proc();
}
