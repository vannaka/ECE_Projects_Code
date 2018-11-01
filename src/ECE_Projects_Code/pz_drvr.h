#ifndef PZ_DRVR_H
#define PZ_DRVR_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************
 *							Types
 *****************************************************************/


/*****************************************************************
 *				         Procedures
 ****************************************************************/

void pz_drvr_init( void );
void pz_drvr_proc( void );
bool pz_drvr_knock_detect();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
