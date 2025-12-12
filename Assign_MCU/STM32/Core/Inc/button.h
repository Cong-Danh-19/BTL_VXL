/*
 * button.h
 *
 *  Created on: Dec 9, 2025
 *      Author: dell pro
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


#include "main.h"


#define BUTTON_COUNT 4

#define PRESSED_STATE GPIO_PIN_RESET
#define NOR_STATE GPIO_PIN_SET

// External variables declaration
extern int button_auto_increase[BUTTON_COUNT];

// Function declarations
void button_init(void);
void getKeyInput(void);
int is_button_pressed(int index);
int is_button_pressed_1s(int index);
int is_button_double_pressed(int index);
int is_button_auto_increase(int index);
int is_button_held(int index);

#endif /* INC_BUTTON_H_ */
