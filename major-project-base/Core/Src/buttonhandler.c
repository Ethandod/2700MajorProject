#include "buttonhandler.h"
#include "stm32f303xc.h"

// store a pointer to the function that is called when a button is pressed
// set a default value of NULL so that it won't be called until the
// function pointer is defined
static void (*on_button_press)() = 0x00;

void enable_interrupt()
{
    __disable_irq();

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;

    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->IMR |= EXTI_IMR_MR0;

    NVIC_SetPriority(EXTI0_IRQn, -1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    __enable_irq();
}

void initButtonHandler(ButtonPressCallback callback)
{
    on_button_press = callback;
}

void EXTI0_IRQHandler(void)
{
    // run the button press handler (make sure it is not null first !)
    if (on_button_press != 0x00)
    {
        on_button_press();
    }

    // reset the interrupt (so it doesn't keep firing until the next trigger)
    EXTI->PR |= EXTI_PR_PR0;
}
