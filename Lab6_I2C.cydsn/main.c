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

#define numOfChars 79

CY_ISR_PROTO(byteReceived);

int updateFlag;
int i = 0;
int x = 0;
int y = 0;
int entry = 0;

char holding[numOfChars] = "";
char input[numOfChars] = "";
char empty[numOfChars] = "";
char nextByte;

int main(void)
{
    UART_Start();
    isr_1_StartEx(byteReceived);
    CyGlobalIntEnable; 
    
    for(;;)
    {
        if(updateFlag == 1){
            UART_PutString(holding);
            UART_PutString("\n");
            updateFlag = 0;

        }
    }
}

CY_ISR(byteReceived){
    //gets incoming byte from UART and stores it
    nextByte = UART_GetChar(); 
    //if the byte is a printable character & the string isn't full
    if(nextByte > 31 && nextByte < 127 && x < numOfChars){
        //echo character back to host computer 
        UART_PutChar(nextByte);
        //store character into an input buffer
        input[x] = nextByte;
        //increment to next buffer location
        x++;
    }
    
    //if byte is non printable
    else{
        //if the byte is a delete perform rubout sequence
        if(nextByte == 0x7F && x > 0){
            UART_PutChar(0x08);
            UART_PutChar(0x20);
            UART_PutChar(0x08);
            //sets input buffer location back 1 to reflect host readout
            x--;     
            //replaces deleted character with null
            input[x] = 0;
        }
        
        //if carriage return (enter) is sent
        else if(nextByte == 0x0D){
            //new line and carriage return
            UART_PutString("\n");
            UART_PutChar(nextByte);
            
            //add carriage return deliminator to input buffer
            input[x] = 0x0D;
            
            //store input array in a holding array
            for (i = 0; i < numOfChars; i++){
                holding[i] = input[i];
            }
            
            //clear input array
            for(y = 0;y < numOfChars; y++){
                input[y] = empty[y];
            }
            
            //return input buffer write location to beginning
            x = 0;
            //set flag for action in the main code
            updateFlag = 1;
        }
        
        //if byte is not printable or if input buffer is full..
        //or if trying to delete past 0 send bell to host computer
        else{
            UART_PutChar(7);
        }
    }
}
    