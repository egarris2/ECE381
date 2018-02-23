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

int latch1 = 0;
int latch2 = 0;

int main(void)
{
    CyGlobalIntEnable; 

    for(;;)
    { 
        if(Pin1_Read() == 0) 
            latch1 = 0;
    
        if(Pin2_Read() == 0) 
            latch2 = 0;

        if (Pin1_Read() == 1 && latch1 == 0)
        {  
            latch1 = 1;
            if (LED1_Read() == 0)
            {
                LED1_Write(1);
            }
            else 
            {
                LED1_Write(0);
            }
        }
        
        if (Pin2_Read() == 1 && latch2 == 0)
        {
            latch2 = 2;
            if (LED2_Read() == 0)
            {
                LED2_Write(1);
            }
            else
            {
                LED2_Write(0);
            }
        }     
    }
}

/*
for(;;)
    { 

        if (Pin1_Read() == 1)
        {
            if (LED1_Read() == 0)
            {
                LED1_Write(1);
            }
            else 
            {
                LED1_Write(0);
            }
        }
        if (Pin2_Read() == 1)
        {
            if (LED2_Read() == 0)
            {
                LED2_Write(1);
            }
            else
            {
                LED2_Write(0);
            }
        }     
    }
}
*/
