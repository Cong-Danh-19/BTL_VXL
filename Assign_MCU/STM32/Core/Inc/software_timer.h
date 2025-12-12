/*
 * software_timer.h
 *
 *  Created on: 9 Dec 2025
 *      Author: dell pro
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>


extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;  // LED timer
extern int timer3_flag;  // LCD timer

void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
 void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
