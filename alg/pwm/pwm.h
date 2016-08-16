#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

typedef struct
{
	uint32_t period;
	uint32_t pulse;
	uint32_t us;
	uint8_t out;
}PWM;

#define PWM_NEW(PERIOD,PULSE) {PERIOD,PULSE,0,0}

void PWM_Init(PWM* pwm);
void PWM_Calc(PWM* pwm);

#endif


