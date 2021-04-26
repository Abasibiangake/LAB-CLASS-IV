// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 11, 2014

// Lab 8
//      Jon Valvano and Ramesh Yerraballi
//      November 21, 2013

// ***** 1. Pre-processor Directives Section *****
//#include "TExaS.h"
#include "tm4c123gh6pm.h"
#define GPIO_PORTE_DATA_R           (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R            (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R          (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R            (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R            (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R             (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R          (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R           (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R              (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOE          0x10  // port E Clock Gating Control


// ***** 2. Global Declarations Section *****
unsigned long In;
// FUNCTION PROTOTYPES: Each subroutine defined
//void DisableInterrupts(void); // Disable interrupts
//void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10 k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).

void Delay(void) {unsigned long volatile time;
	time = 727240*200/91;
	while(time){
		time--;
	}
}

int main(void){ unsigned long volatile delay;
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
//  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1);  // activate grader and set system clock to 80 MHz
  SYSCTL_RCGC2_R |= 0x10;                     // activate Port E clock
	delay = SYSCTL_RCGC2_R;          // allow time for clock to stabilize, no need to unlock PE1-0
	GPIO_PORTE_AMSEL_R &= ~0x03;               //disable analog for PE0 and PE1
	GPIO_PORTE_DIR_R |= 0x02;                    //make PE1 output 
	GPIO_PORTE_DIR_R &= ~0x01;                   // make PE0 input 
	GPIO_PORTE_AFSEL_R &= ~0x03;                    // no alternate function for PE0 and PE1
	GPIO_PORTE_DEN_R |= 0x03;                  // enable port PE1 and PE0
	
        
//  EnableInterrupts();           // enable interrupts for the grader
  while(1){
		Delay();
		In = GPIO_PORTE_DATA_R&0x01;
		if (In == 0x01) {  // 0x01 means switch is pressed and LED is turned off initially
			GPIO_PORTE_DATA_R ^= 0x02;  // Toggle LED
		}
		else // 0x10 means switch not pressed
		{
			GPIO_PORTE_DATA_R = 0x02;
		}
		
  }
  
}
