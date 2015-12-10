/******************************************************************************
* Project Name		: VTM16 Current Sensors
* File Name			: main.c
* Version 			: **
* Device Used		: CY8C5888LTI-LP097
* Software Used		: PSoC Creator 3.1 SP2
* Compiler    		: ARM GCC 4.8.4, ARM RVDS Generic, ARM MDK Generic
* Related Hardware	: CY8CKIT059 PSoC 5 LP Prototyping Kit 
*******************************************************************************/

#include <device.h>
#include "stdio.h"

/* Project Defines */
#define FALSE  0
#define TRUE   1
#define TRANSMIT_BUFFER_SIZE  16
#define I2C_BUFFER_SIZE 0x0C
#define I2C_RW_AREA_SIZE 0x00


//Need to use ezi2c_get_activity to develop a mechanism for data coherency
//Only write to buffer if it is not busy
void main()
{
    /* Variable to store ADC result */
    int16 Output;
    int32 data[6];
    /* Variable to store UART received character */
    uint8 Ch;
    /* Variable used to send emulated data */
    uint8 EmulatedData;
    /* Flags used to store transmit data commands */
    uint8 ContinuouslySendData;
    uint8 SendSingleByte;
    uint8 SendEmulatedData;
    //Set Up i2c variables
    uint8 i2cBuffer[I2C_BUFFER_SIZE];
    uint8 tempStatus;
    /* Transmit Buffer */
    char TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    
    
    int i;
    /* Start the components */
    ADC_SAR_Seq_1_Start();
    UART_1_Start();
    EZI2C_1_Start();
    EZI2C_1_SetBuffer1(I2C_BUFFER_SIZE, I2C_RW_AREA_SIZE, i2cBuffer); 
    
    /* Initialize Variables */
    ContinuouslySendData = FALSE;
    SendSingleByte = FALSE;
    SendEmulatedData = FALSE;
    EmulatedData = 0;
    
    /* Start the ADC conversion */
    ADC_SAR_Seq_1_StartConvert();
    
    /* Send message to verify COM port is connected properly */
    UART_1_PutString("COM Port Open");
    
    for(;;)
    {        
        /* Non-blocking call to get the latest data recieved  */
        Ch = UART_1_GetChar();
        
        /* Set flags based on UART command */
        switch(Ch)
        {
            case 0:
                /* No new data was recieved */
                break;
            case 'C':
            case 'c':
                SendSingleByte = TRUE;
                break;
            case 'S':
            case 's':
                ContinuouslySendData = TRUE;
                break;
            case 'X':
            case 'x':
                ContinuouslySendData = FALSE;
                break;
            case 'E':
            case 'e':
                SendEmulatedData = TRUE;
                break;
            default:
                /* Place error handling code here */
                break;    
        }
        
        /* Check to see if an ADC conversion has completed */
        //At some point should switch to interrupts
        if(ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_RETURN_STATUS))
        {
            /* Use the GetResult16 API to get an 8 bit unsigned result in
             * single ended mode.  The API CountsTo_mVolts is then used
             * to convert the ADC counts into mV before transmitting via
             * the UART.  See the datasheet API description for more
             * details */
            i = 0;
            for(i = 0;i<6;i++)
            {
            Output = ADC_SAR_Seq_1_GetResult16(i);
            data[i] = ADC_SAR_Seq_1_CountsTo_mVolts(Output);
            }
            //Need to split data into 12 individual bytes for storage in the i2c transmit buffer
            tempStatus = EZI2C_1_GetActivity(); 
            if(tempStatus && EZI2C_1_STATUS_BUSY)
            {
            //set data intoi2c transmit buffer
            }
            /* Send data based on last UART command */
            if(SendSingleByte || ContinuouslySendData)
            {
                /* Format ADC result for transmition */
                sprintf(TransmitBuffer, "Overall: %ld mV\r\n", data[0]);
                /* Send out the data */
                UART_1_PutString(TransmitBuffer);
                
                sprintf(TransmitBuffer, "Production: %ld mV\r\n", data[1]);
                UART_1_PutString(TransmitBuffer);      
                sprintf(TransmitBuffer, "Fpump: %ld mV\r\n", data[2]);
                UART_1_PutString(TransmitBuffer);                  
                sprintf(TransmitBuffer, "Finj: %ld mV\r\n", data[3]);
                UART_1_PutString(TransmitBuffer);                 
                sprintf(TransmitBuffer, "Ignition: %ld mV\r\n", data[4]);
                UART_1_PutString(TransmitBuffer);                   
                sprintf(TransmitBuffer, "RefV: %ld mV\r\n\n\n\n\n\n\r", data[5]);
                UART_1_PutString(TransmitBuffer);                   
                /* Reset the send once flag */
                SendSingleByte = FALSE;
            }
            else if(SendEmulatedData)
            {
                /* Format ADC result for transmition */
                sprintf(TransmitBuffer, "Emulated Data: %x \r\n", EmulatedData);
                /* Send out the data */
                UART_1_PutString(TransmitBuffer);
                EmulatedData++;
                /* Reset the send once flag */
                SendEmulatedData = FALSE;   
            }
        }
    }
}


/* [] END OF FILE */
