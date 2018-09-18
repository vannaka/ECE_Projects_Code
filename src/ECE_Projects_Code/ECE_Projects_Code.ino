#include "lck_cntrlr.h"

// the setup function runs once when you press reset or power the board
void setup()
{
    lck_cntrlr_init();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    lck_cntrlr_proc();
}