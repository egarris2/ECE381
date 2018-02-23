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
CY_ISR_PROTO(changeDuty);

uint16 prev;
uint16 current;
uint16 direction;
uint16 numTransitions = 0;
uint16 volumeChangeFlag = 0;
uint16 updateFrequencyFlag = 0;
float divider[] = {12,13,15,17,20,24,30,40,60,120,133,150,171,200,240,300,400,600,1200};
uint16 counter = 0;
uint16 divpos = 18;
float freq = 0;
char str[16];
float duty = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    Counter_1_Start();
    ENC_ISR_StartEx(frequencyChange);
    CHG_DUTY_ISR_StartEx(changeDuty);
    
    LCD_ClearDisplay();
    LCD_PrintString("Frequency");
    LCD_PrintDecUint16(freq);
    LCD_Position(1,0);
    LCD_PrintString("Duty Cycle");
    LCD_PrintDecUint16(Counter_1_ReadCompare());
    LCD_PrintString("%");
    
    for(;;)
    { 
        if(updateFrequencyFlag){
            LCD_ClearDisplay();           
            updateFrequencyFlag = 0;
            CLK_SetDividerValue(divider[divpos]);
            freq = 120000/divider[divpos];
            sprintf(str,"%8.1f",freq);
            LCD_PrintString("Freq:");
            LCD_PrintString(str);
            LCD_Position(1,0);
            LCD_PrintString("Duty:");
            LCD_PrintDecUint16(Counter_1_ReadCompare());
            LCD_PrintString("%");
        }
    }
}

CY_ISR(frequencyChange)
{   
    CyDelay(1);
    counter++;
    current = StatReg_Read();
    
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

CY_ISR(changeDuty)
{
    updateFrequencyFlag =1;
    if(Counter_1_ReadCompare() == 50){
        Counter_1_WriteCompare(25);
    }
    
    else
        Counter_1_WriteCompare(50);
    
    CHG_DUTY_ClearInterrupt();
}
    