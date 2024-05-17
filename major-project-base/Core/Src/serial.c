#include <stdlib.h>
#include <stdbool.h>
#include "serial.h"

void serialReceiveCharacter(SerialPort *serial_port);
void serialTransmitCharacter(SerialPort *serial_port);

struct _SerialPort {
	USART_TypeDef *UART;
	GPIO_TypeDef *GPIO;
	volatile uint32_t MaskAPB2ENR;	// mask to enable RCC APB2 bus registers
	volatile uint32_t MaskAPB1ENR;	// mask to enable RCC APB1 bus registers
	volatile uint32_t MaskAHBENR;	// mask to enable RCC AHB bus registers
	volatile uint32_t SerialPinModeValue;
	volatile uint32_t SerialPinSpeedValue;
	volatile uint32_t SerialPinAlternatePinValueLow;
	volatile uint32_t SerialPinAlternatePinValueHigh;
	volatile uint8_t* StringBuffer;
	volatile uint8_t* AlternateStringBuffer;
	volatile uint32_t BufferCount;
	volatile uint32_t BufferSize;
	volatile uint8_t* TransmitPointer;
	volatile uint32_t UART_IRQn;
	void (*RxCompletedStringFunction)(volatile uint8_t*, uint32_t);
};

// Create an instance of SerialPort for USART1
SerialPort USART1_PORT = {USART1,
		GPIOC,
		RCC_APB2ENR_USART1EN, // bit to enable for APB2 bus
		0x00,	// bit to enable for APB1 bus
		RCC_AHBENR_GPIOCEN, // bit to enable for AHB bus
		0xA00,		// Change bits 4 and 5 to AF mode
		0xF00,		// Change bits 4 and 5 to high speed
		0x770000,  // for USART1 PC4 and 5, this is in the AFR low register
		0x00, // no change to the high alternate function register
		0x00, // default buffer pointer is NULL
		0x00, // default alternate buffer pointer is NULL
		0x00, // default buffer counter starts at 0
		0x00, // default buffer size is NULL
		0x00, // default transmit pointer is NULL
		USART1_IRQn, // the specific IRQn for the given USART
		0x00, // default RxCompletedStringFunction is NULL
		};

void USART1_IRQHandler(void) {
	// Catch the interrupt and call the handler with the appropriate USART port
	serialReceiveCharacter(&USART1_PORT);
	// Only transmit if transmit interupt is enabled
	if ((USART1->CR1 & USART_CR1_TXEIE) != 0) {
		serialTransmitCharacter(&USART1_PORT);
	}
}

// Initialise a serial port with interrupts
void serialInitialise(uint32_t buffer_size,
					  uint32_t baudRate,
					  SerialPort *serial_port,
					  void (*rxCompletedStringFunction)(volatile uint8_t*, uint32_t)) {
	// buffer_size - size of the double buffer
	// baudRate - serial baud rate
	// *serial_port - serial port to intialise
	// function - pointer to function with inputs pointer to buffer and string length


	// enable clock power, system configuration clock and GPIOC
	// common to all UARTs
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// enable the GPIO which is on the AHB bus
	RCC->AHBENR |= serial_port->MaskAHBENR;

	// set pin mode to alternate function and speed to high for the specific GPIO pins
	serial_port->GPIO->MODER = serial_port->SerialPinModeValue;
	serial_port->GPIO->OSPEEDR = serial_port->SerialPinSpeedValue;

	// set alternate function to enable USART to external pins
	serial_port->GPIO->AFR[0] |= serial_port->SerialPinAlternatePinValueLow;
	serial_port->GPIO->AFR[1] |= serial_port->SerialPinAlternatePinValueHigh;

	// enable the device based on the bits defined in the serial port definition
	RCC->APB1ENR |= serial_port->MaskAPB1ENR;
	RCC->APB2ENR |= serial_port->MaskAPB2ENR;

	// Get a pointer to the 16 bits of the BRR register that we want to change
	uint16_t *baud_rate_config = (uint16_t*)&serial_port->UART->BRR; // only 16 bits used!

	// Baud rate calculation from datasheet
	switch(baudRate){
	case BAUD_9600:
		*baud_rate_config = 0x341 * 6;  // 9600 at 8MHz
		break;
	case BAUD_19200:
		*baud_rate_config = 0x1A1 * 6;  // 19200 at 8MHz
		break;
	case BAUD_38400:
		*baud_rate_config = 0xD0 * 6;  // 38400 at 8MHz
		break;
	case BAUD_57600:
		*baud_rate_config = 0x8B * 6;  // 57600 at 8MHz
		break;
	case BAUD_115200:
		*baud_rate_config = 0x46 * 6;  // 115200 at 8MHz
		break;
	}

	// enable serial port for tx and rx
	serial_port->UART->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	// initialise the double buffer
	serial_port->BufferSize = buffer_size;
	serial_port->StringBuffer = (volatile uint8_t*)malloc(serial_port->BufferSize * sizeof(uint8_t));
	serial_port->AlternateStringBuffer = (volatile uint8_t*)malloc(serial_port->BufferSize * sizeof(uint8_t));

	// set the completion function
	serial_port->RxCompletedStringFunction = rxCompletedStringFunction;

	__disable_irq();

	// enable the rx interrupts, tx interrupts enabled when a string is being tranmitted
	serial_port->UART->CR1 |= USART_CR1_RXNEIE;
	serial_port->UART->CR3 |= USART_CR3_EIE;

	// Tell the NVIC module to enable interrupt and set priority
	NVIC_SetPriority(serial_port->UART_IRQn, 4);
	NVIC_EnableIRQ(serial_port->UART_IRQn);
	__enable_irq();
}

void setTransmitInterrupt(bool set, SerialPort *serial_port) {
	// Function to enable/disable the transmit interrupt
	__disable_irq();
	if (set) {
		serial_port->UART->CR1 |= USART_CR1_TXEIE;
	} else {
		serial_port->UART->CR1 &= ~USART_CR1_TXEIE;
	}
	__enable_irq();
}

void serialReceiveCharacter(SerialPort *serial_port) {
	// Called when interrupt is activated to receive a character into the buffer
	// When the buffer is full, call the callback function and switch the buffers

	// If byte is received properly
	if (!((serial_port->UART->ISR & USART_ISR_RXNE) == 0) &&
		(serial_port->UART->ISR & USART_ISR_FE) == 0 &&
		(serial_port->UART->ISR & USART_ISR_ORE) == 0) {

		// Add the new character to the string buffer
		serial_port->StringBuffer[serial_port->BufferCount] = serial_port->UART->RDR & 0xFF;
		serial_port->BufferCount++;

		// if exceeding size limit append 0x00 NULL terminating character
		if (serial_port->BufferCount + 1 == serial_port->BufferSize) {
			serial_port->StringBuffer[serial_port->BufferCount] = 0x00;
			serial_port-> BufferCount++;
		}

		// If terminating character found -> flip the buffers and call the callback function
		if (serial_port->StringBuffer[serial_port->BufferCount - 1] == 0x00){
			// Swap the buffers
			volatile uint8_t* temporary_buffer_pointer = serial_port->StringBuffer;
			serial_port->StringBuffer = serial_port->AlternateStringBuffer;
			serial_port->AlternateStringBuffer = temporary_buffer_pointer;

			// Callback function
			serial_port->RxCompletedStringFunction(temporary_buffer_pointer, serial_port->BufferCount);
			serial_port-> BufferCount = 0;
		}
	} else {
		// Clear errors if frame is not received properly
		serial_port->UART->ICR |= USART_ICR_ORECF | USART_ICR_FECF;

	}
}

void serialTransmitCharacter(SerialPort *serial_port) {
	// Called when the interrupt is activated and transmit interrupt is enabled

	// Check whether tx interrupt called the function, do nothing if tx interrupt didn't call
	if ((serial_port->UART->ISR & USART_ISR_TXE) == 0) {return;}

	// If we are at the end of the transmit buffer (null character),
	// send \r then \0 on the next interrupt then disable interrupt (no more characters to transmit)
	if (serial_port->TransmitPointer == 0x00) {
		return;
	}

	// If nothing left to send set pointer to null
	if (*serial_port->TransmitPointer == 0x00) {
		serial_port->UART->TDR = 0;
		serial_port->TransmitPointer = 0;
		setTransmitInterrupt(false, serial_port);
		return;
	}

	// All other cases, transmit the character normally
	serial_port->UART->TDR = *serial_port->TransmitPointer;
	serial_port->TransmitPointer++;
}

void serialTransmitString(volatile uint8_t* pt, SerialPort *serial_port) {
	// Set the pointer to the start of the string to transmit then enable the tx interrupt
	serial_port->TransmitPointer = pt;
	setTransmitInterrupt(true, serial_port);
}

