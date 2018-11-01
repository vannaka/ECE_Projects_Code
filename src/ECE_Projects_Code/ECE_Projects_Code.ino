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

	Serial.begin( 115200 );
}

void loop() 
{

	double volt = get_sensor_voltage();

	switch( get_state() )
	{
		case UNLOCKED:
			Serial.print( "UNLOCKED " );
			break;
		case UNLOCKED_TO_LOCKED:
			Serial.print( "UNLOCKED_TO_LOCKED " );
			break;
		case LOCKED:
			Serial.print( "LOCKED " );
			break;
		case LOCKED_TO_UNLOCKED:
			Serial.print( "LOCKED_TO_UNLOCKED " );
			break;
	}

	Serial.print( "Volt: ");
	Serial.println( volt );


	// Unlock the lock
	if( rf_drvr_btn_A_pressed() || pz_drvr_knock_detect() )
		{
		lck_cntrlr_set_state( LCK_CNTRLR_STATE_UNLOCKED );
		}

    lck_cntrlr_proc();
	pz_drvr_proc();
	mtr_cntrl_proc();
}
