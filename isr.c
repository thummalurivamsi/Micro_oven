#include <xc.h>
unsigned int count ;
extern unsigned char sec,min;
extern unsigned char pre_heat_time;
void __interrupt() isr( void )
{
    if(TMR2IF)
    {
        if( ++count == 20000) // 250 , 200ns 8 bit timer for 1 sec
        {
            count = 0;
            
            //for every 1 sec,decrement sec
            if(sec!=0)
                sec--;
            else if(sec==0 && min!=0)//if sec is 0, dec min
            {
                min=0;
                sec=60;
            }
            else if(pre_heat_time!=0)
            {
                pre_heat_time--;
            }
        }
        
        TMR2IF = 0; // clear interrupt flag 
        
    }
       
}

