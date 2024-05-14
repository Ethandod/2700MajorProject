#include "sweep_flag.h"

uint32_t status = SETUP;

uint32_t get_status()
{
	return status;
}

void set_setup()
{
	status = SETUP;
	return;
}

void set_green()
{
	status = GREEN;
	return;
}

void set_red()
{
	status = RED;
	return;
}

void set_detected()
{
	status = DETECTED;
	return;
}

void set_finished()
{
	status = FINISHED;
	return;
}
