#include "buttonhandler.h"

void (*buttonCallback)(void);

void initButtonHandler(void (*callback)(void))
{
    buttonCallback = callback;

    // Enable clock for SYSCFG
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Configure PA0 as input
    GPIOA->MODER &= ~GPIO_MODER_MODER0_Msk;

    // Configure PA0 for external interrupt
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

    // Enable rising edge trigger for EXTI0
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // Enable EXTI0 interrupt
    EXTI->IMR |= EXTI_IMR_MR0;

    // Enable NVIC IRQ for EXTI0
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0)
    {
        EXTI->PR |= EXTI_PR_PR0; // Clear the pending bit

        if (buttonCallback != NULL)
        {
            buttonCallback();
        }
    }
}
