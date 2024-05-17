#ifndef SWEEP_FLAG_H
#define SWEEP_FLAG_H

#include <stdint.h>

enum ProgrammeStatus {
	SETUP,
	GREEN,
	RED,
	DETECTED,
	FINISHED
};

enum ProgrammeStatus get_status();

void set_setup();

void set_green();

void set_red();

void set_detected();

void set_finished();


#endif
