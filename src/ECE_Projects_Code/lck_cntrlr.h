#ifndef LCK_CNTRLR_H
#define LCK_CNTRLR_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
*                                   Types
******************************************************************************/

typedef uint8_t lck_cntrlr_state_t;
enum
    {
    LCK_CNTRLR_STATE_LOCKED,
    LCK_CNTRLR_STATE_UNLOCKED,
    LCK_CNTRLR_STATE_HOLD
    };

typedef uint8_t intrnl_state_t;
enum
    {
    UNLOCKED,
    UNLOCKED_TO_LOCKED,
    LOCKED,
    LOCKED_TO_UNLOCKED   
    };

/******************************************************************************
*                                 Procedures
******************************************************************************/

void lck_cntrlr_init( void );
void lck_cntrlr_proc( void );
void lck_cntrlr_set_state( lck_cntrlr_state_t state );
lck_cntrlr_state_t lck_cntrlr_get_state( void );

intrnl_state_t get_state( void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif
