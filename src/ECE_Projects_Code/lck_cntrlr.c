
#include "lck_cntrlr.h"
#include "mtr_cntrl.h"


/******************************************************************************
*                                   Types
******************************************************************************/

typedef uint8 intrnl_state_t;
enum
    {
    UNLOCKED,
    UNLOCKED_TO_LOCKED,
    LOCKED,
    LOCKED_TO_UNLOCKED   
    }


/******************************************************************************
*                               Global Variables
******************************************************************************/

// State machine control variables
static intrnl_state_t intrnl_curr_state;
//static intrnl_state_t intrnl_next_state;

// Public lock state
static lck_cntrlr_state_t lck_curr_state;
static lck_cntrlr_state_t lck_next_state;


/******************************************************************************
*                                 Procedures
******************************************************************************/

void lck_cntrlr_init( void )
{
    mtr_cntrl_init();

    intrnl_curr_state = UNLOCKED;
    intrnl_next_state = UNLOCKED;
    lck_next_state = LCK_CNTRLR_STATE_UNLOCKED;
}

void lck_cntrlr_proc( void )
{
    // State machine for the lock
    switch( intrnl_curr_state )
        {
        // Lock is stationary in the unlocked position
        case UNLOCKED:
            // Exit if next state in locked state
            if( LCK_CNTRLR_STATE_LOCKED == lck_next_state )
                {
                // Turn on motor.
                mtr_cntrl_set_state( MTR_CNTRL_STATE_CW );

                // Go to next state.
                intrnl_curr_state = UNLOCKED_TO_LOCKED;
                }

        // Lock is in transit to the locked position
        case UNLOCKED_TO_LOCKED:
            // If motor is at end of movement disable motor and go to next state
            // !!!USE ELAPSED TIME IF WE DECIDE NO TO ADD A LIMIT SWITCH!!!
            if( mtr_cntrl_get_limit_cw() )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );

                // Go to next state.
                intrnl_curr_state = LOCKED;
                }
            break;

        // Lock is stationary in the locked position
        case LOCKED:
            // Exit if next state in unlocked state
            if( LCK_CNTRLR_STATE_UNLOCKED == lck_next_state )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_CCW );

                // Go to next state.
                intrnl_curr_state = UNLOCKED_TO_LOCKED;
                }
            break;

        // Lock is in transit to the unlocked position
        case LOCKED_TO_UNLOCKED:
            // If motor is at end of movement disable motor and go to next state
            // !!!USE ELAPSED TIME IF WE DECIDE NO TO ADD A LIMIT SWITCH!!!
            if( mtr_cntrl_get_limit_ccw() )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );

                // Go to next state.
                intrnl_curr_state = UNLOCKED;
                }
            break;
        }
}

void lck_cntrlr_set_state( lck_cntrlr_state_t state )
{
    lck_next_state = state;
}

lck_cntrlr_state_t lck_cntrlr_get_state( void )
{
    return lck_curr_state;
}

