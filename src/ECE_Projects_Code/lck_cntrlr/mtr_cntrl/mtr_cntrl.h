#ifndef MTR_CTRL_H
#define MTR_CTRL_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t mtr_cntrl_state_t;
enum
    {
    MTR_CNTRL_STATE_FORWARD,
    MTR_CNTRL_STATE_REVERSE,
    MTR_CNTRL_STATE_STOPPED
    };

void mtr_cntrl_init( void );
void mtr_cntrl_set_state( mtr_cntrl_state_t state );
mtr_cntrl_state_t mtr_cntrl_get_state( void );
bool mtr_cntrl_get_limit_cw( void );
bool mtr_cntrl_get_limit_ccw( void );

#endif
