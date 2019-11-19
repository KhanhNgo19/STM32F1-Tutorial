/*
Topic: Generating an interrupt using the the Systick timer

Program Description: Having a main thread where each time I set the input pin PA0 
The LED PC13 is set HIGH, at the same time in a parallel thread the pin PA13 get 
Toggle based on the interrupt generated by the systick interrupt

*/


#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"                   // GPIO library



int main(void)
{
	init_GP(PA,0,IN,I_PP);
	init_GP(PA,12,OUT50,O_GP_PP);
	init_GP(PC,13,OUT50,O_GP_PP);
	
	__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = 7200000-1; /// Set the relad value (Or having 0.1 sec delay as Clock is 72Mhz)
	SysTick->VAL = 0; // Initialize value
	SysTick->CTRL = 7; // Enabling the Systick timer and also the interrupt
	__enable_irq();
	
	while(1)
	{
		W_GP(PA,12,R_GP(PA,0));
	}
	
}

void SysTick_Handler(void)
{
	toggle_GP(PC,13);
}


