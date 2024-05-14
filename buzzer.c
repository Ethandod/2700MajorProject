#include "main.h"
#include "math.h"
#include "buzzer.h"

int val = 0;

uint32_t var;

uint32_t sine_val[100];

#define PI 3.1415926


void calcsin (int val)
{
	for (int i=0; i<100; i++)
	{
		sine_val[i] = val * ((sin(i*2*PI/100) + 1)*(4096/2));
	}
}

void toggleBuzzer(DAC_HandleTypeDef hdac1){
	val = 1 - val;

	calcsin(val);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sine_val, 100, DAC_ALIGN_12B_R);
}
