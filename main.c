/*
 * File:   main.c
 * Author: vamsi
 *
 * Created on 9 February, 2025, 6:52 AM
 */


#include <xc.h>
#include"clcd.h"
#include"main.h"
#include"microoven.h"
#include"matrix_keypad.h"
#include"timers.h"

#pragma config WDTE=OFF

unsigned char operational_flag=POWER_ON_SCREEN;
unsigned char reset_flag=RESET_NOTHING;
extern unsigned char min,sec;

void init_config(void)
{
    //config CLCD
    init_clcd();
    init_matrix_keypad();
    
    //config FAN
    FAN_DDR=0;
    FAN=0;
    
    //config buzzer
    BUZZER_DDR=0;//CONFIG BUZZER PINS as output
    BUZZER=0;
    //config timer
    init_timer2();   
    PEIE=1;
    GIE=1;
}
void main(void) 
{
    unsigned char key;
    unsigned char start_mode=0;
    init_config();
    while(1)
    {
        key=read_matrix_keypad(STATE);//0 1 2 3 4 5 6 7 8 9 * # ALL_RELEASED
        //select the cooking mode based on key press,  in the menu screen
        if(operational_flag==MENU_SCREEN)
        {
            
            if(key==1)
            {
                clear_screen();
                operational_flag=MICRO_MODE;
                start_mode=0;
                clcd_print("Power=900W",LINE2(0));
                __delay_ms(2000);
                clear_screen();
                reset_flag=RESET_MODE;
            }
            else if(key==2)
            {
                clear_screen();
                start_mode=0;
                operational_flag=GRILL_MODE;
                reset_flag=RESET_MODE;
            }
            else if(key==3)
            {
                clear_screen();
                start_mode=0;
                operational_flag=CONVENTION_MODE;
                reset_flag=RESET_MODE;
            }
            else if(key==4)
            {
                clear_screen();
                operational_flag=START_MODE;
                start_mode=1;
                reset_flag=RESET_MODE;
            }
                
        }
        if(operational_flag==DISPLAY_TIME)
        {
            if(key==4)
            {
                //increment cooking time by 30sec
                if(start_mode)
                {
                    sec=sec+30;
                    if(sec>59)
                    {
                        min++;
                        sec=sec-60;
                    }
                }
            }
            else if(key==5)
            {
                operational_flag=PAUSE;
            }
            else if(key==6)
            {
                operational_flag=STOP;
            }
        }
        else if(operational_flag==PAUSE)
        {
            //resume the microoven
            if(key==4)
            {
                FAN=1;
                TMR2ON=1;
                operational_flag=DISPLAY_TIME;
                
            }
        }
        switch(operational_flag)
        {
            case POWER_ON_SCREEN :
                                  //display POWER_ON_SCREEN
                                  power_on_screen();
                                  operational_flag=MENU_SCREEN;//switch to menu screen
                                  clear_screen();//to clear the clcd
                                  break;
            case MENU_SCREEN     :
                                  //display menu
                                  display_menu_screen();
                                  break;
                
            case MICRO_MODE      :
                                   //read the key based on key SET TIME
                                   set_time(key,reset_flag);
                
                                   //turn ON microwave and display the time
                                   break;
            case DISPLAY_TIME    :
                                   time_display();
                                   break;
            case PAUSE           :
                                   //stop microoven and timer
                                   FAN=0;
                                   TMR2ON=0;
                                   break;
            case STOP            :
                                   //stop microoven and timer
                                   FAN=0;
                                   TMR2ON=0;
                                   clear_screen();
                                   operational_flag=MENU_SCREEN;
                                   break;
            case GRILL_MODE     :
                                   set_time(key,reset_flag);
                                   break;
            case CONVENTION_MODE:
                                   //set temperature, set time, display time
                                   set_temp(key,reset_flag);
                                   break;  
            case START_MODE     :
                                   //display time which 30sec as cooking time
                heat_food();
                
                                   break;
        }
        reset_flag=RESET_NOTHING;
    }
}

