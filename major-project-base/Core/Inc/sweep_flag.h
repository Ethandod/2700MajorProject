#ifndef SWEEP_FLAG_H
#define SWEEP_FLAG_H

#include <stdint.h>

enum
{
	SETUP,
	GREEN,
	RED,
	DETECTED,
	FINISHED
};

uint32_t get_status();

void set_setup();

void set_green();

void set_red();

void set_detected();

void set_finished();


#endif
