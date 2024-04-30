#ifndef LIDAR_SWEEP_HEADER
#define LIDAR_SWEEP_HEADER

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "stm32f3xx.h"
#include "serial.h"
#include "sweep_flag.h"

// Quality of Life Definitions
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define LR 12
#define RL 23

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
#define THRESHOLD_VALUE 180
#define BREACHES 3
#define RESET_DELAY_FACTOR 2
#define SWEEP_DELAY_FACTOR 5

//#define THRESHOLD_VALUE 180
//#define BREACHES 3
//#define RESET_DELAY_FACTOR 2
//#define SWEEP_DELAY_FACTOR 5

typedef uint16_t distReadings[READINGS_PER_SWEEP];

void setup_sweeper();

uint16_t get_pan();

uint8_t set_pan(uint16_t pwmVal);

void sweep(uint16_t *previousReadings, uint16_t *output);

void omni_sweep(uint8_t direction, uint16_t *previousReadings, uint16_t *output);

void sweep_routine();

#endif

//	// CONSTANTS
//	uint16_t pwm_per_degree = 11;
//	uint16_t degree_t*raverse_ms = 3;
//	uint16_t starting_offset_y = 1450; //1450
//	uint16_t starting_offset_x = 1000; //1000
//
//	// INSTANCE
//	uint16_t degrees_of_sweep = 90;
//	uint16_t degrees_per_step = 3;
//
//	// DERIVED
//	uint16_t steps_per_sweep = degrees_of_sweep / degrees_per_step;
//	uint16_t step_increment = degrees_per_step * pwm_per_degree;
//	uint16_t starting_pwm = starting_offset_x - (step_increment * steps_per_sweep) / 2;
//	uint16_t finishing_pwm = starting_offset_x + (step_increment * steps_per_sweep) / 2;
//
//	// OPERATIONAL
//	uint16_t current_pwm = starting_pwm;
//	uint16_t sweep_direction = 1;
//
//
//	TIM2->CCR1 = starting_offset_y;//vertical_PWM;
//	//TIM2->CCR2 = starting_offset_x;//horizontal
//	while (1)
//	{
//		if(sweep_direction == 1)
//		{
//			current_pwm = current_pwm + step_increment;
//		}
//		else if (sweep_direction == 0)
//		{
//			current_pwm = current_pwm - step_increment;
//		}
//
//		if(current_pwm >= finishing_pwm)
//		{
//			current_pwm = finishing_pwm;
//			sweep_direction = 0;
//		}
//		else if (current_pwm <= starting_pwm)
//		{
//			current_pwm = starting_pwm;
//			sweep_direction = 1;
//		}
//
//
//		TIM2->CCR2 = current_pwm;//horizontal_PWM;
//
//		HAL_Delay(degree_traverse_ms * degrees_per_step);
