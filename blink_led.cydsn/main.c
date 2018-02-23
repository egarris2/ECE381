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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
int ix = 0;
    for(;;)
    {
        /* Place your application code here. */
        LED1_Write(1);
for(ix = 0; ix <300000; ++ix);
    LED1_Write(0);
        for(ix = 0; ix < 300000; ++ix);
        
    }
}

/* [] END OF FILE */
