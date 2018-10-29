#include <Arduino.h>

#include "piezo_drvr.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                                   Types
******************************************************************************/

/******************************************************************************
*                               Global Variables
******************************************************************************/
static volatile bool knock_detect;
uint8_t knock_counter = 0;
uint32_t start_time;
uint16_t reading = 0;
bool reset_knock = true;


/******************************************************************************
*                               Local Procedures
******************************************************************************/

/******************************************************************************
*                                 Procedures
******************************************************************************/
void pz_drvr_init( void )
{
	knock_detect = false;

	pinMode( PZ_DRVR_PIN, INPUT );


} /*pz_drvr_init */

bool pz_drvr_knock_detect( void )
{
	bool tmp = knock_detect;
	knock_detect = false;
	return tmp;

} /* pz_drvr_knock_detect */

void pz_drvr_proc( void )
{
	reading = pz_drvr_get_snsr_reading();
	
	if( reset_knock )
	{
		start_time = millis();
		knock_counter = 0;
		reset_knock = false;
	}

		//if a knock has occured increment counter 
	if( reading >= KNOCK_THRESHOLD )
	{
		knock_counter++;
		start_time = millis();
	}
		
	else if( ( millis() - start_time ) > KNOCK_TIMEOUT )
	{
		//if more than three second has passed reset 
		reset_knock = true;
	}

	//if the counter has reached five set the knock detect flag 
	if( knock_count >= KNOCK_COUNT )
	{
		knock_detect = true;
	}
	
	//Short delay so we dont overload the serial port buffer
	delay( 50 );

} /* pz_drvr_proc */

bool pz_drvr_sts_rtn( void )
{
	return knock_detect;
}

uint16_t pz_drvr_get_snsr_reading( void )
{
	return analogRead( PZ_DRVR_PIN );
} /* pz_drvr_get_snsr_reading */
