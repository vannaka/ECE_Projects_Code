#ifndef PIEZO_DRVR_H
#define PIEZO_DRVR_H

#include <stdint.h>
#include <stdbool.h>

/****************************************************************
 * 						 Global Constants
 ***************************************************************/
#define KNOCK_COUNT 5
#define KNOCK_TIMEOUT 3000
#define KNOCK_THRESHOLD 100

/*****************************************************************
 *							Types
 *****************************************************************/

/*****************************************************************
 *				         Procedures
 ****************************************************************/

void pz_drvr_init( void );
void pz_drvr_proc( void );
bool pz_drvr_knock_detect();
bool pz_drvr_snsr_rtn();
uint16_t pz_drvr_get_snsr_reading( void );

#endif
