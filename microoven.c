#include<xc.h>
#include"microoven.h"
#include"clcd.h"
#include"matrix_keypad.h"
#include"main.h"

unsigned char sec,min,pre_heat_time;//global var
unsigned char operational_flag;

void power_on_screen(void)
{
    for (unsigned int i=0;i<16;i++)
    {
        clcd_putch(BAR,LINE1(i));
    }
    clcd_print("Powering On",LINE2(2));
    clcd_print("Microwave Oven",LINE3(1));
    for (unsigned int i=0;i<16;i++)
    {
        clcd_putch(BAR,LINE4(i));
    }
    __delay_ms(5000);//built in fn
}

void clear_screen(void)
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}
void display_menu_screen(void)
{
    clcd_print("1.Micro",LINE1(0));
    clcd_print("2.Grill",LINE2(0));
    clcd_print("3.Convention",LINE3(0));
    clcd_print("4.Start",LINE4(0));
}
/*SET TIME (MM:SS)
  TIME - mm:ss
  *:CLEAR  #:ENTER*/
void set_time(unsigned char key,unsigned char reset_flag)
{
    static unsigned char blink_pos=0,key_count=0;//should not get re initialized
  
    if(reset_flag==RESET_MODE)
    {
        blink_pos=0;
        key_count=0;
        key=ALL_RELEASED;
        min=0;
        sec=0;
        reset_flag=RESET_NOTHING;
    }
    clcd_print("SET TIME (MM:SS)",LINE1(0));
    clcd_print("TIME -",LINE2(0));
    clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    
//The Matrix Keypad keys 0 to 9 are used to enter time.
    if(key!='*'&& key!='#'&& key!=ALL_RELEASED)
    {
        key_count++;
        if(key_count<=2)//update sec
        {
            sec=sec*10+key;//0*10+3=3//4*10=40-->34sec
            blink_pos=0;//blinks sec field
        }
        else if(key_count<=4)//update min
        {
            min=min*10+key;
            blink_pos=1;//blink min field
        }
    }
//The KEY * is used to clear entered time
    else if(key=='*')
    {
        if(blink_pos)//editing min field
        {
            min=0;
            key_count=2;
        }
        else
        { 
            sec=0;
            key_count=0;
        }
    }
//The KEY  #  is used to start microwave oven with entered time
    else if(key=='#')
    {
        //turn on the fan
        FAN=1;
        //start down counting time
        TMR2ON=1;
        //switch to the display time screen
        operational_flag=DISPLAY_TIME;
        clear_screen();
    }
//the secs filed should blink indicating the field to be chnaged
//to convert min and sec into ASCII to display on lcd (clcd won't display int values))
    if(blink_pos==0)//blink sec
    {
        clcd_putch(' ',LINE2(9));
        clcd_putch(' ',LINE2(10));
    }
    else//blink min
    {
        clcd_putch(' ',LINE2(6));
        clcd_putch(' ',LINE2(7));
    }
    //blinking the time to indicate we are reading time
    for(unsigned char wait=50;wait--;);
        
    clcd_putch((sec/10+'0'),LINE2(9));//  TIME : m m : s s
    clcd_putch((sec%10+'0'),LINE2(10));// 012345 6 7 8 9 10                      
    clcd_putch(':',LINE2(8));
    clcd_putch((min/10+'0'),LINE2(6));
    clcd_putch((min%10+'0'),LINE2(7));
}
void time_display(void)
{
    //display time and the options
    clcd_print("TIME = ",LINE1(1));
    clcd_putch((sec/10+'0'),LINE1(12));
    clcd_putch((sec%10+'0'),LINE1(13));                      
    clcd_putch(':',LINE1(11));
    clcd_putch((min/10+'0'),LINE1(9));
    clcd_putch((min%10+'0'),LINE1(10));
    clcd_print("4.START/RESUME",LINE2(1));
    clcd_print("5.PAUSE",LINE3(1));
    clcd_print("6.STOP",LINE4(1));
    
    if(min==0 && sec==0)
    {
        clear_screen();
        //display message cooking completed
        TMR2ON=0;
        FAN=0;
        clcd_print("TIME UP!!!",LINE2(1));
        clcd_print("ENJOY YOUR MEAL",LINE3(1));
    
        //indicate with buzzer
        BUZZER=1;
        __delay_ms(1000);
        BUZZER=0;
        //switch back to menu screen
        clear_screen();
        operational_flag=MENU_SCREEN;
    }
}

void set_temp(unsigned char key,unsigned char reset_flag)
{
    static unsigned char key_count;
    static unsigned int temp;
    if(reset_flag==RESET_MODE)
    {
        temp=0;
        key_count=0;
        key=ALL_RELEASED;
    }
    clcd_print("SET TEMP <*C>",LINE1(0));
    clcd_print("TEMP -",LINE2(0));
    clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    
    //blinking the temp to indicate we are reading temperature
    clcd_putch(' ',LINE2(8));
    clcd_putch(' ',LINE2(9));
    clcd_putch(' ',LINE2(10));
    for(unsigned char wait=50;wait--;);
    //Convert decimal temp into ascii format max(180*)
    clcd_putch((temp/100+'0'),LINE2(8));//1
    clcd_putch(((temp/10)%10+'0'),LINE2(9));//8
    clcd_putch((temp%10+'0'),LINE2(10));//0
    //the matrix keypad keys 0 to 9 are used to enter temperature
     if(key!='*'&& key!='#'&& key!=ALL_RELEASED)
     {
         if(key_count<3)
         {
             temp=temp*10+key;
             key_count++;
         }
     }
     else if(key=='*')
     {
         //The KEY * is used to clear entered temperature
         temp=0;
         key_count=0;
     }
     else if(key=='#')
     {
         //The KEY # is used to confirm entered temperature
         if(temp>180)
             temp=180;
         //implement pre heat screen
         clear_screen();
         clcd_print("Pre-Heating ",LINE1(2));
         clcd_print("Time Rem :",LINE3(0));
         clcd_print("Sec",LINE3(13));
         pre_heat_time=60;
         TMR2ON=1; 
         
         //display preheat screen till pre_heat_time is 0
         while(pre_heat_time!=0)
         {
             //decimal to ASCII to display it on clcd
             clcd_putch((pre_heat_time/100+'0'),LINE3(10));//1
             clcd_putch(((pre_heat_time/10)%10+'0'),LINE3(11));//8
             clcd_putch((pre_heat_time%10+'0'),LINE3(12));//0
             
         }
         //turn on the timer and change the operation_flag
         TMR2ON=0;
         clear_screen();
         operational_flag=MICRO_MODE;
     }    
}

void heat_food(void)
{
    //start cooking with 30sec
    sec=30;
    min=0;
    FAN=1;
    TMR2ON=1;
    operational_flag=DISPLAY_TIME;
}