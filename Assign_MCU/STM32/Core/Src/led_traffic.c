/*
 * led_traffic.c
 *
 *  Created on: Dec 9, 2025
 *      Author: dell pro
 */
#include "led_traffic.h"

void RGB_TrafficLight_Init(RGB_TrafficLight_t* RGB_tl,
                           uint16_t MODULED_A_Pin, uint16_t MODULED_B_Pin,
                           GPIO_TypeDef * MODULED_A_Port, GPIO_TypeDef * MODULED_B_Port)
{
    RGB_tl->MODULED_A_Pin  = MODULED_A_Pin;
    RGB_tl->MODULED_B_Pin  = MODULED_B_Pin;

    RGB_tl->MODULED_A_Port = MODULED_A_Port;
    RGB_tl->MODULED_B_Port = MODULED_B_Port;
}

void RGB_TrafficLight_TurnOn(RGB_TrafficLight_t RGB_tl, uint8_t State)
{
    HAL_GPIO_WritePin(RGB_tl.MODULED_A_Port, RGB_tl.MODULED_A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RGB_tl.MODULED_B_Port, RGB_tl.MODULED_B_Pin, GPIO_PIN_RESET);

    if(State == RED_STATE){
        HAL_GPIO_WritePin(RGB_tl.MODULED_A_Port, RGB_tl.MODULED_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_tl.MODULED_B_Port, RGB_tl.MODULED_B_Pin, GPIO_PIN_SET);
    }
    else if(State == YELLOW_STATE){
        HAL_GPIO_WritePin(RGB_tl.MODULED_A_Port, RGB_tl.MODULED_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_tl.MODULED_B_Port, RGB_tl.MODULED_B_Pin, GPIO_PIN_RESET);
    }
    else { // GREEN
        HAL_GPIO_WritePin(RGB_tl.MODULED_A_Port, RGB_tl.MODULED_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_tl.MODULED_B_Port, RGB_tl.MODULED_B_Pin, GPIO_PIN_SET);
    }
}

void RGB_TrafficLight_Blink(RGB_TrafficLight_t RGB_tl, uint8_t State)
{
    if (blink) {
        HAL_GPIO_WritePin(RGB_tl.MODULED_A_Port, RGB_tl.MODULED_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_tl.MODULED_B_Port, RGB_tl.MODULED_B_Pin, GPIO_PIN_RESET);
    }
    else {
        RGB_TrafficLight_TurnOn(RGB_tl, State);
    }
}

void updateBlink() {
    blink = 1 - blink;
}
