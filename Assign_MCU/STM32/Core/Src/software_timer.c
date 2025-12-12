/*
 * software_timer.c
 *
 *  Created on: 9 Dec 2025
 *      Author: dell pro
 */


#include "software_timer.h"


int timer0_counter = 0;
int timer1_counter = 0;
int timer2_counter = 0;   // LED counter
int timer3_counter = 0;   // LCD counter

int timer0_flag = 0;
int timer1_flag = 0;
int timer2_flag = 0;      // LED flag
int timer3_flag = 0;      // LCD flag


void setTimer0(int duration){
    timer0_counter = duration / 10;
    timer0_flag = 0;
}

void setTimer1(int duration){
    timer1_counter = duration / 10;
    timer1_flag = 0;
}

void setTimer2(int duration){   // LED timer
    timer2_counter = duration / 10;
    timer2_flag = 0;
}

void setTimer3(int duration){   // LCD timer
    timer3_counter = duration / 10;
    timer3_flag = 0;
}


void timer_run(){
    if(timer0_counter > 0){
        timer0_counter--;
        if(timer0_counter == 0){
            timer0_flag = 1;
        }
    }

    if(timer1_counter > 0){
        timer1_counter--;
        if(timer1_counter == 0){
            timer1_flag = 1;
        }
    }

    if(timer2_counter > 0){     // LED
        timer2_counter--;
        if(timer2_counter == 0){
            timer2_flag = 1;
        }
    }

    if(timer3_counter > 0){     // LCD
        timer3_counter--;
        if(timer3_counter == 0){
            timer3_flag = 1;
        }
    }
}
