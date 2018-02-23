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
CY_ISR_PROTO(button);
int lcdFlag = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_StartEx(button);
    LCD_Char_1_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Counter_1_Start();
    LCD_Char_1_ClearDisplay();
    LCD_Char_1_PrintString("Freq: ");
    LCD_Char_1_PrintNumber((500000)/(Counter_1_ReadPeriod()+1));
    LCD_Char_1_Position(1,0);
    LCD_Char_1_PrintString("Duty: ");
    LCD_Char_1_PrintNumber(Counter_1_ReadCompare());
    LCD_Char_1_PrintString("%");
    for(;;)
    {
        if(lcdFlag == 1){
            LCD_Char_1_ClearDisplay();
            LCD_Char_1_PrintString("Freq: ");
            LCD_Char_1_PrintNumber((500000)/(Counter_1_ReadPeriod()+1));
            LCD_Char_1_PrintString("Hz");
            LCD_Char_1_Position(1,0);
            LCD_Char_1_PrintString("Duty: ");
            LCD_Char_1_PrintNumber(100/((Counter_1_ReadPeriod()+1)/(Counter_1_ReadCompare())));
            LCD_Char_1_PrintString("%");
            lcdFlag = 0;
        }
    }
}

CY_ISR(button){
    if(Pin_3_Read() == 1){
        Counter_1_WriteCompare(125);
        Counter_1_WritePeriod(249);
    }
    
    else{
        Counter_1_WriteCompare(25);
        Counter_1_WritePeriod(99);
    }
    lcdFlag = 1;
    
    Pin_3_ClearInterrupt();
}

/* [] END OF FILE */
