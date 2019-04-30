// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 11/20/2018 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground






#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "SysTick.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds

void PortF_Init(void){
	volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x20;  //initialize port F clock
	delay++;
	GPIO_PORTF_DEN_R |= 0x0E;   //enables PF1, PF2, PF3
	GPIO_PORTF_DIR_R |= 0x0E;   //establish PF1, PF2, PF3 as outputs
}

int x_frog = 50;
int x_car = 50;
int x_car2 = 50;
int x_truck = 50;

int main(void){
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(NVIC_ST_CURRENT_R);
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();
	PortF_Init();
	

  //Output_Init();
  ST7735_FillScreen(0x0000);            // set screen to black
  
  ST7735_DrawBitmap(50,50, frog1, 24, 18);
	ST7735_DrawBitmap(50,110,car,22,20);
	ST7735_DrawBitmap(50,130,car,22,20);
	ST7735_DrawBitmap(50,20,truck,35,15);
	EnableInterrupts();
	/*ST7735_DrawBitmap(50,90,snake,37,19);
	
	ST7735_DrawBitmap(0,70,ground,16,14);
	ST7735_DrawBitmap(14,70,ground,16,14);
	ST7735_DrawBitmap(28,70,ground,16,14);
	ST7735_DrawBitmap(42,70,ground,16,14);
	ST7735_DrawBitmap(56,70,ground,16,14);
	ST7735_DrawBitmap(60,70,ground,16,14);
	ST7735_DrawBitmap(74,70,ground,16,14);
	ST7735_DrawBitmap(88,70,ground,16,14);
	ST7735_DrawBitmap(92,70,ground,16,14);
	ST7735_DrawBitmap(106,70,ground,16,14);
	ST7735_DrawBitmap(120,70,ground,16,14);
	ST7735_DrawBitmap(50,70,snake,37,19);*/
  Delay100ms(100);              // delay 5 sec at 80 MHz
  /*ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  LCD_OutDec(1234);*/
  while(1){
  }

}


// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void SysTick_Handler(void)
{
	GPIO_PORTF_DATA_R ^= 0x02;
	GPIO_PORTF_DATA_R ^= 0x02;
	ST7735_FillScreen(0x0000); 
	x_frog = (x_frog+1)%120;
	x_car = (x_car+1)%120;
	x_car2 = (x_car2 + 2) %120;
	x_truck = (x_truck + 2) %120;
	ST7735_DrawBitmap(x_frog, 50, frog1, 24, 18);
	ST7735_DrawBitmap(x_car,110,car,22,20);
	ST7735_DrawBitmap(x_car2,130,car,22,20);
	ST7735_DrawBitmap(x_truck,20,truck,35,15);
	GPIO_PORTF_DATA_R ^= 0x02;
}
