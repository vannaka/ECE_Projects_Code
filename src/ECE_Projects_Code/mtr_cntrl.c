#include <Arduino.h>

#include "mtr_cntrl.h"
#include "smrt_lck_pin_defs.h"


/******************************************************************************
*                               Global Constats
******************************************************************************/

#define LIMIT_UNLOCK_THRESH_HI  20.0
#define LIMIT_UNLOCK_THRESH_LOW 15.0

#define LIMIT_LOCK_THRESH_HI    80.0
#define LIMIT_LOCK_THRESH_LOW   65.0


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

/**********************************************************
*   mtr_cntrl_init
*       Init the motor control module. Setup pins and vars.
**********************************************************/
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


/**********************************************************
*   mtr_cntrl_proc
*       Process function. Updates sensor voltage reading.
**********************************************************/
void mtr_cntrl_proc( void )
{
    // Read limit sensor voltage
    sensor_volt = update_sensor_voltage();
}


/**********************************************************
*   mtr_cntrl_set_state
*       Set the state of the motor.
**********************************************************/
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


/**********************************************************
*   mtr_cntrl_get_state
*       Get the state of the motor.
**********************************************************/
mtr_cntrl_state_t mtr_cntrl_get_state( void )
{
  return mtr_state;
}


/**********************************************************
*   mtr_cntrl_get_limit_lock
*       Check the limit sensor.
**********************************************************/
bool mtr_cntrl_get_limit_lock( void )
{
    if( ( LIMIT_LOCK_THRESH_LOW <= sensor_volt ) 
     && ( LIMIT_LOCK_THRESH_HI >= sensor_volt  ) )
        {
        return true;
        }
    else
        {
        return false;
        }
}


/**********************************************************
*   mtr_cntrl_get_limit_unlock
*       Check the limit sensor.
**********************************************************/
bool mtr_cntrl_get_limit_unlock( void )
{
    if( ( LIMIT_UNLOCK_THRESH_LOW <= sensor_volt )
     && ( LIMIT_UNLOCK_THRESH_HI >= sensor_volt  ) )
        {
        return true;
        }
    else
        {
        return false;
        }
}


/**********************************************************
*   update_sensor_voltage
*       Read the limit sensor voltage. The returned voltage
*       is adjusted for the reference voltage of the 
*       arduino.
**********************************************************/
double update_sensor_voltage( void )
{
    double vcc = readVCC();
    int adc_val = analogRead( MTR_CNTRL_LIMIT_PIN );

    return ( (double)adc_val / 1024.0 ) * vcc; 
}


/**********************************************************
*   readVCC
*       Get the reference voltge of the arduino.
**********************************************************/
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
