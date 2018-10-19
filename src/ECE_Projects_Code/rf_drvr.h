#ifndef RF_DRVR_H
#define RF_DRVR_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
*                                   Types
******************************************************************************/


/******************************************************************************
*                                 Procedures
******************************************************************************/

void rf_drvr_init( void );
bool rf_drvr_btn_A_pressed( void );


#ifdef __cplusplus
} // extern "C"
#endif

#endif