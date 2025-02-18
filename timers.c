#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
    //timer2 control register
    
    //selecting post scalar as 1:1
    TOUTPS3 = 0;
    TOUTPS2 = 0;
    TOUTPS1 = 0;
    TOUTPS0 = 0;
    
    
    // turn on the timer2
    TMR2ON = 0;
    
    // prescalar as 1:1
    T2CKPS1 = 0;
    T2CKPS0 = 0;
    
    // enable timer2 interrupt
    TMR2IE = 1;
    
    
    // clear timer2 int flag
    TMR2IF = 0;
    
    //no of ticks in PR2
    PR2 = 250;
    
    
}
