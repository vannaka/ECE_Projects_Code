#include "mtr_cntrl.h"

/******************************************************************************
*                               Global Variables
******************************************************************************/
static mtr_cntrl_state_t mtr_state;

/******************************************************************************
*                                 Procedures
******************************************************************************/
void mtr_cntrl_init( void )
{
    mtr_state = MTR_CNTRL_STATE_STOPPED;
}

void mtr_cntrl_set_state( mtr_cntrl_state_t state )
{
    mtr_state = state;
    
    switch( mtr_state )
        {
        case MTR_CNTRL_STATE_FORWARD:
            // TODO: Set motor to CW
            break;

        case MTR_CNTRL_STATE_REVERSE:
            // TODO: Set motor to full CCW
            break;

        case MTR_CNTRL_STATE_STOPPED:
            // TODO: Set motor to off
            break;
        }
}

mtr_cntrl_state_t mtr_cntrl_get_state( void )
{
  return mtr_state;
}

bool mtr_cntrl_get_limit_cw( void )
{
    // TODO: read the limit pin and return true if tripped
    return true;
}

bool mtr_cntrl_get_limit_ccw( void )
{
    // TODO: read the limit pin and return true if tripped
    return true;
}

