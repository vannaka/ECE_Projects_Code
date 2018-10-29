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
uint8_t knock_count = 0;

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
	uint16_t reading = pz_drvr_get_snsr_reading();
	uint32_t start_time = millis();
	knock_count = 0;

	while( knock_count < KNOCK_COUNT )
	{
		//if a knock has occured increment counter 
		if( reading >= KNOCK_THRESHOLD )
		{
			//Wait for knock to finish so we dont count it twice 
			while( pz_drvr_get_snsr_reading() >= KNOCK_THRESHOLD ){}
			knock_count++;
			start_time = millis();
		}
		
		else if( ( millis() - start_time ) > KNOCK_TIMEOUT )
		{
			//if more than three second has 
			break;
		}

		delay( 100 );
	}

	//if the counter has reached five set the knock detect flag 
	if( knock_count >= 5 )
	{
		knock_detect = true;
	}
	
} /* pz_drvr_proc */

bool pz_drvr_sts_rtn( void )
{
	return knock_detect;
}

uint16_t pz_drvr_get_snsr_reading( void )
{
	return analogRead( PZ_DRVR_PIN );
} /* pz_drvr_get_snsr_reading */
