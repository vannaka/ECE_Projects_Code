#include "rf_drvr.h"
#include "mtr_cntrl.h"
#include "lck_cntrlr.h"

/******************************************************************************
*                                 Procedures
******************************************************************************/

void setup()
{
	rf_drvr_init();
    mtr_cntrl_init();
    lck_cntrlr_init();
}

void loop() 
{
	
	remt_recvr_proc();
    lck_cntrlr_proc();
}
