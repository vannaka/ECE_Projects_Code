#include <Arduino.h>

#include "mtr_cntrl.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                               Global Constats
******************************************************************************/
#define LIMIT_THRESH 600

/******************************************************************************
*                               Global Variables
******************************************************************************/

static mtr_cntrl_state_t mtr_state;
static bool at_limit;


/******************************************************************************
*                                 Procedures
******************************************************************************/

void mtr_cntrl_init( void )
{
    pinMode( MTR_CNTRL_LEFT_HIGH_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_RIGHT_HIGH_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_LEFT_LOW_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_RIGHT_LOW_SIDE, OUTPUT );

    mtr_state = MTR_CNTRL_STATE_STOPPED;

    at_limit = false;
}

void mtr_cntrl_proc( void )
{
    // Get proximity to endstop
    int limit_val = analogeRead( MTR_CNTRL_LIMIT_PIN );

    // If at end of movement, stop motor
    if( LIMIT_THRESH <= limit_val )
    {
        mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );
    }
}


void mtr_cntrl_set_state( mtr_cntrl_state_t state )
{
    mtr_state = state;
    
    switch( mtr_state )
        {
        case MTR_CNTRL_STATE_CW:
            analogWrite( MTR_CNTRL_LEFT_HIGH_SIDE, 0 );
            analogWrite( MTR_CNTRL_RIGHT_HIGH_SIDE, 255 );
            analogWrite( MTR_CNTRL_LEFT_LOW_SIDE, 0 );
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 25 );
            break;

        case MTR_CNTRL_STATE_CCW:
            analogWrite( MTR_CNTRL_LEFT_HIGH_SIDE, 255 );
            analogWrite( MTR_CNTRL_RIGHT_HIGH_SIDE, 0 );
            analogWrite( MTR_CNTRL_LEFT_LOW_SIDE, 25 );
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 0 );
            break;

        case MTR_CNTRL_STATE_STOPPED:
            analogWrite( MTR_CNTRL_LEFT_HIGH_SIDE, 0 );
            analogWrite( MTR_CNTRL_RIGHT_HIGH_SIDE, 0 );
            analogWrite( MTR_CNTRL_LEFT_LOW_SIDE, 0 );
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 0 );
            break;
        }
}


mtr_cntrl_state_t mtr_cntrl_get_state( void )
{
  return mtr_state;
}


bool mtr_cntrl_get_limit( void )
{
    return at_limit;
}

