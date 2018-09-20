#include "lck_cntrlr.h"
#include "mtr_cntrl.h"


/******************************************************************************
*                                 Procedures
******************************************************************************/

void setup()
{
	// Initialize motor control driver
    mtr_cntrl_init();

    // Initialize lock controller
    lck_cntrlr_init();
}

void loop() 
{
    lck_cntrlr_proc();
}
