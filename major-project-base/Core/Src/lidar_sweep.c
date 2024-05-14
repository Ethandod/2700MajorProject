#include "lidar_sweep.h"


// Quality of Life Definitions
#define LR 12
#define RL 23

typedef uint16_t distReadings[READINGS_PER_SWEEP];

typedef struct servo
{
	TIM_HandleTypeDef *controlTimer;
	uint16_t position;
};

struct servo pan, tilt;


uint16_t last_capture = 0;
uint16_t diff = 0;

uint16_t rise_time = 0;
uint16_t last_period = 0;

HAL_StatusTypeDef return_value = 0x00;

uint16_t get_pan()
{
	return pan.position;
}

uint8_t set_pan(uint16_t pwmVal)
{
	if (pwmVal < 0 || pwmVal > 2000)
	{
		return 1;
	}

	pan.position = pwmVal;
	pan.controlTimer->Instance->CCR2 = pwmVal;
	return 0;
}

uint8_t set_tilt(uint16_t pwmVal)
{
	if (pwmVal < 0 || pwmVal > 2000)
	{
		return 1;
	}

	tilt.position = pwmVal;
	tilt.controlTimer->Instance->CCR1 = pwmVal;
	return 0;
}

void transfer_array_data(uint16_t *sourceArray, uint16_t *targetArray, uint16_t elements)
{
	for(int c = 0; c < elements;c++)
	{
		targetArray[c] = sourceArray[c];
	}
	return;
}

void setup_sweeper(I2C_HandleTypeDef *hi2c1, SPI_HandleTypeDef *hspi1, TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2, PCD_HandleTypeDef *hpcd_USB_FS)
{
	// enable clocks
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;

	SerialInitialise(BAUD_115200, &USART1_PORT, 0x00);

	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_2);

	HAL_TIM_IC_Start_IT(htim1, TIM_CHANNEL_1);

	// TIM 2 is setup with a prescaler that makes 1 count = 1 microsecond
	// Even with HAL, you can still set the values yourself
	TIM2->ARR = 20000; // 20000 = 20ms, which is the desired clock period for servos
	TIM2->CR1 |= TIM_CR1_ARPE; // this makes the timing not change until the next pulse is finished



	// note: for PWM if you continually change the clock period
	// you can get unexpected results. To remove this, set ARPE so that the
	// ARR settings are not activated until the next cycle.

	initialise_ptu_i2c(hi2c1);

//	uint8_t reset_value = 0x00;
//	return_value = HAL_I2C_Mem_Write(hi2c1, LIDAR_WR, 0x00, 1, &reset_value, 1, 10);


	// set the servos to their starting positions
	pan.controlTimer = htim2;
	tilt.controlTimer = htim2;

	set_pan(STARTING_OFFSET_HORI);
	set_tilt(STARTING_OFFSET_VERT);

	HAL_Delay(100);


}

void sweep(uint16_t *previousReadings, uint16_t *output)
{
	uint16_t step_increment = DEGREES_PER_STEP * PWM_PER_DEGREE;
	uint16_t starting_pwm = STARTING_OFFSET_HORI - (step_increment * READINGS_PER_SWEEP) / 2;
	uint16_t finishing_pwm = STARTING_OFFSET_HORI + (step_increment * READINGS_PER_SWEEP) / 2;

	// OPERATIONAL
	uint16_t current_pwm;
	uint8_t string_to_send[64];
	uint16_t delta;
	uint8_t thresholdBreachCount = 0;

	// set the servos to the starting position
	SerialOutputString("############\r\n", &USART1_PORT);
	set_tilt(STARTING_OFFSET_VERT);
	set_pan(starting_pwm);
	HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_OF_SWEEP * RESET_DELAY_FACTOR);

//	sprintf(string_to_send, "---{%hu}---\r\n", previousReadings[READINGS_PER_SWEEP - 1]);
//	SerialOutputString(string_to_send, &USART1_PORT);


	for(int i = 1; i < READINGS_PER_SWEEP; i++) // DO NOT CHANGE i TO 0, ITS A COCONUT.png situation
	{
		current_pwm = starting_pwm + step_increment * i;

		set_pan(current_pwm);

		HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_PER_STEP * SWEEP_DELAY_FACTOR);
		output[i] = last_period;

		if (previousReadings != NULL)
		{
			delta = abs(output[i]-previousReadings[i]);

			sprintf(string_to_send, "[%hu] : {%hu vs %hu} --> [%hu]\r\n",i, output[i], previousReadings[i], delta);
			SerialOutputString(string_to_send, &USART1_PORT);

			if (delta > THRESHOLD_VALUE)
			{
				thresholdBreachCount++;
			}
			else
			{
				thresholdBreachCount = 0;
			}
		}
		else
		{
			sprintf(string_to_send, "{%hu}\r\n", output[i]);
			SerialOutputString(string_to_send, &USART1_PORT);
		}
		if (thresholdBreachCount >= BREACHES)
		{
			SerialOutputString("Breach Limit Reached!!!\r\n", &USART1_PORT);
			set_detected();
			return;
		}
	}
}


void crude_omni_sweep(uint16_t *previousReadings, uint16_t *output)
{
	uint16_t step_increment = DEGREES_PER_STEP * PWM_PER_DEGREE;
	uint16_t starting_pwm = STARTING_OFFSET_HORI - (step_increment * READINGS_PER_SWEEP) / 2;
	uint16_t finishing_pwm = STARTING_OFFSET_HORI + (step_increment * READINGS_PER_SWEEP) / 2;

	// OPERATIONAL
	uint16_t current_pwm;
	uint8_t string_to_send[64];
	uint16_t delta;
	uint8_t thresholdBreachCount = 0;

	// set the servos to the starting position
	SerialOutputString("############\r\n", &USART1_PORT);
	set_tilt(STARTING_OFFSET_VERT);
	set_pan(starting_pwm);
	HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_OF_SWEEP * RESET_DELAY_FACTOR);

//	sprintf(string_to_send, "---{%hu}---\r\n", previousReadings[READINGS_PER_SWEEP - 1]);
//	SerialOutputString(string_to_send, &USART1_PORT);


	for(int i = 0; i < READINGS_PER_SWEEP; i++)
	{
		current_pwm = starting_pwm + step_increment * i;

		set_pan(current_pwm);

		HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_PER_STEP * SWEEP_DELAY_FACTOR);
		output[i] = last_period;

		if (previousReadings[0] != 0)
		{
			delta = abs(output[i]-previousReadings[i]);

			sprintf(string_to_send, "[%hu] : {%hu vs %hu} --> [%hu]\r\n",i, output[i], previousReadings[i], delta);
			SerialOutputString(string_to_send, &USART1_PORT);

			if (delta > THRESHOLD_VALUE)
			{
				thresholdBreachCount++;
			}
			else
			{
				thresholdBreachCount = 0;
			}
		}
		else
		{
			sprintf(string_to_send, "[%hu] : {%hu}\r\n", i, output[i]);
			SerialOutputString(string_to_send, &USART1_PORT);
		}
		if (thresholdBreachCount >= BREACHES)
		{
			SerialOutputString("Breach Limit Reached!!!\r\n", &USART1_PORT);
			while(1 == 1){ }
		}
	}


//	memcpy(previousReadings, output, sizeof(previousReadings));
//	previousReadings = output;
	transfer_array_data(output, previousReadings, READINGS_PER_SWEEP);

	for(int i = READINGS_PER_SWEEP - 1; i >= 0; i--)
	{
		current_pwm = starting_pwm + step_increment * i;

		set_pan(current_pwm);

		HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_PER_STEP * SWEEP_DELAY_FACTOR);
		output[i] = last_period;

		if (previousReadings[0] != 0)
		{
			delta = abs(output[i]-previousReadings[i]);

			sprintf(string_to_send, "[%hu] : {%hu vs %hu} --> [%hu]\r\n",i, output[i], previousReadings[i], delta);
			SerialOutputString(string_to_send, &USART1_PORT);

			if (delta > THRESHOLD_VALUE)
			{
				thresholdBreachCount++;
			}
			else
			{
				thresholdBreachCount = 0;
			}
		}
		else
		{
			sprintf(string_to_send, "[%hu] : {%hu}\r\n", i, output[i]);
			SerialOutputString(string_to_send, &USART1_PORT);
		}
		if (thresholdBreachCount >= BREACHES)
		{
			SerialOutputString("Breach Limit Reached!!!\r\n", &USART1_PORT);
			while(1 == 1){ }
		}
	}
}



void omni_sweep(uint8_t direction, uint16_t *previousReadings, uint16_t *output)
{
	uint16_t step_increment = DEGREES_PER_STEP * PWM_PER_DEGREE;
	uint16_t min_pwm = STARTING_OFFSET_HORI - (step_increment * READINGS_PER_SWEEP) / 2;
	uint16_t max_pwm = STARTING_OFFSET_HORI + (step_increment * READINGS_PER_SWEEP) / 2;

	uint16_t starting_pwm;
	uint16_t finishing_pwm;

	switch(direction)
	{
	case LR:
		starting_pwm = min_pwm;
		finishing_pwm = max_pwm;
		break;
	case RL:
		starting_pwm = max_pwm;
		finishing_pwm = min_pwm;
		break;
	default:
		return;
	};

	// OPERATIONAL
	uint16_t current_pwm = starting_pwm;
	uint8_t string_to_send[64];
	uint16_t delta;
	uint16_t reading_array_position;
	uint16_t alt_reading_position;
	uint8_t threshold_breach_count = 0;
	uint8_t reading_count = 0;


	// set the servos to the starting position allowing time for travel
	SerialOutputString("############\r\n", &USART1_PORT);
	set_tilt(STARTING_OFFSET_VERT);

	uint16_t grace_period_delay = abs(get_pan() - starting_pwm) * DEGREE_TRAVERSE_MS * RESET_DELAY_FACTOR;
	set_pan(starting_pwm);
	HAL_Delay(grace_period_delay);

	//set_pan(current_pwm);
	//HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_OF_SWEEP * RESET_DELAY_FACTOR); // maximum possible time to reach position

	// loop through readings
	while(reading_count < READINGS_PER_SWEEP)
	{
		set_pan(current_pwm);


		// record the reading and get the next pwm ready
		if(direction == RL)
		{
			reading_array_position = READINGS_PER_SWEEP - reading_count - 1;
			alt_reading_position = reading_count;
			HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_PER_STEP * SWEEP_DELAY_FACTOR);
			output[reading_array_position] = last_period;
			current_pwm = starting_pwm - step_increment * reading_count;
		}
		else
		{
			reading_array_position = reading_count;
			alt_reading_position = READINGS_PER_SWEEP - reading_count - 1;
			HAL_Delay(DEGREE_TRAVERSE_MS * DEGREES_PER_STEP * SWEEP_DELAY_FACTOR);
			output[reading_array_position] = last_period;
			current_pwm = starting_pwm + step_increment * reading_count;
		}

		//
		if (previousReadings != NULL)
		{
			delta = abs(output[reading_array_position]-previousReadings[reading_array_position]);

			sprintf(string_to_send, "[%hu] : {%hu vs %hu} --> [%hu]\r\n",reading_array_position, output[reading_array_position], previousReadings[reading_array_position], delta);
			SerialOutputString(string_to_send, &USART1_PORT);

			if (delta > THRESHOLD_VALUE)
			{
				threshold_breach_count++;
//				threshold_breach_count = 0;
			}
			else
			{
				threshold_breach_count = 0;
			}
		}
		else
		{
			sprintf(string_to_send, "[%hu] : {%hu}\r\n", reading_array_position, output[reading_array_position]);
			SerialOutputString(string_to_send, &USART1_PORT);
		}

		if (threshold_breach_count >= BREACHES)
		{
			SerialOutputString("Breach Limit Reached!!!\r\n", &USART1_PORT);
			set_detected();
			return;
		}

		reading_count++;
	}

}

void sweep_routine()
{
	uint16_t previousSet[READINGS_PER_SWEEP];
	previousSet[0] = 0;
	uint16_t currentSet[READINGS_PER_SWEEP];


	//crude_omni_sweep(&previousSet, &currentSet);
//	while (get_sweep_flag() == 1)
//	{
//		crude_omni_sweep(&previousSet, &currentSet);
//		transfer_array_data(&currentSet, &previousSet, READINGS_PER_SWEEP);
//	}

//
//	omni_sweep(RL, NULL, &previousSet);
//	while(get_sweep_flag() == 1)
//	{
//		omni_sweep(LR, &previousSet, &currentSet);
//		memcpy(previousSet, currentSet, sizeof(previousSet));
//		omni_sweep(RL, &previousSet, &currentSet);
//		memcpy(previousSet, currentSet, sizeof(previousSet));
////		omni_sweep(LR, &previousSet, &currentSet);
////		*previousSet = &currentSet;
//	}

	sweep(NULL, &previousSet);


	while (get_status() == RED)
	{
		sweep(&previousSet, &currentSet);
		transfer_array_data(&currentSet, &previousSet, READINGS_PER_SWEEP);
	}

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	uint8_t buffer[32];
	if (htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		uint16_t IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 1)
			rise_time = IC_Val1;
		else
			last_period = IC_Val1 - rise_time;

		diff = IC_Val1 - last_capture;
		last_capture = IC_Val1;
	}
}

