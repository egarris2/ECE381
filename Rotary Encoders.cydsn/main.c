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
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    SW1_ISR_StartEx(volumeChange);
    for(;;)
    {
        /* Place your application code here. */
    }
}
CY_ISR(volumeChange)
{
   LED1_Write(~LED1_Read());
   SW1_ClearInterrupt();
   ENC_ISR_ClearInterrupt();
}
/* [] END OF FILE */
