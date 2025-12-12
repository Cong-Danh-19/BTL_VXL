/*
 * global.h
 *
 *  Created on: 9 Dec 2025
 *      Author: dell pro
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

/****************** SCHEDULER DEFINE *********************/
//#define SCH_MAX_TASKS 40
//#define NO_TASK_ID    0

/****************** BUTTON DEFINE *********************/
#define N0_OF_BUTTONS              	 4
#define DURATION_FOR_AUTO_INCREASING 100
#define DOUBLE_PRESS_CHECKIN       	 8
#define DOUBLE_PRESS_TIMEOUT       	 15
#define BUTTON_IS_PRESSED          	 0
#define BUTTON_IS_RELEASED         	 1

/****************** LIGHT DEFINE *********************/
#define RED_STATE    0
#define GREEN_STATE  1
#define YELLOW_STATE 2

/****************** SYSTEM DEFINE *********************/
#define NORMAL_STATE     0
#define MANUAL_STATE 	 1
#define TUNNING_STATE     2


#define DURATION_RED     5
#define DURATION_YELLOW  2
#define DURATION_GREEN   3

/****************** SETTING STATE DEFINE *********************/
#define TUNNING_RED_STATE    0
#define TUNNING_YELLOW_STATE 1
#define TUNNING_GREEN_STATE  2


/****************** MANUAL STATE DEFINE *********************/
#define MANUAL_WAIT_STATE 0
#define MANUAL_SWITCH_STATE 1
#define MANUAL_WAIT_TIME 3

/****************** STRUCTURE DEFINE **************************/
typedef struct {
    uint16_t      btn_Pin;
    GPIO_TypeDef *btn_Port;

    GPIO_PinState btn_state;
    GPIO_PinState debounceButton_1;
    GPIO_PinState debounceButton_2;
    GPIO_PinState debounceButton_3;
    GPIO_PinState debounceButton_4;

    uint8_t  flagForButtonPress1s;
    uint8_t  flagForButtonPressDouble;
    uint8_t  firtpressflag;
    uint8_t  flagpress;
    uint16_t counterForButtonPress;
    uint16_t counterForButtonPress1s;
    uint16_t counterForButtonPressDouble;
} btn_typedef;

typedef struct {
    uint16_t MODULED_A_Pin;
    uint16_t MODULED_B_Pin;

    GPIO_TypeDef *MODULED_A_Port;
    GPIO_TypeDef *MODULED_B_Port;
} RGB_TrafficLight_t;
/****************** GLOBAL VARIABLES DEFINE *********************/

// SYSTEM STATE / COUNTERS
extern uint8_t system_state;
extern uint8_t setting_state;
extern uint8_t manual_state;

extern uint8_t light_state1;
extern uint8_t light_state2;

extern uint8_t Pre_Red_Counter;
extern uint8_t Pre_Yellow_Counter;
extern uint8_t Pre_Green_Counter;

extern uint8_t Red_Counter;
extern uint8_t Yellow_Counter;
extern uint8_t Green_Counter;

extern uint8_t Red_Counter_temp1;
extern uint8_t Yellow_Counter_temp1;
extern uint8_t Green_Counter_temp1;

extern uint8_t Red_Counter_temp2;
extern uint8_t Yellow_Counter_temp2;
extern uint8_t Green_Counter_temp2;

extern uint16_t Manual_Wait_Counter;
extern uint8_t Manual_Wait_Second;

// 7-SEG DISPLAY VALUES
extern uint8_t num1;
extern uint8_t num2;

extern uint8_t is_switch;

extern uint8_t blink;

// BUTTON ARRAY
extern btn_typedef btn[N0_OF_BUTTONS];

// TRAFFIC LIGHT INSTANCES
extern RGB_TrafficLight_t RGB_tl1;
extern RGB_TrafficLight_t RGB_tl2;


#endif /* INC_GLOBAL_H_ */
