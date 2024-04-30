/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "stm32f303xc.h"
#include "buttonhandler.h"

void enable_clocks()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
}

void initGame()
{
    // Initialize the 'game' here
}

void interrupt_LEDs()
{
    // Handle LED interrupts here
}

int main(void)
{
    enable_clocks();

    // Set the interrupt handling function
    initButtonHandler(initGame);

    /* Loop forever */
    for (;;)
    {
    }
}
