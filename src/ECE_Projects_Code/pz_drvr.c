#include <Arduino.h>

#include "pz_drvr.h"
#include "smrt_lck_pin_defs.h"


/****************************************************************
 * 						 Global Constants
 ***************************************************************/

#define KNOCK_COUNT 3
#define KNOCK_TIMEOUT 3000
#define PROC_PERIOD 100
#define KNOCK_THRESHOLD 80


/******************************************************************************
*                                   Types
******************************************************************************/


/******************************************************************************
*                               Global Variables
******************************************************************************/
static bool knock_detect;
static uint8_t knock_counter = 0;

static uint16_t reading = 0;

// Timer stuff
static uint32_t curr_time;
static uint32_t last_knock_time;
static uint32_t last_proc_time;

/******************************************************************************
*                               Local Procedures
******************************************************************************/

static uint16_t get_snsr_reading( void );


/******************************************************************************
*                                 Procedures
******************************************************************************/

/**********************************************************
*   pz_drvr_init
*       Init the piezo driver. Setup pins and vars.
**********************************************************/
void pz_drvr_init( void )
{
	knock_detect = false;

	// Set to 0 so proc will run on first call.
	last_proc_time = 0;

	pinMode( PZ_DRVR_PIN, INPUT );


} /*pz_drvr_init */


/**********************************************************
*   pz_drvr_knock_detect
*       Returns whether a knock sequence has been detected.
*		Resets the knock_detect flag on function call.
**********************************************************/
bool pz_drvr_knock_detect( void )
{
	bool tmp = knock_detect;
	knock_detect = false;
	return tmp;

} /* pz_drvr_knock_detect */


/**********************************************************
*   pz_drvr_proc
*       Process function. Handles the state of the knock
*		sequence.
**********************************************************/
void pz_drvr_proc( void )
{
	curr_time = millis();
	
	// 100ms period
	if( PROC_PERIOD <= ( curr_time - last_proc_time ) )
		{
		// Set last proc time
		last_proc_time = curr_time;

		// Get reading from vibration sensor
		reading = get_snsr_reading();

		// If a knock has occured increment counter 
		if( KNOCK_THRESHOLD <= reading )
			{
			knock_counter++;
			last_knock_time = curr_time;
			}
		// If knock timeout occurs, reset counter	
		else if( ( knock_counter > 0 ) 
			  && ( KNOCK_TIMEOUT <= ( curr_time - last_knock_time ) ) )
			{
			knock_counter = 0;
			}

		//if the counter has reached KNOCK_COUNT set the knock detect flag 
		if( knock_counter >= KNOCK_COUNT )
			{
			knock_detect = true;
			knock_counter = 0;
			}
		}
	

} /* pz_drvr_proc */


/**********************************************************
*   get_snsr_reading
*		Reads the piezo sensor pin.
**********************************************************/
uint16_t get_snsr_reading( void )
{
	return analogRead( PZ_DRVR_PIN );
} /* pz_drvr_get_snsr_reading */

