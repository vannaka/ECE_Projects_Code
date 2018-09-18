#include "lck_cntrlr.h"
#include "mtr_cntrl.h"

static lck_cntrlr_state_t lck_curr_state;
static lck_cntrlr_state_t lck_next_state;

void lck_cntrlr_init( void )
{
    mtr_cntrl_init();

    lck_curr_state = LCK_CNTRLR_STATE_UNLOCKED;
    lck_next_state = LCK_CNTRLR_STATE_UNLOCKED;
}

void lck_cntrlr_proc( void )
{
    switch( lck_curr_state )
    {
        case LCK_CNTRLR_STATE_UNLOCKED:
            if( LCK_CNTRLR_STATE_LOCKED == lck_next_state )
            {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_FORWARD );
            }
            
            if( ( LCK_CNTRLR_STATE_LOCKED == lck_next_state )
             && ( mtr_cntrl_get_limit_cw()                  ) )
            {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );
                lck_curr_state = lck_next_state;
            }
            break;
            
        case LCK_CNTRLR_STATE_LOCKED:
            if( LCK_CNTRLR_STATE_UNLOCKED == lck_next_state )
            {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_REVERSE );
            }
            
            if( ( LCK_CNTRLR_STATE_UNLOCKED == lck_next_state )
             && ( mtr_cntrl_get_limit_ccw()                   ) )
            {
                mtr_cntrl_set_state( MTR_CNTRL_STATE_STOPPED );
                lck_curr_state = lck_next_state;
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

