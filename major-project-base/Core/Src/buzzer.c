#include "buzzer.h"

#include "main.h"
#include "math.h"

int val = 0;

uint32_t var;

uint32_t sine_val[100];

#define PI 3.1415926

//produces sine wave in the sin_val array (turns on or off based on val input)
void calcsin (int val)
{
	for (int i=0; i<100; i++)
	{
		sine_val[i] = val * ((sin(i*2*PI/100) + 1)*(4096/2));
	}
}

uint32_t get_buzzer()
{
	return val;
}

//toggles whether the buzzer is on or off
void toggleBuzzer(DAC_HandleTypeDef hdac1){
	if (!val)
	{
		val = 1;
	}
	else
	{
		val = 0;
	}

	calcsin(val);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sine_val, 100, DAC_ALIGN_12B_R);
}
