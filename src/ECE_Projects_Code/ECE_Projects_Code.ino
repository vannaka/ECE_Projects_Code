#include "lck_cntrlr.h"


/******************************************************************************
*                                 Procedures
******************************************************************************/

void setup()
{
    // Initialize lock controller
    lck_cntrlr_init();
}

void loop() 
{
    lck_cntrlr_proc();
}
