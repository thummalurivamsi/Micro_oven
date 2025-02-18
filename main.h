/*
 * File:   main.c
 * Author: vamsi
 *
 * Created on 9 February, 2025, 6:52 AM
 */


#ifndef MAIN_H
#define MAIN_H
#define POWER_ON_SCREEN         0x01
#define MENU_SCREEN             0X02
#define MICRO_MODE              0X11
#define GRILL_MODE              0X12
#define CONVENTION_MODE         0X13
#define START_MODE              0X14

#define DISPLAY_TIME            0xDD

#define RESET_MODE              0xFF
#define RESET_NOTHING           0x00

#define FAN_DDR                 TRISC2
#define FAN                     RC2

#define BUZZER_DDR              TRISC1
#define BUZZER                  RC1

#define START                   0xAA
#define STOP                    0xBB
#define PAUSE                   0xCC


#endif     /*MAIN_H*/