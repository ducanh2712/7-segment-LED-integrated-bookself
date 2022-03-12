#ifndef _PWM_H_
#define _PWM_H_

void PWM_Init (int ck);
void PWM_Start ();
void PWM_End ();
void PWM_Set_Duty (char duty);
void TimerOverflow();

#endif