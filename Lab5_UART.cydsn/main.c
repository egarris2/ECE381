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
#include <string.h>

CY_ISR_PROTO(byteReceived);
     
char menu = 0x30;
char subMenu = 0x30;
char stringNum = 0x00;
int updateFlag;
int i = 0;
int x = 0;
int entry = 0;


char string1[17] = "";
char string2[17] = "";
char string3[17] = "";
char string4[17] = "";

char input[17] = "";
char nextByte;

int main(void)
{
    LCD_Start();
    UART_Start();
    isr_1_StartEx(byteReceived);
    UART_PutString("\n\rSelect an option\n\r1) Write\n\r2) Read\n\r3) Display \n\r");
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        if(updateFlag){
            switch(menu){
                case 0x30 :
                        UART_PutString("\n\rSelect an option\n\r1) Write\n\r2) Read\n\r3) Display \n\r");
                    break;
                case 0x31 :
                        UART_PutString("\n\rWhich String would you like to write to?\n\r");
                        menu = 0x34;
                    break;
                case 0x32 :
                        UART_PutString("\n\rWhich String would you like to read?\n\r");
                        menu = 0x035;
                    break;
                case 0x33 :
                        UART_PutString("\n\rWhich String would you like to display?\n\r");
                    break;
                        
                case 0x34 :
                        if(entry == 0){
                            UART_PutString("\n\rWriting to string:\n\r");
                            entry = 1;
                        }
                        
                        else{
                            for (i = 0; i < 17; i++){
                                switch (stringNum){
                                case 0x01 :
                                        string1[i] = input[i];
                                    break;
                                case 0x02 :
                                        string2[i] = input[i];
                                    break;
                                case 0x03 :
                                        string3[i] = input[i];
                                    break;
                                case 0x04 :
                                        string4[i] = input[i];
                                    break;
                                }      
                            }
                            entry = 0;
                            menu = 0x30;
                        }
                break;
                case 0x35 :
                    if(entry == 0){
                        UART_PutString("\n\rReading String:\n\r");
                        entry = 1;
                    }
                    
                    else{
                            switch (stringNum){
                            case 0x01 :
                                    UART_PutString(string1);
                                break;
                            case 0x02 :
                                    UART_PutString(string2);
                                break;
                            case 0x03 :
                                    UART_PutString(string3);
                                break;
                            case 0x04 :
                                    UART_PutString(string4);
                                break;
                            }      
                        }
                        entry = 0;
                        menu = 0x30;
                break;
            }
        updateFlag = 0;
        }         
    }
}

CY_ISR(byteReceived){
    nextByte = UART_GetChar();
    UART_PutChar(nextByte);
    input[x] = nextByte;
    x++;
    
    if (nextByte == 0x0D){
        x = 0;
        UART_PutString("\n\r");
        updateFlag = 1;
    }
    
    else{
        if(menu == 0x30){
            menu = input[0];
        }   
        
        else if(menu == 0x34 && entry == 0){
            stringNum = input[0] - 0x30;
        }
        
        else if(menu == 0x35 && entry == 0){
            stringNum = input[0] - 0x30;
        }
    }
}

/* [] END OF FILE */
