#ifndef SERIAL_PORT_HEADER
#define SERIAL_PORT_HEADER

#include <stdint.h>
#include "stm32f303xc.h"

// Serial port structure, stores important information for serial port usage
// Users of this module may want to define a new port for different USART peripherals
struct _SerialPort;
typedef struct _SerialPort SerialPort;

// make any number of instances of the serial port (they are extern because
//   they are fixed, unique values)
extern SerialPort USART1_PORT;


// The user might want to select the baud rate
enum {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200
};

// Functions called by the user of the module
void serialInitialise(uint32_t buffer_size,
					  uint32_t baudRate,
					  SerialPort *serial_port,
					  void (*rxCompletedStringFunction)(volatile uint8_t*, uint32_t));
void serialTransmitString(volatile uint8_t *pt, SerialPort *serial_port);

#endif
