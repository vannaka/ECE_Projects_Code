#include <Arduino.h>

#include "mtr_cntrl.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                               Global Variables
******************************************************************************/

static mtr_cntrl_state_t mtr_state;


/******************************************************************************
*                                 Procedures
******************************************************************************/

void mtr_cntrl_init( void )
{
    pinMode( MTR_CNTRL_MOTOR_CW_PIN, OUTPUT );
    pinMode( MTR_CNTRL_MOTOR_CCW_PIN, OUTPUT );

    mtr_state = MTR_CNTRL_STATE_STOPPED;
}


void mtr_cntrl_set_state( mtr_cntrl_state_t state )
{
    mtr_state = state;
    
    switch( mtr_state )
        {
        case MTR_CNTRL_STATE_CW:
            // TODO: Set motor to CW
            digitalWrite( MTR_CNTRL_MOTOR_CW_PIN, HIGH );
            digitalWrite( MTR_CNTRL_MOTOR_CCW_PIN, LOW );
            break;

        case MTR_CNTRL_STATE_CCW:
            // TODO: Set motor to CCW
            digitalWrite( MTR_CNTRL_MOTOR_CW_PIN, LOW );
            digitalWrite( MTR_CNTRL_MOTOR_CCW_PIN, HIGH );
            break;

        case MTR_CNTRL_STATE_STOPPED:
            // TODO: Set motor to off
            digitalWrite( MTR_CNTRL_MOTOR_CW_PIN, LOW );
            digitalWrite( MTR_CNTRL_MOTOR_CCW_PIN, LOW );
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

