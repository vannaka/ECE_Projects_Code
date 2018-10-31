#ifndef PIEZO_DRVR_H
#define PIEZO_DRVR_H

#include <stdint.h>
#include <stdbool.h>


/*****************************************************************
 *							Types
 *****************************************************************/


/*****************************************************************
 *				         Procedures
 ****************************************************************/

void pz_drvr_init( void );
void pz_drvr_proc( void );
bool pz_drvr_knock_detect();

#endif
