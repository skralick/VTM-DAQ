#include "usb.h"
#include "usb_host_msd.h"
#include "usb_host_msd_scsi.h"
#include "FSIO.h"


// *****************************************************************************
// *****************************************************************************
// Configuration Bits
// *****************************************************************************
// *****************************************************************************

#ifndef OVERRIDE_CONFIG_BITS
        
    #pragma config UPLLEN   = ON            // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config ICESEL       = ICS_PGx1  // ICE/ICD Comm Channel Select
    #pragma config DEBUG        = OFF       // Debugger Disabled for Starter Kit

    #pragma config FNOSC        = PRIPLL	// Oscillator selection
    #pragma config POSCMOD      = XT	// Primary oscillator mode
    #pragma config FPLLIDIV     = DIV_2	// PLL input divider
    #pragma config FPLLODIV     = DIV_1	// PLL output divider
    #pragma config FPBDIV       = DIV_1	// Peripheral bus clock divider
    #pragma config FSOSCEN      = OFF	// Secondary oscillator enable

    #pragma config FCANIO = OFF //required for CAN see mx7ck rm

    #pragma config FWDTEN = OFF // Watchdog Timer enable
    #pragma config WDTPS = PS1 // Watchdog Timer Postscale

#endif // OVERRIDE_CONFIG_BITS

#define getPBusClock() 80000000
#define UART_BAUD 9600
#define SYS_FREQ (80000000L)

// Global variables
BYTE CAN1MessageFifoArea[2 * 8 * 16];
BYTE CAN2MessageFifoArea[2 * 8 * 16];
int prevButton1;
int prevButton2;
int counter = 0;

FSFILE * myFile;
BYTE myData[512];
size_t numBytes;
volatile BOOL deviceAttached;
BOOL shouldLog;
BOOL shouldStop;
//int count;
BYTE angularRateInfo[8];
BOOL angularRateInfoRec;
BYTE accelerationSensor[8];
BOOL accelerationSensorRec;
BYTE HRaccelerationSensor[8];
BOOL HRaccelerationSensorRec;
static unsigned int analogIn1;
static unsigned int analogIn2;
BOOL analogRead;

unsigned short rpm;
unsigned short tp;
unsigned short map;
unsigned short at;
unsigned short et;
unsigned short la1;
unsigned short fp;
unsigned short op;
unsigned short egt1;
unsigned short launch;
unsigned short ntrl;
unsigned short bp;
unsigned short bpf1;
unsigned short batV;
unsigned short ldSpd;
unsigned short lgSpd;
unsigned short rdSpd;
unsigned short rgSpd;
unsigned short runTime;
unsigned short fuel;
BOOL motec0Read, motec1Read, motec2Read, motec3Read, motec4Read;

//enum used for the finite state machine implemented in this logger
typedef enum{
    init, startLog, log, stopLog, wait

}STATE;

int logNum;
STATE state;

void initUART1(){
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);//configure uart for rx and tx
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);//configure for interrupts
    UARTSetLineControl(UART1,  UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);//set uart line options
    UARTSetDataRate(UART1, getPBusClock(), UART_BAUD);//data rate 9600 baud and pbus 10MHz
    UARTEnable(UART1, UART_PERIPHERAL | UART_RX | UART_TX | UART_ENABLE); //enable the uart for tx rx
    while(!UARTTransmitterIsReady(UART1));
}

void sendString(char* string){
    int i = 0;
    while(string[i]){
        while(!UARTTransmitterIsReady(UART1));
        UARTSendDataByte(UART1, string[i]);
        i++;
    }
}

//return true on rising edge of BTN1 for sending from can2 to can1
BOOL checkForButton1(){
    //look for rising edge in button1
    if((PORTG & 0x40) != 0x40){
        prevButton1 = 0;
        return FALSE;
    }else if( prevButton1 == 0){
        DelayMs(20);
        if(PORTG & 0x40){
            prevButton1 = 1;
            return TRUE;
        }
        return FALSE;
    }else{
        prevButton1 = 1;
        return FALSE;
    }
    return FALSE;
}
BOOL checkForButton2(){
    //look for rising edge in button1
    if((PORTG & 0x80) != 0x80){
        prevButton2 = 0;
        return FALSE;
    }else if( prevButton2 == 0){
        DelayMs(20);
        if(PORTG & 0x80){
            prevButton2 = 1;
            return TRUE;
        }
        return FALSE;
    }else{
        prevButton2 = 1;
        return FALSE;
    }
    return FALSE;
}
void writeMessageToUART1(CANRxMessageBuffer *message)
{


    char string[20];
    int eidE = message->msgEID.IDE;
    int eidD = message->msgEID.DLC;
    int eidEid = ((message->msgEID.EID) & 0xFFFF);

    BYTE data[8];
    int i;
    for(i = 0; i < 8; i++){
        data[i] = message->data[i];
    }
    int messageWord[4];
    for(i = 0; i < 4; i++){
        messageWord[i] = message->messageWord[i];
    }
    //sprintf(string, "EID: %x %x", eidE, eidD);
    //sendString(string);
    //CAN_MSG_EID tempEid = message->msgEID;
    //UARTSendDataByte(UART1, data[0]);
    //UARTSendDataByte(UART1, data[1]);
    //int output = (data[1] << 8) | data[0];
    //UARTSendDataByte(UART1, '\n');
    //sprintf(string, "eid: %x\n\r",eidEid);
    //*string = "g12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678\n";
    if(eidEid == 0x2d30){
        int i;
        for(i = 0; i < 8; i++){
            accelerationSensor[i] = data[i];
        }
        accelerationSensorRec = TRUE;
    }else if(eidEid == 0x2a30){
        int i;
        for(i = 0; i < 8; i++){
            angularRateInfo[i] = data[i];
        }
        angularRateInfoRec = TRUE;
    }else if(eidEid == 0x0030){
        int i;
        for(i = 0; i < 8; i++){
            HRaccelerationSensor[i] = data[i];
        }
        HRaccelerationSensorRec = TRUE;
    }
    //sendString(string);


    //sprintf(string, "EID: %x", eidEid);
    //sendString(string);

    //for(i = 0; i < 8; i++){
    //    char temp[50];
        //sprintf(temp, "data%d: %x ", i, data[i]);
        //sendString(temp);
    //}
    //sendString("\n\r");
}

void writeCan2Msg(CANRxMessageBuffer *message){

    BYTE data[8];
    int i;
    for(i = 0; i < 8; i++){
        data[i] = message->data[i];
    }

    unsigned int sid = message->msgSID.SID;

    if(sid == 0x6f0){
        rpm = data[0] << 8 | data[1];
        tp = data[2] << 8 | data[3];
        map = data[4] << 8 | data[5];
        at = data[6] << 8 | data[7];
        motec0Read = TRUE;
    }else if(sid == 0x6f1){
        et = data[0] << 8 | data[1];
        la1 = data[2] << 8 | data[3];
        fp = data[4] << 8 | data[5];
        op = data[6] << 8 | data[7];
        motec1Read = TRUE;
    }else if(sid == 0x6f2){
        egt1 = data[0] << 8 | data[1];
        launch = data[2] << 8 | data[3];
        ntrl = data[4] << 8 | data[5];
        bp = data[6] << 8 | data[7];
        motec2Read = TRUE;
    }else if(sid == 0x6f3){
        bpf1 = data[0] << 8 | data[1];
        batV = data[2] << 8 | data[3];
        ldSpd = data[4] << 8 | data[5];
        lgSpd = data[6] << 8 | data[7];
        motec3Read = TRUE;
    }else if(sid == 0x6f4){
        rdSpd = data[0] << 8 | data[1];
        rgSpd = data[2] << 8 | data[3];
        runTime = data[4] << 8 | data[5];
        motec4Read = TRUE;
        fuel = data[6] << 8| data[7];
    }

}
//the next few functions are general for i2c
//all these functions were stolen from Kralick_Lab4
void initI2CBus(I2C_MODULE id, int pBusFrq, int i2cFrq){
    I2CConfigure(id, 0);
    I2CSetFrequency(id, pBusFrq, i2cFrq);
    I2CEnable(id, TRUE);
}
void i2cStart(I2C_MODULE id){
    while( !I2CBusIsIdle(id) );
    I2CStart(id);
    while ( !(I2CGetStatus(id) & I2C_START) );
}void i2cSendByte(I2C_MODULE id, BYTE data){
    while(!I2CTransmitterIsReady(id));//maybe comment this out
    I2CSendByte(id, data);
    //I2C_RESULT temp = I2CSendByte(id, data);
    //temp;
    while(!I2CTransmissionHasCompleted(id));
    while(!I2CByteWasAcknowledged(id));
}
void i2cRepeatedStart(I2C_MODULE id){
    I2CRepeatStart(id);
    while ( !(I2CGetStatus(id) & I2C_START) );
}
void i2cStop(I2C_MODULE id){
    I2CStop(id);
    while ( !(I2CGetStatus(id) & I2C_STOP) );
}
BYTE i2cRecieveByte(I2C_MODULE id, BOOL ack){
    I2CReceiverEnable(id, TRUE);
    while(!I2CReceivedDataIsAvailable(id));
    I2CAcknowledgeByte(id, ack);
    while(!I2CAcknowledgeHasCompleted(id)) ;
    BYTE result = I2CGetByte(id);
    return result;
}
//setup I2C to talk to the eeprom
void initI2CEEPROM(){
    initI2CBus(I2C2, getPBusClock(), 400000);
}
//write a byte to eeprom
void writeEEPROM(short address, BYTE data){
    i2cStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1);
    i2cSendByte(I2C2, (address & 0xFF00)>> 8);
    i2cSendByte(I2C2, address & 0xFF);
    i2cSendByte(I2C2, data);
    i2cStop(I2C2);
}
//write several bytes to the eeprom
void writeMultiEEPROM(short address, BYTE *data, int length){
    i2cStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1);
    BYTE high = (address & 0xFF00) >> 8;
    BYTE low = address & 0xFF;
    i2cSendByte(I2C2, high);
    i2cSendByte(I2C2, low);
    int i;
    for(i = 0; i < length; i++){
        i2cSendByte(I2C2, data[i]);
    }
    i2cStop(I2C2);
}
//read a byte from the eeprom
BYTE readEEPROM(BYTE address){
    i2cStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1);
    i2cSendByte(I2C2, (address & 0xFF00)>> 8);
    i2cSendByte(I2C2, address & 0xFF);
    i2cRepeatedStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1 | 0x01);
    BYTE temp = i2cRecieveByte(I2C2, FALSE);
    i2cStop(I2C2);
    return temp;
}
//read multiple bytes from the eeprom
BOOL readMultiEEPROM(BYTE address, BYTE *data, int length){
    BOOL keepReading = TRUE;
    i2cStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1);
    i2cSendByte(I2C2, (address & 0xFF00)>> 8);
    i2cSendByte(I2C2, address & 0xFF);
    i2cRepeatedStart(I2C2);
    i2cSendByte(I2C2, 0x50 << 1 | 0x01);
    int i;
    for(i = 0; i < length-1; i++){
        *(data + i) = i2cRecieveByte(I2C2, TRUE);
        if(*(data+i)  == 0xFF){
            keepReading = FALSE;
        }
        if(keepReading == FALSE){
            *(data +i) = 0xFF;
        }
    }
    *(data + length - 1) = i2cRecieveByte(I2C2, FALSE);
    i2cStop(I2C2);
    return keepReading;
}

int main(void)
{
    int  value;

    value = SYSTEMConfigWaitStatesAndPB( GetSystemClock() );

    // Enable the cache for the best performance
    CheKseg0CacheOn();

    // Initialize GPIO for BTN1 and LED1
    TRISGCLR = 0xF000;   // Clear PortG bit associated with LED1
    ODCGCLR  = 0xF000;   // Normal output for LED1 (not open drain)
    TRISGSET = 0x40;     // Set PortG bit associated with BTN1
    LATGCLR = 0xF000;

    CAN1Init();//CAN1 is configured to accept all EIDs
    CAN2Init();
    DelayInit();

    initUART1();
    prevButton1 = 0;
    prevButton2 = 0;


    OpenTimer2(T2_ON | T2_IDLE_CON | T2_SOURCE_INT | T2_PS_1_256 | T2_GATE_OFF, 3125);//changed so its 100Hz

    INTEnableSystemMultiVectoredInt();
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_1);
    INTClearFlag(INT_T2);
    INTEnable(INT_T2, INT_ENABLED);


    value = OSCCON;
    while (!(value & 0x00000020))
    {
        value = OSCCON;    // Wait for PLL lock to stabilize
    }

    deviceAttached = FALSE;

    //Initialize the stack
    USBInitialize(0);

    shouldLog = FALSE;
    shouldStop = FALSE;
    //count = 0;
    angularRateInfoRec = FALSE;
    accelerationSensorRec = FALSE;
    HRaccelerationSensorRec = FALSE;
    analogRead = FALSE;
    analogIn1 = 0;
    analogIn2 = 0;

    INTSetVectorPriority(INT_ADC_VECTOR, INT_PRIORITY_LEVEL_1);
    INTEnable(INT_AD1, INT_ENABLED);
    INTClearFlag(INT_AD1);  //clear flag to avoid spurious interrupt

    //current statys of ADC is that sampling 0-3.3V from JA-03 and JA-04 with some weird things happing in the data, it could just be a bad joystick or weird data things happing

    //init timer 3 to convert adc at 100hz
    OpenTimer3(T3_ON|T3_PS_1_256|T3_SOURCE_INT, 1562);

    //set ADC to sample analog pin2
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 | ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN6);

    //open ADC to give unsigned integers and start conversions on timer3
    //use 0v and 3.3V take one sample per interrupt, use analog pin2
    OpenADC10(ADC_MODULE_ON|ADC_FORMAT_INTG32|ADC_CLK_TMR|ADC_AUTO_SAMPLING_ON ,
        ADC_VREF_AVDD_AVSS |ADC_SAMPLES_PER_INT_2 | ADC_ALT_INPUT_ON,
        ADC_CONV_CLK_PB|ADC_CONV_CLK_Tcy,
        ENABLE_AN4_ANA | ENABLE_AN6_ANA,
        SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN5 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15);

    EnableADC10();
    //AD1CON1SET = 0x4;
    //TRISBCLR = 5 << 7;//for adc this was also screwing up the adc making things be randomly 1ff
    //PORTBSET = 1 << 6; //this will make adc respoint with binary haha

    state = init;
    logNum = 0;

    initI2CEEPROM();
    short addy = 0x0000;
    BYTE num = 0x00;

    while(1)
    {
        //USB stack process function
        USBTasks();

        switch(state){
            case init:
                if(checkForButton1()){
                    state = startLog;
                }
                break;
            case startLog:
                //if thumbdrive is plugged in
                if(USBHostMSDSCSIMediaDetect())
                {
                    deviceAttached = TRUE;

                    //now a device is attached
                    //See if the device is attached and in the right format
                    if(FSInit())
                    {
                        //Opening a file in mode "w" will create the file if it doesn't
                        //  exist.  If the file does exist it will delete the old file
                        //  and create a new one that is blank.
                        char nameString[20];
                        logNum = readEEPROM(addy);
                        sprintf(nameString, "test%d.csv", logNum);
                        myFile = FSfopen(nameString,"w");
                        char string[350];
                        sprintf(string, "pitch(deg/sec),roll(deg/sec),yaw(deg/sec),lat(m/s^2),long(m/s^2),vert(m/s^2),latHR(m/s^2),longHR(m/s^2),vertHR(m/s^2),current sensor(V),rpm, tps(percent),ect(degF),lambda,fuel pres,egt(?),launch,neutral,brake pres,brake pres filtered,BattVolt(V),ld speed, lg speed,rd speed,rg speed,run time(second),fuel used\n");
                        FSfwrite(string,1, strlen(string),myFile);

                        state = log;
                    }
                }
                break;
            case log:
                if(checkForButton2()){
                    state = stopLog;
                }
                break;
            case stopLog:
                //Always make sure to close the file so that the data gets
                //  written to the drive.
                FSfwrite("endFile", 1, 7, myFile);
                FSfclose(myFile);
                state = wait;
                logNum++;
                writeEEPROM(addy, logNum);
                break;
            case wait:
                USBTasks();
                if(checkForButton1()){
                    state = startLog;
                }
                break;
            default:
                state = wait;
                break;
        }

//        if(checkForButton1()){
//            //if thumbdrive is plugged in
//            if(USBHostMSDSCSIMediaDetect() && !shouldLog && shouldStop == FALSE)
//            {
//                deviceAttached = TRUE;
//
//                //now a device is attached
//                //See if the device is attached and in the right format
//                if(FSInit())
//                {
//                    //Opening a file in mode "w" will create the file if it doesn't
//                    //  exist.  If the file does exist it will delete the old file
//                    //  and create a new one that is blank.
//                    myFile = FSfopen("test.csv","w");
//                    char string[350];
//                    sprintf(string, "pitch(deg/sec),roll(deg/sec),yaw(deg/sec),lat(m/s^2),long(m/s^2),vert(m/s^2),latHR(m/s^2),longHR(m/s^2),vertHR(m/s^2),current sensor(V),rpm, tps(percent),lambda,fuel pres,egt(?),launch,neutral,brake pres,brake pres filtered,BattVolt(V),ld speed, lg speed,rd speed,rg speed,run time(second),fuel used\n");
//                    FSfwrite(string,1, strlen(string),myFile);
//
//                    shouldLog = TRUE;
//
//                    //Just sit here until the device is removed.
//                    //while(deviceAttached == TRUE)
//                    //{
//                    //    USBTasks();
//                    //}
//                }
//            }
//        }
//        if (shouldStop && shouldLog){
//            //Always make sure to close the file so that the data gets
//            //  written to the drive.
//            FSfwrite("endFile", 1, 7, myFile);
//            FSfclose(myFile);
//            shouldLog = FALSE;
//            //Just sit here until the device is removed.
//            while(deviceAttached == TRUE)
//            {
//                USBTasks();
//            }
//        }
        // Update LED 1 to show program is running
        if(PORTG & 0x40){  // check BTN1
            LATGSET = 1 << 12; // LED1 on
        }
        else{
            LATGCLR = 1 << 12; // LED1 off
        }

        //If button 1 is pressed increment the counter and send the counter out of CAN2
        //with the current configuration using EID this doesnt work (messages send are using SID)
//        if(checkForButton1()){
//            counter++;
//            CAN2TxSendLEDMsg(counter);
//        }
//        if(checkForButton2()){
//            //count = 150;
//            shouldStop = TRUE;
//        }
        CANRxMessageBuffer* CAN1RxMessage = CAN1RxMsgProcess();
        if(CAN1RxMessage){
            writeMessageToUART1(CAN1RxMessage);
            //sprintf(string, "CAN1: The button has been pushed %d times\n\r", CAN1RxMessage->data[0]);
        }
        CANRxMessageBuffer* CAN2RxMessage = CAN2RxMsgProcess();
        if(CAN2RxMessage){
            writeCan2Msg(CAN2RxMessage);
            //sprintf(string, "CAN1: The button has been pushed %d times\n\r", CAN1RxMessage->data[0]);
        }
    }
    return 0;
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.

            //This means that the device was removed
            deviceAttached = FALSE;
            return TRUE;

        case EVENT_HUB_ATTACH:
            return TRUE;

        case EVENT_UNSUPPORTED_DEVICE:
            return TRUE;

        case EVENT_CANNOT_ENUMERATE:
            return TRUE;

        case EVENT_CLIENT_INIT_ERROR:
            return TRUE;

        case EVENT_OUT_OF_MEMORY:
            return TRUE;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            return TRUE;

        default:
            break;
    }

    return FALSE;
}


void __ISR(_TIMER_2_VECTOR, ipl1) Timer2_ISR(void) {
    if (INTGetFlag(INT_T2)){
        if (state == log){
            double pitch, roll, yaw;
            double latAcc, longAcc, vertAcc;
            double HRlatAcc, HRlongAcc, HRvertAcc;
            char angString[40];
            char accString[40];
            char HRaccString[40];
            char analogString[40];
            char motec0String[40];
            char motec1String[40];
            char motec2String[40];
            char motec3String[40];
            char motec4String[40];
            if(angularRateInfoRec){
                pitch = (((double)(angularRateInfo[1] << 8 | angularRateInfo[0])) /128) - 250;
                roll = (((double)(angularRateInfo[3] << 8 | angularRateInfo[2])) /128) - 250;
                yaw = (((double)(angularRateInfo[5] << 8 | angularRateInfo[4])) /128) - 250;
                angularRateInfoRec = FALSE;
                sprintf(angString, "%.6f,%.6f,%.6f,", pitch, roll, yaw);
            }else{
                sprintf(angString, " , , ,");
            }
            if(accelerationSensorRec){
                latAcc = (((double)(accelerationSensor[1] << 8 | accelerationSensor[0])) * .01) - 320;
                longAcc = (((double)(accelerationSensor[3] << 8 | accelerationSensor[2])) * .01) - 320;
                vertAcc = (((double)(accelerationSensor[5] << 8 | accelerationSensor[4])) * .01) - 320;
                accelerationSensorRec = FALSE;
                sprintf(accString, "%.6f,%.6f,%.6f,", latAcc, longAcc, vertAcc);
            }else{
                sprintf(accString, " , , ,");
            }
            if(HRaccelerationSensorRec){
                HRlatAcc = (((double)(HRaccelerationSensor[1] << 8 | HRaccelerationSensor[0])) * .000599) - 19.62;
                HRlongAcc = (((double)(HRaccelerationSensor[3] << 8 | HRaccelerationSensor[2])) * .000599) - 19.62;
                HRvertAcc = (((double)(HRaccelerationSensor[5] << 8 | HRaccelerationSensor[4])) * .000599) - 19.62;
                HRaccelerationSensorRec = FALSE;
                sprintf(HRaccString, "%.6f,%.6f,%.6f,", HRlatAcc, HRlongAcc, HRvertAcc);
            }else{
                sprintf(HRaccString, " , , ,");
            }
            if(analogRead){
                analogRead = FALSE;
                double temp = (double)analogIn2 * 3.3 / 1024;
                sprintf(analogString, "%.6f,", temp);
            }else{
                sprintf(analogString, ",");
            }

            if(motec0Read){
                int t_rpm = rpm;
                double t_tps = (double) tp * .1;
                sprintf(motec0String, "%d, %.6f,", t_rpm, t_tps );
                motec0Read = FALSE;
            }else{
                sprintf(motec0String, " , ,");
            }
            if(motec1Read){
                double t_engineTemp = (double) et * .1;
                double t_lambda1 = (double) la1 * .001;
                int t_fuelPress = fp;
                sprintf(motec1String, "%.6f,%.6f,%d,", t_engineTemp, t_lambda1, t_fuelPress);
                motec1Read = FALSE;
            }else{
                sprintf(motec1String, " , , ,");
            }
            if(motec2Read){
                double t_egt1 = (double)egt1 *.1;
                int t_userLaunch = launch;//not sure scaling
                int t_userNtrl = ntrl;//not sure scaling
                int t_brakePres = bp;//not sure scaling
                sprintf(motec2String, "%.6f,%d,%d,%d,", t_egt1, t_userLaunch, t_userNtrl, t_brakePres);
                motec2Read = FALSE;
            }else{
                sprintf(motec2String, " , , , ,");
            }
            if(motec3Read){
                int t_brakePresFil = bpf1;//not sure scaling
                double t_batV = (double)batV * .01;
                double t_ldspd = (double)ldSpd * .1;
                double t_lgspd = (double)lgSpd * .1;
                sprintf(motec3String, "%d,%.6f,%.6f,%.6f,", t_brakePresFil, t_batV, t_ldspd, t_lgspd);
                motec3Read = FALSE;
            }else{
                sprintf(motec3String, " , , , ,");
            }
            if(motec4Read){
                double t_rdspd = (double)rdSpd * .1;
                double t_rgspd = (double)rgSpd * .1;
                float t_runTime = runTime * .1;//not sure scaling
                sprintf(motec4String, "%.6f,%.6f,%.6f, %d\n", t_rdspd, t_rgspd, t_runTime, fuel);
                motec4Read = FALSE;
            }else{
                sprintf(motec4String, " , , , \n");
            }
            FSfwrite(angString,1, strlen(angString),myFile);
            FSfwrite(accString,1, strlen(accString),myFile);
            FSfwrite(HRaccString,1, strlen(HRaccString),myFile);
            FSfwrite(analogString,1, strlen(analogString),myFile);
            FSfwrite(motec0String,1, strlen(motec0String),myFile);
            FSfwrite(motec1String,1, strlen(motec1String),myFile);
            FSfwrite(motec2String,1, strlen(motec2String),myFile);
            FSfwrite(motec3String,1, strlen(motec3String),myFile);
            FSfwrite(motec4String,1, strlen(motec4String),myFile);
            //sprintf(string, "%s%s%s", angString, accString, HRaccString);
            //sprintf(string, "test,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", pitch, roll, yaw, latAcc, longAcc, vertAcc, HRlatAcc, HRlongAcc, HRvertAcc);
            //int a = sizeof(string) / sizeof(char);
            //int a = strlen(string);
            //FSfwrite(string,1, a,myFile);
            //count ++;
        }

        INTClearFlag(INT_T2);
    }
}

//adding the following stopped the error
//undefined reference to `_p32mxsk_putc
//that was caused by using sprintf
void _mon_putc(char c) {}


void __attribute__((vector(_ADC_VECTOR), interrupt(ipl4), nomips16)) ADC_ISR(void)
{
    if (INTGetFlag(INT_AD1)){
        //when conversion is complete write ADC word to the variable so it can be displayed
        analogIn1 = ReadADC10(0);
        analogIn2 = ReadADC10(1);
        analogRead = TRUE;
        INTClearFlag(INT_AD1);
    }
}