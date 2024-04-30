#include "sweep_flag.h"

volatile uint8_t sweep_flag = 0;

uint8_t get_sweep_flag()
{
	return sweep_flag;
}

void set_sweep_flag(uint8_t status)
{
	if (status != 0 && status != 1)
	{
		return;
	}
	sweep_flag = status;
	return;
}
