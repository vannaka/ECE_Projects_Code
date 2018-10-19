
#include "lck_cntrlr.h"
#include "mtr_cntrl.h"


/******************************************************************************
*                               Global Constats
******************************************************************************/

#define TO_LOCKED_MOTOR_TIME 1000
#define TO_UNLOCKED_MOTOR_TIME 1000
#define UNLOCK_STATE_TIMEOUT 5000

/******************************************************************************
*                                   Types
******************************************************************************/

typedef uint8_t intrnl_state_t;
enum
    {
    UNLOCKED,
    UNLOCKED_TO_LOCKED,
    LOCKED,
    LOCKED_TO_UNLOCKED   
    };


/******************************************************************************
*                               Global Variables
******************************************************************************/

// State machine control variables
static intrnl_state_t curr_state;
static intrnl_state_t prev_state;

// Public lock state
static lck_cntrlr_state_t lck_curr_state;
static lck_cntrlr_state_t lck_next_state;

// Timer stuff
static uint32_t start_time;
static uint32_t curnt_time;
static uint32_t elaps_time;


/******************************************************************************
*                                 Procedures
******************************************************************************/

void lck_cntrlr_init( void )
{
    prev_state = UNLOCKED;
    curr_state = UNLOCKED;
    lck_next_state = LCK_CNTRLR_STATE_UNLOCKED;
}


void lck_cntrlr_proc( void )
{
    // Update timer
    elaps_time = millis() - start_time;

    // State machine for the lock
    switch( curr_state )
        {
        // Lock is stationary in the unlocked position
        case UNLOCKED:
            // This is true for the first loop that we're in this state for
            if( prev_state != curr_state )
            {
                // Reset timer here.
                start_time = millis();

                prev_state = curr_state;
            }

            // Exit if next state in locked state or the timeout has occured
            if( ( UNLOCK_STATE_TIMEOUT <= elaps_time        ) 
             || ( LCK_CNTRLR_STATE_LOCKED == lck_next_state ) )
                {
                // Turn on motor.
                mtr_cntrl_set_state( MTR_CNTRL_STATE_CW );

                // Go to next state.
                prev_state = curr_state;
                curr_state = UNLOCKED_TO_LOCKED;
                }
            break;

        // Lock is in transit to the locked position
        case UNLOCKED_TO_LOCKED:
            // This is true for the first loop that we're in this state for
            if( prev_state != curr_state )
            {
                // Reset timer here.
                start_time = millis();

                prev_state = curr_state;
            }

            // If motor is at end of movement disable motor and go to next state
            if( TO_LOCKED_MOTOR_TIME <= elaps_time )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );

                // Go to next state.
                curr_state = LOCKED;
                }
            break;

        // Lock is stationary in the locked position
        case LOCKED:
            // Exit if next state in unlocked state
            if( LCK_CNTRLR_STATE_UNLOCKED == lck_next_state )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_CCW );

                // Go to next state.
                prev_state = curr_state;
                curr_state = UNLOCKED_TO_LOCKED;
                }
            break;

        // Lock is in transit to the unlocked position
        case LOCKED_TO_UNLOCKED:
            // This is true for the first loop that we're in this state for
            if( prev_state != curr_state )
            {
                // Reset timer here.
                start_time = millis();

                prev_state = curr_state;
            }

            // If motor is at end of movement disable motor and go to next state
            if( TO_UNLOCKED_MOTOR_TIME <= elaps_time )
                {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );

                // Go to next state.
                curr_state = UNLOCKED;
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

