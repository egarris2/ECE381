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
CY_ISR_PROTO(volumeChange);

uint16 prev;
uint16 current;
uint16 direction;
uint16 numTransitions = 0;
uint16 volumeChangeFlag = 0;
uint16 updateDisplayFlag = 0;
uint16 volume = 51;
uint16 counter = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    ENC_ISR_StartEx(volumeChange);
    
    LCD_ClearDisplay();
    LCD_PrintString("Volume:");
    LCD_Position(1,0);
    LCD_PrintDecUint16(volume);
    
    for(;;)
    {
        if(Pin_1_Read()){
            Pin_3_Write(~Pin_3_Read());
        }
            
        
        if(updateDisplayFlag){
            LCD_ClearDisplay();
            LCD_PrintString("Volume:");
            LCD_Position(1,0);
            LCD_PrintDecUint16(volume);
            updateDisplayFlag = 0;
        }
    }
}

CY_ISR(volumeChange)
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
        if(volume < 100){
            volume++;
        }
        updateDisplayFlag = 1;
    }
    
    else if(StatReg_Read() == 0 && direction == 0){
        if(volume > 0){
            volume--;
        }
        updateDisplayFlag = 1;
    }
    
    prev = current;
    ENC_ClearInterrupt();
}
/* [] END OF FILE */
