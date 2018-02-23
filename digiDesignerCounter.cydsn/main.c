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
    int i = 0;
    for(;;)
    {
        /* Place your application code here. */
       
for(ix = 0; ix <256; ix++){
    CNTR_Write(ix);
        for(i = 0; i < 600000; i++);
}
      
    }
}

/* [] END OF FILE */
