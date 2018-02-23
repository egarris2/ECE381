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

uint16 count = 50;
int latch1 = 0;
int latch2 = 0;

int main(void)
{
    LCD_Start();
    
    CyGlobalIntEnable; 

    for(;;)
    {   
        LCD_Position(0,0);
        LCD_PrintString("Count");
        LCD_Position(1,0);
        LCD_PrintDecUint16(count);
        LCD_Position(1, 8);
        LCD_PrintHexUint16(count);
        
        if(Pin1_Read() == 0)
            latch1 = 0;
        
        if(Pin2_Read() == 0)
            latch2 = 0;
        
        if (Pin1_Read() == 1 && latch1 == 0)
        {
            latch1 = 1;
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Incrementing");
            CyDelay(500);
            count++;
            LCD_ClearDisplay();
        }
        if (Pin2_Read() == 1 && latch2 == 0)
        {
            latch2 = 1;
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Decrementing");
            CyDelay(500);
            count--;
            LCD_ClearDisplay();
        }
    }
}

/* [] END OF FILE */
