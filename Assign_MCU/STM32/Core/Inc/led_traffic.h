/*
 * led_traffic.h
 *
 *  Created on: Dec 9, 2025
 *      Author: dell pro
 */

#ifndef INC_LED_TRAFFIC_H_
#define INC_LED_TRAFFIC_H_


#include "main.h"
#include "global.h"
void RGB_TrafficLight_Init(
    RGB_TrafficLight_t* RGB_tl,
    uint16_t MODULED_A_Pin,
    uint16_t MODULED_B_Pin,
    GPIO_TypeDef *MODULED_A_Port,
    GPIO_TypeDef *MODULED_B_Port
);

void RGB_TrafficLight_TurnOn(RGB_TrafficLight_t RGB_tl, uint8_t State);
void RGB_TrafficLight_Blink(RGB_TrafficLight_t RGB_tl, uint8_t State);
void updateBlink();

#endif /* INC_LED_TRAFFIC_H_ */
