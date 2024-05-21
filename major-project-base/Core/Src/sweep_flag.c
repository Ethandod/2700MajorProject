#include "sweep_flag.h"

enum ProgrammeStatus status = SETUP;

enum ProgrammeStatus get_status()
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
