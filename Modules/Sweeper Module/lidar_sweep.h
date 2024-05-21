#ifndef LIDAR_SWEEP_HEADER
#define LIDAR_SWEEP_HEADER

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <Serial.h>

#include "stm32f3xx.h"
#include "sweep_flag.h"

// UNIVERSAL CONSTANTS
#define PWM_PER_DEGREE 11
#define DEGREE_TRAVERSE_MS 3
#define STARTING_OFFSET_VERT 1450
#define STARTING_OFFSET_HORI 1000

// INSTANCE CONSTANTS
#define DEGREES_OF_SWEEP 60
#define DEGREES_PER_STEP 1
#define READINGS_PER_SWEEP DEGREES_OF_SWEEP / DEGREES_PER_STEP

// TRIMMED CONSTANTS
//#define THRESHOLD_VALUE 5000
//#define BREACHES 3
//#define RESET_DELAY_FACTOR 2
//#define SWEEP_DELAY_FACTOR 20
//
//#define THRESHOLD_VALUE 100
//#define BREACHES 5
//#define RESET_DELAY_FACTOR 2
//#define SWEEP_DELAY_FACTOR 5

#define THRESHOLD_VALUE 100
#define BREACHES 5
#define RESET_DELAY_FACTOR 2
#define SWEEP_DELAY_FACTOR 5

void setup_sweeper();

void sweep_routine(void (*callback)());

#endif