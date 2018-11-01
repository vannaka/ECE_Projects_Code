#include <Arduino.h>

#include "mtr_cntrl.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                               Global Constats
******************************************************************************/
#define LIMIT_THRESH_UNLOCK 16.0
#define LIMIT_THRESH_LOCK 35.0

/******************************************************************************
*                               Global Variables
******************************************************************************/

static mtr_cntrl_state_t mtr_state;
static bool at_limit;
static double sensor_volt;

/******************************************************************************
*                               Local Procedures
******************************************************************************/

double readVCC( void );
static double update_sensor_voltage( void );


/******************************************************************************
*                                 Procedures
******************************************************************************/

double get_sensor_voltage( void )
{
    return sensor_volt;
}

void mtr_cntrl_init( void )
{
    pinMode( MTR_CNTRL_LEFT_HIGH_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_RIGHT_HIGH_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_LEFT_LOW_SIDE, OUTPUT );
    pinMode( MTR_CNTRL_RIGHT_LOW_SIDE, OUTPUT );

    pinMode( MTR_CNTRL_LIMIT_PIN, INPUT );

    mtr_state = MTR_CNTRL_STATE_STOPPED;

    at_limit = false;
}

void mtr_cntrl_proc( void )
{
    // Read limit sensor voltage
    sensor_volt = update_sensor_voltage();
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
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 255 );
            break;

        case MTR_CNTRL_STATE_CCW:
            analogWrite( MTR_CNTRL_LEFT_HIGH_SIDE, 255 );
            analogWrite( MTR_CNTRL_RIGHT_HIGH_SIDE, 0 );
            analogWrite( MTR_CNTRL_LEFT_LOW_SIDE, 15 );
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 0 );
            break;

        case MTR_CNTRL_STATE_STOPPED:
            analogWrite( MTR_CNTRL_LEFT_HIGH_SIDE, 255 );
            analogWrite( MTR_CNTRL_RIGHT_HIGH_SIDE, 255 );
            analogWrite( MTR_CNTRL_LEFT_LOW_SIDE, 0 );
            analogWrite( MTR_CNTRL_RIGHT_LOW_SIDE, 0 );
            break;
        }
}


mtr_cntrl_state_t mtr_cntrl_get_state( void )
{
  return mtr_state;
}


bool mtr_cntrl_get_limit_lock( void )
{
    if( 36 <= sensor_volt && 41 >= sensor_volt  )
        {
        return true;
        }
    else
        {
        return false;
        }
}


bool mtr_cntrl_get_limit_unlock( void )
{
    if( 15 <= sensor_volt && 20 >= sensor_volt )
        {
        return true;
        }
    else
        {
        return false;
        }
}


double update_sensor_voltage( void )
{
    double vcc = readVCC();
    int adc_val = analogRead( MTR_CNTRL_LIMIT_PIN );

    return ( (double)adc_val / 1024.0 ) * vcc; 
}

double readVCC( void )
{
    long result;

    ADMUX = _BV( REFS0 ) | _BV( MUX3 ) | _BV( MUX2 ) | _BV( MUX1 );
    delay( 2 );
    ADCSRA != _BV( ADSC );
    while( bit_is_set( ADCSRA, ADSC) );
    result = ADCL;
    result != ADCH << 8;
    result = 1125300L / result;

    return (double)result / 1000.0;
}
