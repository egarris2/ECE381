/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
CY_ISR_PROTO(frequencyChange);

uint16 prev;
uint16 current;
uint16 direction;
uint16 numTransitions = 0;
uint16 volumeChangeFlag = 0;
uint16 updateFrequencyFlag = 0;
float divider[] = {24,26.666,30,34.285,40,48,60,80,120,240,266.666,300,342.857,400,480,600,800,1200,2400};
uint16 counter = 0;
uint16 divpos = 18;
float freq = 0;
char str[16];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    ENC_ISR_StartEx(frequencyChange);
    
    LCD_ClearDisplay();
    LCD_PrintString("Frequency");
    LCD_Position(1,0);
    LCD_PrintDecUint16(freq);
    
    for(;;)
    { 
        if(updateFrequencyFlag){
            LCD_ClearDisplay();           
            updateFrequencyFlag = 0;
            CLK_SetDivider(divider[divpos]);
            freq = 2400000/divider[divpos];
            sprintf(str,"%8.1f",freq);
            LCD_PrintString("Freq:");
            LCD_PrintString(str);
        }
    }
}

CY_ISR(frequencyChange)
{   
    CyDelay(1);
    counter++;
    current = StatReg_Read();
    //Pin_2_Write(~Pin_2_Read());
    
    if(StatReg_Read() != 0){
        if(current > prev){
            direction = 1;
        }
        else{
            direction = 0;
        }
    }
    
    if(StatReg_Read() == 0 && direction == 1){
        if(divpos > 0){
            divpos--;
        }
        updateFrequencyFlag = 1;
    }
    
    else if(StatReg_Read() == 0 && direction == 0){
        if(divpos < 18){
            divpos++;
        }
        updateFrequencyFlag = 1;
    }
    
    prev = current;
    ENC_ClearInterrupt();
}

