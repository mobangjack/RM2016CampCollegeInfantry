#include "pwm.h"

void PWM_Init(PWM* pwm)
{
	pwm->period = 2500;
	pwm->pulse = 1500;
	pwm->us = 0;
	pwm->out = 0;
}

void PWM_Calc(PWM* pwm)
{
	pwm->out = (pwm->us < pwm->pulse) ? 1 : 0;
	pwm->us = (pwm->us < pwm->period) ? (pwm->us+1) : 0;
}

