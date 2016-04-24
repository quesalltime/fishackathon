/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1789
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"


#define     VER_110_5CN     1




/*  all of this is use inside eeprom(256 bytes) to save data */
#define EROM_FIRST_POWERON         230      /*  =1ST */
#define EROM_MDQ_COUNT             233      /*   */
#define EROM_MDQ_CURSOR            234      /*   */



#define ARDUINO_SID       0x10      /*  this is slave ID = 0x08>>2 */



#define EPR64_SID         0xA0      /*  this is slave ID = 0x80+0x20+A0,A1,A0 = 0xA0 */
#define EPR64_MAX_SIZE    0x1FFF    /*  24LC64 = 0x2000 */
#define EPR16_SID         0xA0      /*  this is slave ID = 0x80+0x20+A0,A1,A0 = 0xA0 */
#define EPR16_MAX_SIZE    0x7FF     /*  24LC16 = 0x0800 = 2048  */




/*----------------------------------------------------------------------------*/
typedef struct {
    uint16_t Rec_Temp;
    uint16_t Rec_NH3;
    uint16_t Rec_PH;
    uint16_t Rec_TDS;
    uint16_t Rec_HGca;
    uint16_t Rec_GHmg;
    uint16_t Rec_DO;
    uint16_t Rec_ORP;
} REC_MESURE;

REC_MESURE REC_METER_VAL;

/*  need pass to other API used */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8_t RTC_Year;
    uint8_t RTC_Month;
    uint8_t RTC_Day;

    uint8_t RTC_Hour;
    uint8_t RTC_Min;
    uint8_t RTC_Sec;
} RTC_YMDHMS;
    
    
/*  Use to count RTC Sec */
uint32_t RTC_SecCount = 0;
uint16_t RTC_DayCount = 0;


RTC_YMDHMS RTC_Clock;

uint8_t PWM_1MS_COUNT = 0;
uint8_t RUN_PWM_FLAG = 0;
uint8_t MES_TDS_FLAG = 0;
uint8_t MES_DO_FLAG = 0;

        
/*  Next upload count */
uint32_t NUL_SecCount_offset = 300;
uint32_t NUL_SecCount = 300;
uint16_t NUL_DayCount = 0;


uint8_t Flag_Mesure_Test = 0;
uint8_t Loop_Mesure_Test = 0;
uint16_t OneCount_MT = 0;

uint8_t MT_LoopTime = 0;
uint16_t MT_SecTime = 0;


/*
ISE = PH,NH3,ORP,MG,CA
DO
TDS   */
#define     ADC_CH_MAX  3
uint8_t ADC_CH[ADC_CH_MAX] = {
MESURE_ISE,
MESURE_TDS,
MESURE_DO,   };


/*  Temp vol */
uint8_t BufferGetTemp[2];


/* used to save UART receive DATA string buffer, max = 32 */
uint8_t BufferStr[32];
/* used to save UART receive DATA string buffer length */
uint8_t BufferLenght = 0;



/* read uart data step status
 * = 0 not in receive mode
 * = 1 start goto receive mode
 * = 2 end receive, and to do analysis, and to do something
 *  */
uint8_t Flag_RxStr = 0;     

uint32_t ADC_Vol_cal = 0;  /* cal avg */
uint16_t ADC_Vol = 0;
uint16_t ADC_Volm = 0;  /*for TDS used plus and ma*/
        
uint8_t    LoopA = 0;
        
//uint16_t ADC_Vol = 0;

/* = 0 no run install setup, can't upload data
 * = 1 install ok, can uplaod data  */
uint8_t    FirstTimeSetup = 0;

/* normal high   */
uint8_t    exINT_Flag = 0;
/*
 = 0x01 check AP
 = 0x02 check CNCT
 = 0x04 run REG
 = 0x08 run RTC adj
 */
uint8_t    exINT_Mode = 0x80;

uint8_t    SR_0xA0_ADO_Error = 0;
uint8_t    SR_0xA1_ADO_Request = 0;

//I2C_MESSAGE_STATUS I2CMS;
uint8_t BufferRec[32];

#define REE_STRIP    0x01       /* no insert strip */
#define REE_MESURE   0x02       /* mesure vol out range, unknow */
#define REE_ADRUINO  0x04       /* extent EEPROM, error */
#define REE_EEPROM   0x08       /* extent EEPROM, error */
uint8_t Rec_Error_Event = 0;    /*  = 0 OK, = 1 NG */

#define WSE_TEMP     0x01
#define WSE_PH       0x02
#define WSE_NH3      0x04
#define WSE_TDS      0x08
#define WSE_ORP      0x10
#define WSE_DO       0x20
#define WSE_GHCA     0x40
#define WSE_GHMG     0x80
uint8_t What_Strip_Error = 0;   /*  = 0 OK, = 1 Error */



/*  Mesure sort list*/
/*  TEMP */ 
/*  PH */
/*  NH3 */
/*  TDS */
/*  ORP  */
/*  DO */
/*  GHca */
/*  GHmg*/



/*  low nibble = PIC, hight nibble = ADO    */
#define EF_TEMP     0x01
#define EF_MESURE   0x02
#define EF_I2C      0x10
#define EF_AP       0x20
#define EF_SERVE    0x40
uint8_t ErrorFlag = 0;








/*----------------------------------------------------------------------------*/
void Decode_RS232_CMD(uint8_t *BStr, uint8_t Strlen);

void RUN_MESURE(uint8_t WhatStrip);

void UPLOAD_MESURE_REC(void);
void COVERT_ADC2HLB(uint8_t *Buffer, uint16_t ADC_VOL);



/*  need pass to other API used */
/*----------------------------------------------------------------------------*/
void Print_CHLN(void);
void Print_BreakLine(void);
void Print_String(uint8_t const *BStr, uint8_t chln);
void Print_uint16Str(uint16_t InputVol, uint8_t Chgln);
void Print_OCT2Str(uint8_t InputVol);
void Print_HEX2Str(uint8_t InputVol, uint8_t Chgln);




/*----------------------------------------------------------------------------*/
uint8_t STR2HEX(uint8_t *BStr, uint8_t NumPoint);
uint8_t ASCII_OCT2HEX(uint8_t ASCII_OCT);



/*----------------------------------------------------------------------------*/
uint8_t DS18B20_Reset(void);
void DS18B20_Write(uint8_t vByte);
uint8_t DS18B20_Read(void);
void DS18B20_GetTemp(uint8_t *rTwoByte);



/*----------------------------------------------------------------------------*/
void Delay5us(void);
void Delay100us(void);
void Delay480us(void);
void Delay_us(uint16_t uDelay);




/*----------------------------------------------------------------------------*/
void Convert_HMS(uint32_t iCount, RTC_YMDHMS *rClock);
void Print_HMS(RTC_YMDHMS rClock);
void Convert_YMD(uint16_t iCount, RTC_YMDHMS *rClock);
void Print_YMD(RTC_YMDHMS rClock);
uint8_t Convert_2HB(uint8_t iCount);


/*----------------------------------------------------------------------------*/
void TEST_PIC_ALL(void);

void print_RTC(void);

#if 0
void TEST_READ_ADO_16B(void);
#endif

void PIC_SYNC_ADO_RTC(void);
void PIC_SYNC_ADO_ULSR(void);

uint8_t Covert_BDC_2_OCT(uint8_t iBDC);
uint16_t Covert_Month_2_Day(uint16_t iMonth);




//=============================================================================
void I2C_Dealy_1(void);
void I2C_Dealy_2(void);
void I2C_START_BIT(void);
void I2C_STOP_BIT(void);
uint8_t I2C_WRITE_8BIT(unsigned char value);
uint8_t I2C_READ_8BIT(uint8_t acknowledge);
uint8_t I2C_BYTE_WRITE(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l,uint8_t value);
uint8_t I2C_PAGE_WRITE(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l,uint8_t Size, uint8_t *value);
uint8_t I2C_RANDOM_READ(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l);
void I2C_Sequential_READ(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l, uint8_t Size, uint8_t *value);

uint8_t I2C_mWrite(uint8_t *value, uint8_t Size, uint8_t slave_addr);
void I2C_mREAD(uint8_t *value, uint8_t Size, uint8_t slave_addr);


void I2C_TEST_01(void);
void I2C_TEST_02(void);
void I2C_TEST_10(void);

uint8_t Save_QMD_EEPROM(uint8_t *DataBuffer);
uint8_t Load_QMD_EEPROM(uint8_t *DataBuffer);


//=============================================================================
void check_ADO_I2C(void);

/*----------------------------------------------
    Main application
----------------------------------------------*/
void main(void) {

uint16_t loop_tds = 0;
        
/*----------------------------------------------*/  
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    
    
/*----------------------------------------------
 * node -- Initial 
----------------------------------------------*/
    
    /* Power ON, turn on Green LED  */
    LED_GREEN_SetHigh();
    
    MESURE_ISE_SetAnalogMode();
    
    PIC_SDA_SetDigitalOutput();
    PIC_SCL_SetDigitalOutput();
    PIC_SDA_SetHigh();
    PIC_SCL_SetHigh();

//    for(LoopA = 0; LoopA <ADC_CH_MAX; LoopA++)
//        ADC_StartConversion(ADC_CH[LoopA]);

//    ADC_StartConversion(MESURE_ISE);

    
    
    TEMP_DQ_SetHigh();
   
    DAC1_SetOutput(0xC0);   /* ADNREF, 0x28 = 0.50V  */

    UPLOAD_MESURE_REC();    /* when power, do one time upload data   */

    EN_AD8220_SetHigh();
    
    
    
/*----------------------------------------------
 * node -- Self test, for Pic
----------------------------------------------*/  
    TEST_PIC_ALL();



    
    

    
    
/*----------------------------------------------
 * node -- Main Loop
----------------------------------------------*/  
    while (1) {
        // Add your application code
        
        
        
#if 1  /*  UART receive DATA  */      
        if(CheckRxOneByteFlag() == 1)
        {
           if(RC1REG == '<')
           {
                Flag_RxStr = 1;
           }
           else
           {
                if(RC1REG == '>')
                {
                    Flag_RxStr = 2;

                    Decode_RS232_CMD(BufferStr,BufferLenght);
                
                    for(LoopA = 0; LoopA < 32; LoopA++)
                        *(BufferStr+LoopA) =0;

                    BufferLenght = 0;
                    Flag_RxStr = 0;
                }                    

                if(Flag_RxStr == 1)
                {
                    BufferStr[BufferLenght++] = RC1REG;
                }
            }    
        }
#endif

        
        
        
#if 1  /*  Every 1MS Event, for TDS  */          
        else if(RUN_PWM_FLAG == 1)
        {
            if(Check_1MSFlag() == 1)
            {
                PWM_1MS_COUNT++;

                if(PWM_1MS_COUNT & 0x01 )
                    TDS_PWM_SetHigh();
                else 
                    TDS_PWM_SetLow();
                
                for(loop_tds = 0; loop_tds < 3; loop_tds++)
                   ADC_Vol_cal = PWM_1MS_COUNT;

                
#if 1
                if(MES_TDS_FLAG == 1)
                {
                    if(PWM_1MS_COUNT == 0xFD )
                    {
                        ADC_Vol_cal = 0;
                        for(loop_tds = 0; loop_tds < 10; loop_tds++)
                            ADC_Vol_cal += (uint32_t)(ADC_GetConversion(MESURE_TDS)/16);

                        ADC_Vol = ADC_Vol_cal / 10;

    //                    Print_uint16Str(ADC_Vol);
                    }
                    else if(PWM_1MS_COUNT == 0xFE)
                    {
                        ADC_Vol_cal = 0;
                        for(loop_tds = 0; loop_tds < 10; loop_tds++)
                            ADC_Vol_cal += (uint32_t)(ADC_GetConversion(MESURE_TDS)/16);

                        ADC_Volm = ADC_Vol_cal / 10;

                        Print_String("TDS = $", 0);
    //                    Print_uint16Str(ADC_Volm);
    //                    Print_String("                $", 0);

                        if(ADC_Volm > ADC_Vol)
                            Print_uint16Str((ADC_Volm-ADC_Vol),1);
                        else
                            Print_uint16Str((ADC_Vol-ADC_Volm),1);

                        RUN_PWM_FLAG = 0;
                        MES_TDS_FLAG = 1;
                    }      
                }
#endif

#if 0
                if(MES_DO_FLAG == 1)
                {
                    if(PWM_1MS_COUNT == 0xFD )
                    {
                        ADC_Vol_cal = 0;
                        for(loop_tds = 0; loop_tds < 10; loop_tds++)
                            ADC_Vol_cal += (uint32_t)(ADC_GetConversion(MESURE_DO)/16);

                        ADC_Vol = ADC_Vol_cal / 10;

    //                    Print_uint16Str(ADC_Vol);
                    }
                    else if(PWM_1MS_COUNT == 0xFE)
                    {
                        ADC_Vol_cal = 0;
                        for(loop_tds = 0; loop_tds < 10; loop_tds++)
                            ADC_Vol_cal += (uint32_t)(ADC_GetConversion(MESURE_DO)/16);

                        ADC_Volm = ADC_Vol_cal / 10;

                        Print_String("DO = $", 0);
                        Print_uint16Str(ADC_Volm,1);
                       Print_String("                $", 0);

                        if(ADC_Volm > ADC_Vol)
                            Print_uint16Str((ADC_Volm-ADC_Vol),1);
                        else
                            Print_uint16Str((ADC_Vol-ADC_Volm),1);

                        RUN_PWM_FLAG = 0;
                        MES_DO_FLAG = 1;
                    }      
                }
#endif

            }
        }
#endif
        
        
        
        
#if 1  /*  Every Sec Event  */          
        else if(CheckOneSecFlag() == 1)
        {
            RTC_SecCount++;
            LED_GREEN_Toggle();
            
            
            /*  check low nibble = PIC, hight nibble = ADO    */
            if((ErrorFlag & 0xF0) != 0)
                LED_RED_Toggle();
            else if((ErrorFlag & 0x0F) != 0)
                LED_RED_SetHigh();
            else
                LED_RED_SetLow();
                
            if(RTC_SecCount >= (uint32_t)86400)
            {
                RTC_DayCount++;
                RTC_SecCount = 0;
                NUL_SecCount -= (uint32_t)86400;
            }
  
#if 1          
            if(RTC_SecCount >= NUL_SecCount)
            {
                UPLOAD_MESURE_REC();   
                NUL_SecCount = RTC_SecCount + NUL_SecCount_offset;
            }
#endif
            
            if(Flag_Mesure_Test == 1)
            {                
                if(OneCount_MT < MT_LoopTime*5)
                {
                    RUN_MESURE(Loop_Mesure_Test++);              

                    if(Loop_Mesure_Test == 5)
                    {
                        Loop_Mesure_Test = 0;
                        Flag_Mesure_Test = 0;
    //                    Print_CHLN();
                    }
                }

                OneCount_MT++;
                if(OneCount_MT >= (MT_SecTime + MT_LoopTime*5))
                    OneCount_MT = 0;
            }
            
        }
#endif



        
#if 1  /*  exINT Event  */          
        else if(ADO_INT_GetValue() == 0)
        {
            if(exINT_Flag == 0)
            {
                Print_String("exINT enable$", 1);
            }
            
            exINT_Flag = 1;


            /*  read 0xA0, 0xA1 2 bytes data */
            *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
            *(BufferRec+1) = 0xA0;    /* = address */
            *(BufferRec+2) = 0x02;    /* = length  */
//            I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//            I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
            I2C_mWrite(BufferRec, 3+1, ARDUINO_SID);
            I2C_mREAD(BufferRec, 2, ARDUINO_SID);
            
            SR_0xA0_ADO_Error = *BufferRec;
            SR_0xA1_ADO_Request = *(BufferRec+1);
            
/*  print 0xA0, 0xA1 2 bytes data */
            Print_String("SR_0xA0_ADO_Error =0x$", 0);
            Print_HEX2Str(SR_0xA0_ADO_Error, 1);
            Print_String("SR_0xA1_ADO_Request =0x$", 0);
            Print_HEX2Str(SR_0xA1_ADO_Request, 1);
            

/*  first time power on adruino self-test */
            if(exINT_Mode == 0x80)
            {
                Print_String("Check First time ADO TEST$", 1);
            }
            /*  check ap */
            else if(exINT_Mode == 0x01)
            {
                if(SR_0xA0_ADO_Error == 0)
                    FirstTimeSetup = 1;
            }
            /*  CNCT */
            else if(exINT_Mode == 0x02)
            {
            }
            /*  REG */
            else if(exINT_Mode == 0x04)
            {
            }
            /*  ADJ */
            else if(exINT_Mode == 0x08)
            {
                if(SR_0xA1_ADO_Request == 0X01)
                {
                    Print_String("NEED ADJ RTC CLOCK$", 1);
                    PIC_SYNC_ADO_RTC();
                    exINT_Mode = 0;
                    exINT_Flag = 0;   
                }
            }

/* check ADO Error */
            Print_CHLN();            
            if(SR_0xA0_ADO_Error == 0)
            {
                Print_String("RESULT OK$", 1);
                FirstTimeSetup = 1;
            }
            else
            {
                Print_String("RESULT NG, Error = 0x$", 0); /* = 0x10*/
                Print_HEX2Str(SR_0xA0_ADO_Error, 1);
            }

            
            
/* check ADO Request */
            if(SR_0xA1_ADO_Request & 0x01)
            {
                Print_String("NEED ADJ RTC CLOCK$", 1);
                PIC_SYNC_ADO_RTC();
            }
            
            if(SR_0xA1_ADO_Request & 0X02)
            {
                Print_String("NEED CHANGE SAMPLE RATE$", 1);
                PIC_SYNC_ADO_ULSR();

                MT_LoopTime = 1;
                MT_SecTime = 1;

                Flag_Mesure_Test = 1;
                Loop_Mesure_Test = 0;
                OneCount_MT = 0;
            }

            
            exINT_Flag = 0;            
            exINT_Mode = 0;
            
        }
#endif
           
        
        
    }
}

/*----------------------------------------------------------------------------*/
void Decode_RS232_CMD(uint8_t *BStr, uint8_t Strlen)
{

uint8_t Adr = 0;
uint8_t Data = 0;


    /* Volt = set DAC Volt, Hex 2Bytes  */
    if(*(BStr+0) == 'V')
    {
        Data = STR2HEX(BStr, 2);
        DAC1_SetOutput(Data);
        
        Print_CHLN();
        Print_String("Set DAC =$", 0);
        Print_HEX2Str(Data, 1);
    }



    /* for Qc  */
    else if((*(BStr+0) == 'T')&&
            (*(BStr+1) == 'E')&&
            (*(BStr+2) == 'S')&&
            (*(BStr+3) == 'T')&&
            (*(BStr+4) == 'A')&&
            (*(BStr+5) == 'L')&&
            (*(BStr+6) == 'L')  )

    {
        TEST_PIC_ALL();
    }


#if 1
    /* for Test: upload data  */
    else if((*(BStr+0) == 'U')&&
            (*(BStr+1) == 'P')&&
            (*(BStr+2) == 'L')&&
            (*(BStr+3) == 'O')&&
            (*(BStr+1) == 'A')&&
            (*(BStr+2) == 'D')  )
    {
        UPLOAD_MESURE_REC(); 
        Print_String("for Test: upload data!$", 1);
    }
#endif




    /* DAC = Read Temp, PH, NH3  */
    else if(*(BStr+0) == 'M')
    {
        if(*(BStr+2) == 'T')  /*  TEMP */ 
        {
          DS18B20_GetTemp(BufferGetTemp);
        }
        else if(*(BStr+2) == 'P')  /*  PH */ 
        {
          RUN_MESURE(0);
        }
        else if(*(BStr+2) == 'N')  /*  NH3 */ 
        {
          RUN_MESURE(1);
        }
        else if(*(BStr+2) == 'O')  /*  ORP  */ 
        {
          RUN_MESURE(2);
        }
        else if(*(BStr+2) == 'C')  /*  GHca */ 
        {
          RUN_MESURE(4);
        }
        else if(*(BStr+2) == 'M')  /*  GHmg*/ 
        {
          RUN_MESURE(3);
        }
        else if(*(BStr+2) == 'S')  /*  TDS */ 
        {
          RUN_PWM_FLAG = (1 - RUN_PWM_FLAG);

          if(RUN_PWM_FLAG == 1)
          {
              MES_TDS_FLAG = 1;
              PWM_1MS_COUNT = 0;
          }
          RUN_MESURE(5);
        }
        else if(*(BStr+2) == 'D')  /*  DO */ 
        {
//          MES_DO_FLAG = 1;

          RUN_MESURE(6);
        }
    }

    /* Write = Write EEPROM, Hex 2Bytes  */
    else if((*(BStr+0) == 'W')&&
            (*(BStr+1) == 'R')&&
            (*(BStr+2) == 'I')&&
            (*(BStr+3) == 'T')&&
            (*(BStr+4) == 'E') )
    {
        Adr = STR2HEX(BStr, 2);
        Data = STR2HEX(BStr, 5);
        
        DATAEE_WriteByte(Adr, Data); 
        
        Print_CHLN();
        Print_String("Write EEPROM Adr:$", 0);
        Print_HEX2Str(Adr, 1);
        Print_String("Data:$", 0);
        Print_HEX2Str(Data, 1);
    }

    /* Read = Read EEPROM, Hex 2Bytes  */
    else if((*(BStr+0) == 'R')&&
            (*(BStr+1) == 'E')&&
            (*(BStr+2) == 'A')&&
            (*(BStr+3) == 'D') )
    {
        Adr = STR2HEX(BStr, 2);
        
        Data = DATAEE_ReadByte(Adr); 
        
        Print_CHLN();
        Print_String("Read EEPROM Adr:$", 0);
        Print_HEX2Str(Adr, 1);
        Print_String("Data:$", 0);
        Print_HEX2Str(Data, 1);
    }

    /* I2C = Pass string to ardiuno  */
    else if((*(BStr+0) == 'I')&&
            (*(BStr+1) == '2')&&
            (*(BStr+2) == 'C') )

    { 
//        I2C_MasterWrite(BStr+2, Strlen-1, 0x08, &I2CMS);
        I2C_mWrite(BStr+2, Strlen-1, ARDUINO_SID);
        
        Print_CHLN();
        
        I2C_mREAD(BufferRec, 6, ARDUINO_SID);
//        I2C_MasterRead(BufferRec, 6, 0x08, &I2CMS);     /* for test  */
        *(BufferRec + 6) = '$';
//            __delay_ms(10);

        Print_CHLN();
        Print_String("I2C String to Arduino$", 1);
        Print_String(BufferRec, 1);
    }

    /* Time = Set RTC, Check RTC  */
    else if((*(BStr+0) == 'R')&&
            (*(BStr+1) == 'T')&&
            (*(BStr+2) == 'C') )

    {
        print_RTC();
    }

    /* Set SSID  */
    else if((*(BStr+0) == 'S')&&
            (*(BStr+1) == 'S')&&
            (*(BStr+2) == 'I')&&    /**/
            (*(BStr+3) == 'D') )
    {
        *(BStr+2) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+3) = 0x11;           /* = address */
        *(BStr+4) = Strlen-5;       /* = length  */
//        I2C_MasterWrite(BStr+2, Strlen-1, 0x08, &I2CMS);
        I2C_mWrite(BStr+2, Strlen-1, ARDUINO_SID);

        Print_CHLN();
        Print_String("SET SSID OK$", 1);
    }

    /* Set Password  */
    else if((*(BStr+0) == 'P')&&
            (*(BStr+1) == 'A')&&
            (*(BStr+2) == 'S')&&
            (*(BStr+3) == 'S')&&
            (*(BStr+4) == 'W')&&
            (*(BStr+5) == 'O')&&
            (*(BStr+6) == 'R')&&    /**/
            (*(BStr+7) == 'D') )
    {
        *(BStr+6) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+7) = 0x31;           /* = address */
        *(BStr+8) = Strlen-9;       /* = length  */
//        I2C_MasterWrite(BStr+6, Strlen-1-4, 0x08, &I2CMS);
        I2C_mWrite(BStr+6, Strlen-1-4, ARDUINO_SID);
        
        Print_CHLN();
        Print_String("SET Password OK$", 1);
    }

    /* Set AP  */
    else if((*(BStr+0) == 'C')&&
            (*(BStr+1) == 'H')&&
            (*(BStr+2) == 'K')&&
            (*(BStr+3) == 'A')&&
            (*(BStr+4) == 'P') )
    {
        *(BStr+0) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+1) = 0xA1;           /* = address */
        *(BStr+2) = 0x01;       /* = length  */
        *(BStr+3) = 0x01;       /* = data  */
//        I2C_MasterWrite(BStr, 4+1, 0x08, &I2CMS);
        I2C_mWrite(BStr, 4+1, ARDUINO_SID);
         
        Print_CHLN();
        Print_String("CHECK AP, need waiting feedback...$", 1);
                
        exINT_Mode = 0x01;
    }

    /* Set CNCT  */
    else if((*(BStr+0) == 'C')&&
            (*(BStr+1) == 'N')&&
            (*(BStr+2) == 'C')&&    /**/
            (*(BStr+3) == 'T') )
    {
        *(BStr+0) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+1) = 0xA1;           /* = address */
        *(BStr+2) = 0x01;       /* = length  */
        *(BStr+3) = 0x02;       /* = data  */
//        I2C_MasterWrite(BStr, 4+1, 0x08, &I2CMS);
        I2C_mWrite(BStr, 4+1, ARDUINO_SID);
 
        Print_CHLN();
        Print_String("SET CNCT, need waiting feedback...$", 1);
        
        exINT_Mode = 0x02;
    }

    /* Set FID  */
    else if((*(BStr+0) == 'F')&&
            (*(BStr+1) == 'I')&&   /**/
            (*(BStr+2) == 'D') )
    {
        *(BStr+4) = STR2HEX(BStr, 4);
        *(BStr+5) = STR2HEX(BStr, 6);               
        *(BStr+6) = STR2HEX(BStr, 8);

        *(BStr+1) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+2) = 0x3D;           /* = address */
        *(BStr+3) = 0x03;       /* = length  */
//        I2C_MasterWrite(BStr+1, Strlen, 0x08, &I2CMS);
        I2C_mWrite(BStr+1, Strlen, ARDUINO_SID);
 
        Print_CHLN();
        Print_String("SET FID OK$", 1);
    }

    /* Set Register  */
    else if((*(BStr+0) == 'R')&&
            (*(BStr+1) == 'E')&&
            (*(BStr+2) == 'G') )
    {
        *(BStr+0) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+1) = 0xA1;           /* = address */
        *(BStr+2) = 0x01;       /* = length  */
        *(BStr+3) = 0x04;       /* = data  */
//        I2C_MasterWrite(BStr, 4+1, 0x08, &I2CMS);
        I2C_mWrite(BStr, 4+1, ARDUINO_SID);
 
        Print_CHLN();
        Print_String("REGISTER, need waiting feedback...$", 1);
        
        exINT_Mode = 0x04;
    }

    /* Set request adjust online RTC  */
    else if((*(BStr+0) == 'A')&&
            (*(BStr+1) == 'D')&&
            (*(BStr+2) == 'J') )
    {
        *(BStr+0) = 0x01;           /* = 0 read, =1 write   */
        *(BStr+1) = 0xA1;           /* = address */
        *(BStr+2) = 0x01;       /* = length  */
        *(BStr+3) = 0x08;       /* = data  */
//        I2C_MasterWrite(BStr, 4+1, 0x08, &I2CMS);
        I2C_mWrite(BStr, 4+1, ARDUINO_SID);
 
        Print_CHLN();
        Print_String("Adjust, need waiting feedback...$", 1);
        
        exINT_Mode = 0x08;
    }

    

#if 1
    /* for Test: read ph */
    else if(*(BStr+0) == 'X')
    {
        MT_LoopTime = *(BStr+1) - '0';
        MT_SecTime = (*(BStr+2) - '0') * 1000;
        MT_SecTime += (*(BStr+3) - '0') * 100;
        MT_SecTime += (*(BStr+4) - '0') * 10;
        MT_SecTime += *(BStr+5) - '0';
        
        print_RTC();
        Print_CHLN();
        
        Print_String("Loop =  $", 0);
        Print_uint16Str(MT_LoopTime,0);
        Print_String(", Time =  $", 0);
        Print_uint16Str(MT_SecTime,1);
 
        Print_String("Test Read PH $", 1);
        Flag_Mesure_Test = (1-Flag_Mesure_Test);
        Loop_Mesure_Test = 0;
        OneCount_MT = 0;
    }
#endif


#if 1
    /* for Test: read 2 bytes  */
    else if(*(BStr+0) == 'Y')
    {
        Print_CHLN();
        Print_String("Test I2C Write Adruino $", 1);
        I2C_TEST_10();
    }
#endif


#if 1
    /* for Test: read 2 bytes  */
    else if(*(BStr+0) == 'Z')
    {
        Print_CHLN();
        Print_String("Test I2C EEPROM Write Read... $", 1);
        I2C_TEST_02();
    }
#endif

    
    
    
#if 0
    /* for Test: read 2 bytes  */
    else if(*(BStr+0) == 'Z')
    {
        TEST_READ_ADO_16B();
    }
#endif

#if 0
    /* for Test: read 2 bytes  */
    else if(*(BStr+0) == 'Z')
    {
        *(BufferRec+0) = 0x00;  /* = 0 read, =1 write   */
        *(BufferRec+1) = 0xC0;  /* = address */
        *(BufferRec+2) = 0x02;  /* = length  */
        I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);

        I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
        *(BufferRec + 2) = '$';
//            __delay_ms(10);

        Print_CHLN();
        Print_String("Read one =0x$", 0);
//        Print_String(BufferRec, 1);
        Print_HEX2Str(*BufferRec, 0);
        Print_String(", 0x$", 0);
        Print_HEX2Str(*(BufferRec+1), 1);
    }
#endif

    
}



void RUN_MESURE(uint8_t WhatStrip)
{
                   /*      ISE_M, PH, NH3, ORP, MgNa, CaK, TDS, DO, REFEL */
uint8_t setup_table[9*7]={ 1,     1,  0,   0,   0,    0,  0,   0,  1,   /*  0 PH    */
                           1,     0,  1,   0,   0,    0,  0,   0,  1,   /*  1 NH3   */
                           1,     0,  0,   1,   0,    0,  0,   0,  1,   /*  2 ORP   */
                           1,     0,  0,   0,   1,    0,  0,   0,  1,   /*  3 MgNa  */
                           1,     0,  0,   0,   0,    1,  0,   0,  1,   /*  4 CaK   */
                           0,     0,  0,   0,   0,    0,  1,   0,  0,   /*  5 TDS   */
                           0,     0,  0,   0,   0,    0,  0,   1,  0};  /*  6 DO    */
uint8_t tpWhatADC = 0;


                   /*      A2,  A1, A0,  */
uint8_t setup_3t8[3*5]={    0,   1,  0,  /*  0 PH     */
                            0,   0,  1,  /*  0 NH3    */
                            0,   0,  0,  /*  0 ORP    */
                            1,   0,  0,  /*  0 MgNa   */
                            1,   1,  0}; /*  0 VaK    */


uint16_t lpi = 0;
uint32_t AVG100 = 0;

/*

 * CN0  0   1   0   1 
 * CN1  0   0   1   1
 * Gain 0   5   10  15
*/

    OCPGAIN_CN0_SetLow();
    OCPGAIN_CN1_SetLow();


//    EN_AD8220_SetHigh();
#if VER_110_5CN

#else
    if(WhatStrip < 5)
    {
        ISE_M_SetHigh();
        REFEL_CN_SetHigh();
        
        if(setup_3t8[(WhatStrip*3) + 0] == 0) 
            PH_CN_SetLow();
        else
            PH_CN_SetHigh();

        if(setup_3t8[(WhatStrip*3) + 1] == 0) 
            MG_CN_SetLow();
        else
            MG_CN_SetHigh();

        if(setup_3t8[(WhatStrip*3) + 2] == 0) 
            CA_CN_SetLow();
        else
            CA_CN_SetHigh();   
        
        NH3_CN_SetLow();
        ORP_CN_SetLow();
    }
#endif
    

#if VER_110_5CN
#else
    if(WhatStrip >= 5)
#endif
    {
        if(setup_table[(WhatStrip*9) + 0] == 0) 
            ISE_M_SetLow();
        else
            ISE_M_SetHigh();

        if(setup_table[(WhatStrip*9) + 1] == 0) 
            PH_CN_SetLow();
        else
            PH_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 2] == 0) 
            NH3_CN_SetLow();
        else
            NH3_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 3] == 0) 
            ORP_CN_SetLow();
        else
            ORP_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 4] == 0) 
            MG_CN_SetLow();
        else
            MG_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 5] == 0) 
            CA_CN_SetLow();
        else
            CA_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 6] == 0) 
            TDS_CN_SetLow();
        else
            TDS_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 7] == 0) 
            DO_CN_SetLow();
        else
            DO_CN_SetHigh();

        if(setup_table[(WhatStrip*9) + 8] == 0) 
            REFEL_CN_SetLow();
        else
            REFEL_CN_SetHigh();
    }

    if(WhatStrip < 5)
    {
        tpWhatADC = MESURE_ISE;
//        DAC1_SetOutput(0x80);   /* 1.0 V  */
        DAC1_SetOutput(0x00);   /* 0V  */
    }
    else if(WhatStrip == 5)
    {
        tpWhatADC = MESURE_TDS;
        DAC1_SetOutput(0xC0);   /* 1.5 V  */
    }
    else if(WhatStrip == 6)
    {
        tpWhatADC = MESURE_DO;
        DAC1_SetOutput(0x1b);   /* 0.2 V  */    
    }
    if(RUN_PWM_FLAG == 1)
        return;
    
//    Print_CHLN();
//    Print_String("MESURE =$", 0);
                switch(WhatStrip)
                {
                    case 0:
                        Print_String(",$", 0);
                        Print_CHLN();
                        break;
                    case 1:
                        Print_String(",$", 0);
                        break;
                    case 2:
                        Print_String(",$", 0);
                        break;
                    case 3:
                        Print_String(",$", 0);
                        break;
                    case 4:
                        Print_String(",$", 0);
                        break;
                    case 5:
                        Print_String("TDS = $", 0);
                        break;
                    case 6:
                        Print_String("DO = $", 0);
                        break;
                }
   
    for(lpi =0; lpi<1000; lpi++)
    {
        ADC_Vol = ADC_GetConversion(tpWhatADC);
        AVG100 += (uint32_t)ADC_Vol/16;
    }
    
    AVG100 /= 1000;
    
    ADC_Vol = (uint16_t)AVG100;
    
//    ADC_Vol /= 16;

#if 0
    ADC_Vol = ADC_Vol - 180;
    ADC_Vol = ADC_Vol * 10;
    ADC_Vol = ADC_Vol / 15;
#endif
    
    if(WhatStrip == 0)
        REC_METER_VAL.Rec_PH = ADC_Vol;
    else if(WhatStrip == 1)
        REC_METER_VAL.Rec_NH3 = ADC_Vol;
    else if(WhatStrip == 2)
        REC_METER_VAL.Rec_ORP = ADC_Vol;
    else if(WhatStrip == 3)
        REC_METER_VAL.Rec_GHmg = ADC_Vol;
    else if(WhatStrip == 4)
        REC_METER_VAL.Rec_HGca = ADC_Vol;
    else if(WhatStrip == 5)
        REC_METER_VAL.Rec_TDS = ADC_Vol;
    else if(WhatStrip == 6)
        REC_METER_VAL.Rec_DO = ADC_Vol;

    

    
    Print_uint16Str(ADC_Vol,0);

//    Print_String("mv$", 0);

    //    EN_AD8220_SetLow();
}





/*----------------------------------------------------------------------------*/
void UPLOAD_MESURE_REC(void)
{
uint8_t LoopA = 0;
        
/*  7 YYMDHMS + (8 sensor * 2 B) */
uint8_t BufferString[26] = {
0x01,   /* = 0 read, =1 write   */
0x60,   /* = address */
0x17,   /* = length, 0x17 = 23 = 7+(2*8)  */
0x20,0x16,0x01,0x26,0x12,0x34,0x56, /* data: YYMDHMS */
0x01,0x11,  /* Temp */
0x02,0x22,  /* NH3 */
0x03,0x33,  /* PH */
0x04,0x44,  /* TDS */
0x05,0x55,  /* HGca */
0x06,0x66,  /* GHmg */
0x07,0x77,  /* DO */
0x08,0x88   /* ORP */   };



//uint8_t LoopA = 0;

    if(FirstTimeSetup == 0)
        return;


    /*  converter Time, */
    Convert_HMS(RTC_SecCount, &RTC_Clock);
    Convert_YMD(RTC_DayCount, &RTC_Clock);

    BufferString[3] = 0x20; /*  2016 */
    BufferString[4] = RTC_Clock.RTC_Year;
    BufferString[5] = RTC_Clock.RTC_Month;
    BufferString[6] = RTC_Clock.RTC_Day;
    BufferString[7] = RTC_Clock.RTC_Hour;
    BufferString[8] = RTC_Clock.RTC_Min;
    BufferString[9] = RTC_Clock.RTC_Sec;

    
    DS18B20_GetTemp(BufferGetTemp);
    
    BufferString[10] = *(BufferGetTemp+0);
    BufferString[11] = *(BufferGetTemp+1);
    
#if 0
    for(LoopA = 0; LoopA < 8; LoopA++)
    {
        BufferString[10+LoopA*2] = REC_METER_VAL.Rec_Temp
    
    }
#endif
    
    BufferString[12] = REC_METER_VAL.Rec_NH3 / 256;
    BufferString[13] = REC_METER_VAL.Rec_NH3 % 256;
//    BufferString[12] = 0x00;
//    BufferString[13] = 0x20;
    
    BufferString[14] = REC_METER_VAL.Rec_PH / 256;
    BufferString[15] = REC_METER_VAL.Rec_PH % 256;
    
    BufferString[16] = REC_METER_VAL.Rec_TDS / 256;
    BufferString[17] = REC_METER_VAL.Rec_TDS % 256;

    BufferString[18] = REC_METER_VAL.Rec_HGca / 256;
    BufferString[19] = REC_METER_VAL.Rec_HGca % 256;

    BufferString[20] = REC_METER_VAL.Rec_GHmg / 256;
    BufferString[21] = REC_METER_VAL.Rec_GHmg % 256;

    BufferString[22] = REC_METER_VAL.Rec_DO / 256;
    BufferString[23] = REC_METER_VAL.Rec_DO % 256;

    BufferString[24] = REC_METER_VAL.Rec_ORP / 256;
    BufferString[25] = REC_METER_VAL.Rec_ORP % 256;

    

//    I2C_MasterWrite(BufferString, 26+1, 0x08, &I2CMS);
    I2C_mWrite(BufferString, 26+1, ARDUINO_SID);

    
                MT_LoopTime = 1;
                MT_SecTime = 1;

                Flag_Mesure_Test = 1;
                Loop_Mesure_Test = 0;
                OneCount_MT = 0;

}




/*----------------------------------------------------------------------------*/
void COVERT_ADC2HLB(uint8_t *Buffer, uint16_t ADC_VOL)
{
uint8_t HiByte = 0;
uint8_t LowByte = 0;

    HiByte = ADC_VOL / 256;
    LowByte = ADC_VOL % 256;
    *(Buffer+0) = HiByte;
    *(Buffer+1) = LowByte;
}

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/*  ASCII text change   */
void Print_CHLN(void)
{
    EUSART_Write(0x0d);
    EUSART_Write(0x0a);  
}

/*  ASCII text break line   */
void Print_BreakLine(void)
{
uint16_t loopA = 0;

    for(loopA = 0; loopA < 60; loopA++)
        EUSART_Write('-');

    Print_CHLN();
}

/* ASCII text print string
 * need spec string length = [chln]
*/
void Print_String(uint8_t const *BStr, uint8_t chln)
{
uint8_t Data;
uint16_t loopA = 0;

    do
    {
        Data = *(BStr + loopA++);
        if(Data != '$')
            EUSART_Write(Data);
  
    }while(Data != '$');

    if(chln == 1)
        Print_CHLN();
}

/* ASCII text print OCT Number(5 digital)  */
void Print_uint16Str(uint16_t InputVol, uint8_t Chgln)
{
uint16_t loopA = 0;
uint8_t wOneByte = 0x41;
uint16_t CalVol = InputVol;
//uint16_t DIVA = 1000000;
uint16_t DIVA = 10000;

uint8_t Chk19 = 0;


    for(loopA = 0; loopA < 4; loopA++)
    {
        wOneByte = CalVol / DIVA;
        CalVol %= DIVA;
        if((Chk19 == 0)&&(wOneByte == 0))
        {
            EUSART_Write(' ');
//            EUSART_Write(0x30);
        }
        else
        {
            Chk19 = 1;
            EUSART_Write(wOneByte+0x30);
        }
        
        DIVA /=10;
    }

    wOneByte = CalVol;
    EUSART_Write(wOneByte+0x30);
    
    if(Chgln == 1)
        Print_CHLN();
}

/* ASCII text print OCT Number(2 digital)  */
void Print_OCT2Str(uint8_t InputVol)
{
uint8_t wOneByte = 0x41;
uint8_t CalVol = InputVol;

    wOneByte = CalVol / 10;
    CalVol %= 10;
    EUSART_Write(wOneByte+0x30);
    EUSART_Write(CalVol+0x30);
}


/* ASCII text print HEX Number  */
void Print_HEX2Str(uint8_t InputVol, uint8_t Chgln)
{
uint8_t wOneByte = 0x41;
uint16_t HexCal = InputVol/16;

    if(HexCal >= 10)
        wOneByte = 'A'+ HexCal-10;
    else
        wOneByte = '0'+ HexCal;  
    EUSART_Write(wOneByte);
    
    HexCal = InputVol % 16;
    if(HexCal >= 10)
        wOneByte = 'A'+ HexCal-10;
    else
        wOneByte = '0'+ HexCal;  
    EUSART_Write(wOneByte);
    
    if(Chgln == 1)
        Print_CHLN();
}







/*----------------------------------------------------------------------------*/
uint8_t STR2HEX(uint8_t *BStr, uint8_t NumPoint)
{
    return (ASCII_OCT2HEX(*(BStr + NumPoint)) * 16)+ ASCII_OCT2HEX(*(BStr + NumPoint + 1));
}

uint8_t ASCII_OCT2HEX(uint8_t ASCII_OCT)
{
    if((ASCII_OCT >= '0')&&(ASCII_OCT <= '9'))
       ASCII_OCT = ASCII_OCT - '0';
    else if((ASCII_OCT >= 'a')&&(ASCII_OCT <= 'f'))
       ASCII_OCT = ASCII_OCT - 'a' + 10;
    else if((ASCII_OCT >= 'A')&&(ASCII_OCT <= 'F'))
       ASCII_OCT = ASCII_OCT - 'A' + 10;
    
    return ASCII_OCT;
}

/*----------------------------------------------------------------------------*/
#if 1
uint8_t DS18B20_Reset(void)
{
uint8_t vByte = 0;
    
    
   TEMP_DQ_SetLow();
   Delay480us();    /* 360  */
   
   TEMP_DQ_SetDigitalInput();

//   Delay100us();     /*  40 */

   vByte = TEMP_DQ_GetValue();

   
   TEMP_DQ_SetDigitalOutput();

   TEMP_DQ_SetHigh();
   Delay480us();        /* 100 */
   

   return vByte;
}
#endif



#if 0
uint8_t DS18B20_Reset(void)
{
uint8_t vByte = 0;
    
    
   IO_DQ_SetLow();
   Delay480us();    /* 360  */

   IO_DQ_SetHigh();
   Delay5us();     /* 10   */

   
   IO_DQ_SetDigitalInput();

   Delay5us();     /*  40 */

   vByte = IO_DQ_GetValue();
//   IO_LED_GREEN_Toggle();
   
   IO_DQ_SetDigitalOutput();

   IO_DQ_SetHigh();
   Delay100us();        /* 100 */
   

   return vByte;
}
#endif

void DS18B20_Write(uint8_t vByte)
{
uint8_t i;

//    IO_LED_GREEN_Toggle();
    for(i=0;i<8;i++)
    {
       TEMP_DQ_SetLow();
       Delay5us();    /* 10   */
       
       if( (vByte & 0x01) == 1)
       {
           TEMP_DQ_SetLow();
           Delay5us();
           TEMP_DQ_SetHigh();
           Delay100us();
       }
       else
       {
           TEMP_DQ_SetLow();
           Delay100us();
           TEMP_DQ_SetHigh();
           Delay5us();
       }
       vByte >>= 1;
    }

    Delay5us();     /* 10   */  
}

#if 0
void DS18B20_Write(uint8_t vByte)
{
uint8_t i;

//    IO_LED_GREEN_Toggle();
    for(i=0;i<8;i++)
    {
       IO_DQ_SetLow();
       Delay5us();    /* 10   */
       
       if( (vByte & 0x01) == 1)
           IO_DQ_SetHigh();
       else
           IO_DQ_SetLow();
       
       Delay100us();    /* 100   */
//       Delay5us();     /* 10   */
       IO_DQ_SetHigh();
       vByte >>= 1;
    }

    Delay5us();     /* 10   */  
}

#endif


uint8_t DS18B20_Read(void)
{
uint8_t i;
uint8_t vByte = 0;


    for(i=0;i<8;i++)
    {
       vByte >>= 1;
       TEMP_DQ_SetLow();
       Delay5us();    /* 10   */
       TEMP_DQ_SetHigh();
       
       
       TEMP_DQ_SetDigitalInput();
       Delay5us();    /* 10   */
       
       if( TEMP_DQ_GetValue() == 1)
           vByte |= 0x80;

       Delay100us();    /* 10   */
       
       TEMP_DQ_SetDigitalOutput();
    }
    return vByte;
}


#if 0
uint8_t DS18B20_Read(void)
{
uint8_t i;
uint8_t vByte = 0;


    for(i=0;i<8;i++)
    {
       vByte >>= 1;
       IO_DQ_SetLow();
       Delay5us();    /* 10   */
       IO_DQ_SetHigh();
       
       
       IO_DQ_SetDigitalInput();
       Delay5us();    /* 10   */
       
       if( IO_DQ_GetValue() == 1)
           vByte |= 0x80;

       Delay5us();    /* 10   */
       
       IO_DQ_SetDigitalOutput();
    }
    return vByte;
}
#endif


void DS18B20_GetTemp(uint8_t *rTwoByte)
{
uint8_t vByteHi = 0;
uint8_t vByteLow = 0;
uint8_t ack = 1;

uint16_t xTemp = 0;
        
   DS18B20_Reset();
//   Print_uint16Str(ack);
   
//   return ack;

   DS18B20_Write(0xcc);
   DS18B20_Write(0x44);
//   IO_LED_GREEN_Toggle();
   Delay480us();

//   IO_LED_GREEN_Toggle();
   DS18B20_Reset();
   DS18B20_Write(0xcc);
   DS18B20_Write(0xbe);
//   IO_LED_GREEN_Toggle();
   
   vByteLow = DS18B20_Read();
   vByteHi = DS18B20_Read();

   /*  if read Error, try a again */
   if(vByteHi && 0xF0)
   {
        Delay480us();
        DS18B20_Reset();
        DS18B20_Write(0xcc);
        DS18B20_Write(0xbe);
        vByteLow = DS18B20_Read();
        vByteHi = DS18B20_Read();
   }
   
   if(vByteHi && 0xF0)
   {
       ErrorFlag &= EF_TEMP;
   }
//   vByteLow >>= 4;
//   vByteHi <<= 4;

   xTemp = vByteHi;
   xTemp *= 256;
   xTemp += vByteLow;
   xTemp /= 16;
//   vByteLow %= 16;
//   ack = vByteHi + vByteLow;
   
   *(rTwoByte + 0) = vByteHi;
   *(rTwoByte + 1) = vByteLow;

   REC_METER_VAL.Rec_Temp = xTemp;
   
   Print_String("Mesure Temp DATA = $", 0);
   Print_String("0x$", 0);
   Print_HEX2Str(vByteHi, 0);
   Print_String(", 0x$", 0);
   Print_HEX2Str(vByteLow, 1);
   Print_uint16Str(xTemp,1);

//   Print_String("Check TempHi:$", 0);
//   Print_HEX2Str(vByteHi);
}


/*  10 = 1, 480 = 133, 28 = 100    */
/*----------------------------------------------------------------------------*/
void Delay5us(void)
{

}

void Delay480us(void)
{
uint8_t i;
uint8_t s = 0;

   for(i=0;i<80;i++)   /*480*/
    {
       s++;
    }
//    return s;
}

void Delay100us(void)
{
uint8_t i;
uint8_t s = 0;

   for(i=0;i<12;i++)/*17=100us*/
    {
       s++;
    }

//    return s;
}

void Delay_us(uint16_t uDelay)
{
uint16_t i;
uint8_t s = 0;

    for(i=0;i<uDelay;i++)   /* */
    {
       s++;
    }

//    return s;
}
/*----------------------------------------------------------------------------*/
void Convert_HMS(uint32_t iCount, RTC_YMDHMS *rClock)
{
    rClock->RTC_Sec = Convert_2HB(iCount % 60);
    iCount /= 60;
    
    rClock->RTC_Min = Convert_2HB(iCount % 60);
    iCount /= 60;
    
    rClock->RTC_Hour = Convert_2HB(iCount % 24);
}


/*----------------------------------------------------------------------------*/
void Print_HMS(RTC_YMDHMS rClock)
{

    EUSART_Write(0x30 + (rClock.RTC_Hour / 16));
    EUSART_Write(0x30 + (rClock.RTC_Hour % 16));
    EUSART_Write(':');
    EUSART_Write(0x30 + (rClock.RTC_Min / 16));
    EUSART_Write(0x30 + (rClock.RTC_Min % 16));
    EUSART_Write(':');
    EUSART_Write(0x30 + (rClock.RTC_Sec / 16));
    EUSART_Write(0x30 + (rClock.RTC_Sec % 16));
    Print_CHLN();
}


/*----------------------------------------------------------------------------*/
void Convert_YMD(uint16_t iCount, RTC_YMDHMS *rClock)
{
uint16_t MonthTable[12]={
31, /*  1 */
28, /*  2 */
31, /*  3 */
30, /*  4 */
31, /*  5 */
30, /*  6 */
31, /*  7 */
31, /*  8 */
30, /*  9 */
31, /*  10 */
30, /*  11 */
31  /*  12 */
};

uint8_t i =0;
uint8_t cDay = 0;
uint8_t cMonth = 0;
uint8_t cYear = 0;


    while(iCount >= MonthTable[i])
    {
        iCount -= MonthTable[i];
        i++;
        
        if(i >= 12)
        {
            cYear++;
            i = 0;
        }
        cMonth++;
    }
    
    cDay = iCount;

    rClock->RTC_Day = 

    rClock->RTC_Day = Convert_2HB(cDay+1);
    
    rClock->RTC_Month = Convert_2HB(cMonth+1);
    
    rClock->RTC_Year = Convert_2HB(cYear + 16 );

#if 0
    rClock->RTC_Day = Convert_2HB((iCount % 30)+1);
    iCount /= 30;
    
    rClock->RTC_Month = Convert_2HB((iCount % 12)+1);
    iCount /= 12;
    
    rClock->RTC_Year = Convert_2HB(iCount + 16 );
#endif
}


void Print_YMD(RTC_YMDHMS rClock)
{
    EUSART_Write('2');
    EUSART_Write('0');
    EUSART_Write(0x30 + (rClock.RTC_Year / 16));
    EUSART_Write(0x30 + (rClock.RTC_Year % 16));
    EUSART_Write('-');
    EUSART_Write(0x30 + (rClock.RTC_Month / 16));
    EUSART_Write(0x30 + (rClock.RTC_Month % 16));
//    Print_OCT2Str(rClock.RTC_Month);
    EUSART_Write('-');
    EUSART_Write(0x30 + (rClock.RTC_Day / 16));
    EUSART_Write(0x30 + (rClock.RTC_Day % 16));
//    Print_OCT2Str(rClock.RTC_Day);
    EUSART_Write(' ');
//    Print_CHLN();
}


/*----------------------------------------------------------------------------*/
uint8_t Convert_2HB(uint8_t iCount)
{
uint8_t hNib = 0;
uint8_t lNib = 0;

    hNib = iCount / 10;
    lNib = iCount % 10;
    
    return ((hNib*16)+lNib);
}



/*==============================================================================
 * Self-test function
==============================================================================*/

/*------------------------------------------------------------------------------
 * Self-test function
 * for PIC All test
 * return   =0  OK
 *          =1  NG
------------------------------------------------------------------------------*/
void TEST_PIC_ALL(void)
{
    Print_CHLN();
    
    Print_BreakLine();
#if VER_110_5CN
    Print_String("Akubic System Version: 1.10$", 1);
#else
    Print_String("Akubic System Version: 1.00$", 1);
#endif
    Print_String("Auto run self test$", 1);

    print_RTC();
    DS18B20_GetTemp(BufferGetTemp);
    check_ADO_I2C();
    
    Print_String("Check Finish$", 1);
    Print_BreakLine();
}




/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/
void print_RTC(void)
{
    Convert_YMD(RTC_DayCount, &RTC_Clock);
    Convert_HMS(RTC_SecCount, &RTC_Clock);

    Print_CHLN();
    Print_String("Check RTC = $", 0);
    Print_YMD(RTC_Clock);
    Print_HMS(RTC_Clock);
}










/*==============================================================================
 * Self-test function
==============================================================================*/

#if 0
void TEST_READ_ADO_16B(void)
{
uint8_t i;

/*  read RTC */

    /*  read 0xA0, 0xA1 2 bytes data */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0x50;    /* = address */
    *(BufferRec+2) = 7;    /* = length  */
//    I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//    I2C_MasterRead(BufferRec, 7, 0x08, &I2CMS);     /* for test  */
//    exINT_Error = *BufferRec;

    /*  print 0xA0, 0xA1 2 bytes data */
    for(i=0; i<7; i++)
    {
//        Print_String("RESULT NG, Error = 0x$", 0); 
        Print_HEX2Str(*(BufferRec + i), 1);
    }
    
    
    Print_CHLN();
       
/*  read RTC */
    /*  read 0xA0, 0xA1 2 bytes data */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0x4A;    /* = address */
    *(BufferRec+2) = 2;    /* = length  */
//    I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//    I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
//    exINT_Error = *BufferRec;

    /*  print 0xA0, 0xA1 2 bytes data */
    for(i=0; i<2; i++)
    {
//        Print_String("RESULT NG, Error = 0x$", 0); 
        Print_HEX2Str(*(BufferRec + i), 1);
    }

    NUL_SecCount_offset = *(BufferRec) + ( *(BufferRec) * 256);
    NUL_SecCount = RTC_SecCount + NUL_SecCount_offset;
    
}
#endif


/*
 from ADO 0x50 get 7 bytes for RTC data
 sync to PIC RTC data
 ADO = 20,Year,Month,Day,Hour,Min,Sec
 PIC = RTC_DayCount
       RTC_SecCount
 */
void PIC_SYNC_ADO_RTC(void)
{
uint8_t i;
uint16_t    cYear = 0;
uint16_t    cMonth = 0;
uint16_t    cDay = 0;
uint32_t    cHour = 0;
uint16_t    cMin = 0;
uint16_t    cSec =0;




/*  read ADO RTC */

    /*  read 0x50 7 bytes data */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0x50;    /* = address */
    *(BufferRec+2) = 7;    /* = length  */
//    I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//    I2C_MasterRead(BufferRec, 7, 0x08, &I2CMS);     /* for test  */
    I2C_mWrite(BufferRec, 3+1, ARDUINO_SID);
    I2C_mREAD(BufferRec, 7, ARDUINO_SID);
    
    cYear = Covert_BDC_2_OCT(*(BufferRec + 1));
    cYear -= 16;
    cMonth = Covert_BDC_2_OCT(*(BufferRec + 2));
    cMonth -= 1;
    cDay = Covert_BDC_2_OCT(*(BufferRec + 3));
    cDay -= 1;
    
    cYear *= 365; 
    cMonth = Covert_Month_2_Day(cMonth);
    
    cHour = Covert_BDC_2_OCT(*(BufferRec + 4));
    cHour *= 3600;
    cMin = Covert_BDC_2_OCT(*(BufferRec + 5));
    cMin *= 60;
    cSec = Covert_BDC_2_OCT(*(BufferRec + 6));

    
    RTC_DayCount = cYear + cMonth + cDay;    
    RTC_SecCount = cHour + cMin + cSec;
    
    NUL_SecCount = RTC_SecCount + NUL_SecCount_offset;

    /*  print 0x50, 7 bytes data */
    for(i=0; i<7; i++)
    {
        Print_HEX2Str(*(BufferRec + i), 1);
    }
    
    
    Print_CHLN();
}



/*
 from ADO 0x4A get 2 bytes for next time upload sample rate(min)
 sync to PIC next time upload
 ADO = 2 bytes
 PIC = NUL_SecCount_offset  = *60
 */
void PIC_SYNC_ADO_ULSR(void)
{
uint8_t i;

/*  read RTC */
    /*  read 0xA0, 0xA1 2 bytes data */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0x4A;    /* = address */
    *(BufferRec+2) = 2;    /* = length  */
//    I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//    I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
        I2C_mWrite(BufferRec, 3+1, ARDUINO_SID);
        I2C_mREAD(BufferRec, 2, ARDUINO_SID);

    /*  print 0xA0, 0xA1 2 bytes data */
    for(i=0; i<2; i++)
    {
        Print_HEX2Str(*(BufferRec + i), 1);
    }

//    NUL_SecCount_offset = (*(BufferRec) + ( *(BufferRec +1) * 256)) * 60;
    NUL_SecCount_offset = 10;
    NUL_SecCount = RTC_SecCount + NUL_SecCount_offset;
    
    Print_uint16Str(NUL_SecCount_offset,1);
    Print_uint16Str(NUL_SecCount,1);
    Print_uint16Str(RTC_SecCount,1);

    Print_CHLN();
}


uint8_t Covert_BDC_2_OCT(uint8_t iBDC)
{
    return(iBDC/16)*10 + (iBDC%16);    
}



uint16_t Covert_Month_2_Day(uint16_t iMonth)
{
uint16_t MonthTable[12]={
31, /*  1 */
28, /*  2 */
31, /*  3 */
30, /*  4 */
31, /*  5 */
30, /*  6 */
31, /*  7 */
31, /*  8 */
30, /*  9 */
31, /*  10 */
30, /*  11 */
31  /*  12 */
};

uint16_t CalResult =0;
        
uint8_t loopi =0;

    if(iMonth != 0)
    {
        for(loopi=0; loopi< iMonth; loopi++)
            CalResult += MonthTable[loopi];
    }
    return CalResult;    
}










//=============================================================================

//=============================================================================


/*****************************************************************************
 * Author:      enos
 * Function:    I2C_Dealy_1
 * Description: wait for some time to get proper I2c timing
 *****************************************************************************/
void I2C_Dealy_1(void)
{
    Delay5us();
    Delay5us();
}

/*****************************************************************************
 * Author:      enos
 * Function:    I2C_Dealy_2
 * Description: wait for some time to get proper I2c timing
 *****************************************************************************/
void I2C_Dealy_2(void)
{
    Delay5us();
}

/*****************************************************************************
 * Author:      enos
 * Function:    I2C_START_BIT
 * Description: I2C start signal.
 * <comment>
 *  SCL ________
 *              \_________
 *  SDA _____
 *           \____________
 *
 * Return value: None
 *****************************************************************************/
void I2C_START_BIT(void)
{
    
    // for second start signal on I2C_READ_8BIT
    PIC_SDA_SetHigh();
    PIC_SCL_SetHigh();
    I2C_Dealy_1();			/* Start condition hold time = 6 	*/

    // send start signal
    PIC_SDA_SetLow();
    I2C_Dealy_2();			/* Start condition setup time = 7 	*/
    PIC_SCL_SetLow();
}

/*****************************************************************************
 * Author:      enos
 * Function:    I2C_STOP_BIT
 * Description: I2C stop signal.
 * <comment>
 *              ____________
 *  SCL _______/
 *                 _________
 *  SDA __________/
 *
 * assume I2C_SCL = LOW, I2C_SDA = LOW
 *****************************************************************************/
void I2C_STOP_BIT(void)
{
//    I2C_Dealy_2();
//    IO_RC3_IC2_SCL_SetHigh();
    I2C_Dealy_2();
    PIC_SDA_SetLow();
    I2C_Dealy_2();
    PIC_SCL_SetHigh();
    I2C_Dealy_2();			/* Stop condition setup time = 10 	*/
    PIC_SDA_SetHigh();
}

/*****************************************************************************
 * Author:      enos
 * Function:    I2C_WRITE_8BIT
 * Description: I2C write command
 * I2C_SCL = LOW    data change
 * I2C_SCL = HIGH   data stable
 * return:  =0  ok, get ack
 *          =1
 *****************************************************************************/
uint8_t I2C_WRITE_8BIT(unsigned char value)
{
uint8_t i=9;
uint8_t ack = 1;

    while(--i)
    {
        // upload data
        I2C_Dealy_2();
//        I2C_SDA = (value & 0x80) ? HIGH : LOW;
        if(value & 0x80)
          PIC_SDA_SetHigh();
	else
          PIC_SDA_SetLow();


        I2C_Dealy_2();
        
        // send data
        PIC_SCL_SetHigh();
        I2C_Dealy_1();
        
        value <<= 1;
        PIC_SCL_SetLow();
    }

    // get acknowledgement
    I2C_Dealy_2();
    PIC_SDA_SetHigh();
    PIC_SDA_SetDigitalInput();
    
    I2C_Dealy_2();
    PIC_SCL_SetHigh();
    
#if 0   
//    Delay100us();
    i = 0;
    do
    {
      i++;
      I2C_Dealy_1();
      ack = IO_RC4_I2C_SDA_GetValue();
    }while((ack == 1)&&(i < 200));
#endif
    
    I2C_Dealy_1();
    ack = PIC_SDA_GetValue();
    
    PIC_SDA_SetDigitalOutput();
    I2C_Dealy_2();
    PIC_SCL_SetLow();

    return ack;
}




/*****************************************************************************
 * Author:      enos
 * Function:    I2C_READ_8BIT
 * Description: I2C read command
 * I2C_SCL = LOW    data change
 * I2C_SCL = HIGH   data stable
 *****************************************************************************/
uint8_t I2C_READ_8BIT(uint8_t acknowledge)
{
uint8_t value=0;
uint8_t i=8;    //9
uint8_t rSCL=0;

    PIC_SDA_SetDigitalInput();

#if 1
        PIC_SCL_SetDigitalInput();
        value <<= 1;
        do
        {
            rSCL = PIC_SCL_GetValue();
        }while(rSCL == 0);
        value |= PIC_SDA_GetValue();
        PIC_SCL_SetDigitalOutput();
        
        I2C_Dealy_2();
        PIC_SCL_SetLow();
#endif        
        
    // read data
    while(--i)
    {
        // download data
        value <<= 1;
        I2C_Dealy_1();
        // get data
        PIC_SCL_SetHigh();
        I2C_Dealy_2();
        value |= PIC_SDA_GetValue();
        I2C_Dealy_2();
        PIC_SCL_SetLow();
    }

    PIC_SDA_SetDigitalOutput();
    // send acknowledge
    I2C_Dealy_2();
    I2C_Dealy_2();
    I2C_Dealy_2();
    
//    I2C_SDA = acknowledge;
    if(acknowledge)
      PIC_SDA_SetHigh();
    else
      PIC_SDA_SetLow();
      
    I2C_Dealy_2();
    PIC_SCL_SetHigh();
    I2C_Dealy_1();
    PIC_SCL_SetLow();

    // return data
    return value;
}

/*****************************************************************************
 * Author:      eric
 * Function:    I2C_BYTE_WRITE
 * Description: write one byte
 slave_addr = 1010 + 000 + 0 = 0xC0
 reg_addr   = Address
 
 *****************************************************************************/
uint8_t I2C_BYTE_WRITE(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l,uint8_t value)
{

#if 1
uint8_t i=10;
uint8_t Check_Error = 0;

    // Disable All Interrupt

//    while (--i)
    do
    {
        I2C_START_BIT();                           // start I2C

        if(Check_Error = I2C_WRITE_8BIT(slave_addr&0xfe) == 0)
            if(Check_Error = I2C_WRITE_8BIT(reg_addr_h) == 0)
                if(Check_Error = I2C_WRITE_8BIT(reg_addr_l) == 0)
                    Check_Error = I2C_WRITE_8BIT(value);                  

        I2C_STOP_BIT();                            // stop I2C
        i--;
    }while((i!=0)&&(Check_Error == 1) );
#endif
    // Enable All Interrupt

#if 1
//    Print_String("i =0x$", 0);
    Print_HEX2Str(i, 1);
#endif
    
#if 0
    Delay_us(400);
#endif
    
    
    return 0;
}



/*****************************************************************************
 * Author:      eric
 * Function:    I2C_BYTE_WRITE
 * Description: write one byte
 slave_addr = 1010 + 000 + 0 = 0xC0
 reg_addr   = Address
 
 *****************************************************************************/
uint8_t I2C_PAGE_WRITE(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l,uint8_t Size, uint8_t *value)
{

#if 1
uint8_t i=10;
uint8_t Check_Error = 0;
uint8_t j=0;
    // Disable All Interrupt

//    while (--i)
    do
    {
        I2C_START_BIT();                           // start I2C

        if(Check_Error = I2C_WRITE_8BIT(slave_addr&0xfe) == 0)
            if(Check_Error = I2C_WRITE_8BIT(reg_addr_h) == 0)
                if(Check_Error = I2C_WRITE_8BIT(reg_addr_l) == 0)
                    do
                    {
                        Check_Error = I2C_WRITE_8BIT(*(value+j));
                        j++;
                    }while((Check_Error == 0)&&(j<Size));
                    
        I2C_STOP_BIT();                            // stop I2C
        i--;
    }while((i!=0)&&(Check_Error == 1) );
#endif
    // Enable All Interrupt

#if 1
//    Print_String("i =0x$", 0);
    Print_HEX2Str(i, 1);
#endif
    
#if 0
    Delay_us(400);
#endif
    
    
    return 0;
}



/*****************************************************************************
 * Author:      eric
 * Function:    I2C_RANDOM_READ
 * Description: read one byte
 *****************************************************************************/
uint8_t I2C_RANDOM_READ(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l)
{
uint8_t i=10;
uint8_t value=0;

    // Disable All Interrupt
    while (--i)
    {
        // send register address
        I2C_START_BIT();                                // start I2C
        if(I2C_WRITE_8BIT(slave_addr&0xfe)) continue;    // slave address
        if(I2C_WRITE_8BIT(reg_addr_h)) continue;           // register address
        if(I2C_WRITE_8BIT(reg_addr_l)) continue;           // register address

        // read data
        I2C_START_BIT();                                // restart I2C
        if(I2C_WRITE_8BIT(slave_addr | 1)) continue;     // slave address
        value = I2C_READ_8BIT(1);                        // read data
        I2C_STOP_BIT();                                 // stop I2C
        break;
    }
    // Enable All Interrupt
    Print_HEX2Str(value, 1);

    return value;
}


/*****************************************************************************
 * Author:      eric
 * Function:    I2C_RANDOM_READ
 * Description: read one byte
 *****************************************************************************/
void I2C_Sequential_READ(uint8_t slave_addr, uint8_t reg_addr_h, uint8_t reg_addr_l, uint8_t Size, uint8_t *value)
{
uint8_t i=10;
uint8_t j=0;
uint8_t ack=1;

    // Disable All Interrupt
    while (--i)
    {
        // send register address
        I2C_START_BIT();                                // start I2C
        if(I2C_WRITE_8BIT(slave_addr&0xfe)) continue;    // slave address
        if(I2C_WRITE_8BIT(reg_addr_h)) continue;           // register address
        if(I2C_WRITE_8BIT(reg_addr_l)) continue;           // register address

        // read data
        I2C_START_BIT();                                // restart I2C
        if(I2C_WRITE_8BIT(slave_addr | 1)) continue;     // slave address
        do
        {
            if(j+1 == Size)
                ack = 1;
            else
                ack = 0;
            
            *(value+j) = I2C_READ_8BIT(ack);
            j++;        // read data
//            Print_HEX2Str(*(value+j), 1);
        }while(j < Size);
        
        I2C_STOP_BIT();                                 // stop I2C
        break;
    }
    // Enable All Interrupt
    Print_HEX2Str(i, 1);

}


//            I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
//            I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
/*****************************************************************************
 * Author:      eric
 * Function:    I2C_BYTE_WRITE
 * Description: write one byte
 slave_addr = 1010 + 000 + 0 = 0xC0
 reg_addr   = Address
 return:    =0
 *****************************************************************************/
uint8_t I2C_mWrite(uint8_t *value, uint8_t Size, uint8_t slave_addr)
{

#if 1
uint8_t i=10;
uint8_t Check_Error = 0;
uint8_t j=0;
    // Disable All Interrupt

//    while (--i)
    do
    {
        I2C_START_BIT();                           // start I2C

        if(Check_Error = I2C_WRITE_8BIT(slave_addr&0xfe) == 0)
            do
            {
                Check_Error = I2C_WRITE_8BIT(*(value+j));
                j++;
            }while((Check_Error == 0)&&(j<Size));
                    
        I2C_STOP_BIT();                            // stop I2C
        i--;
    }while((i!=0)&&(Check_Error == 1) );
#endif
    // Enable All Interrupt

#if 0   /*  need delay over 3.3 ms */
    Print_String("I2C_mWrite loop =0x$", 0);
    Print_HEX2Str(i, 1);
#endif
    
#if 0
    Delay_us(400);
#endif
    
    
    return 0;
}


/*****************************************************************************
 * Author:      eric
 * Function:    I2C_RANDOM_READ
 * Description: read one byte
 *****************************************************************************/
void I2C_mREAD(uint8_t *value, uint8_t Size, uint8_t slave_addr)
{
uint8_t i=10;
uint8_t j=0;
uint8_t ack=1;
uint8_t rSCL=0;



    // Disable All Interrupt
    while (--i)
    {
        // send register address
//        I2C_START_BIT();                                // start I2C
//        if(I2C_WRITE_8BIT(slave_addr&0xfe)) continue;    // slave address

        // read data
        I2C_START_BIT();                                // restart I2C
        if(I2C_WRITE_8BIT(slave_addr | 1)) continue;     // slave address

#if 0
        IO_RC3_IC2_SCL_SetDigitalInput();
        do
        {
            rSCL = IO_RC3_IC2_SCL_GetValue();
        }while(rSCL == 0);
        IO_RC3_IC2_SCL_SetDigitalOutput();
#endif

        do
        {
            if(j+1 == Size)
                ack = 1;
            else
                ack = 0;
            
            *(value+j) = I2C_READ_8BIT(ack);
            j++;        // read data
//            Print_HEX2Str(*(value+j), 1);
        }while(j < Size);
        
        I2C_STOP_BIT();                                 // stop I2C
        break;
    }
    // Enable All Interrupt
//    Print_String("I2C_mREAD loop =0x$", 0);
//    Print_HEX2Str(i, 1);

}



/*****************************************************************************
 * Author:      Eric
 * Function:    TEST_01
 * Description: Test write 0x10 byte, and read again, check data
 *              for one byte to one byte
 *****************************************************************************/
void I2C_TEST_01(void)
{
uint8_t i = 0;
uint8_t SID = EPR64_SID;
uint8_t i2cAddr_h = EPR64_MAX_SIZE>>8; 
uint8_t i2cAddr_l = 0; 
uint8_t i2cData = 0;
uint8_t Check_Error = 0;


    /*  first write 0x10 bytes */
    for(i=0; i<0x10; i++)
    {
      i2cData = i;
      i2cAddr_l = i;
      Check_Error = I2C_BYTE_WRITE(SID, i2cAddr_h, i2cAddr_l, i2cData);
//      Delay480us();
      
      /* if error, display address & data */
      if(Check_Error != 0)
      {
        Print_String("Error Address =0x$", 0);
        Print_HEX2Str(Check_Error, 1);
        Print_HEX2Str(i2cAddr_h, 0);
        Print_HEX2Str(i2cAddr_l, 1);
      }
    }   

    /* after read 0x10 bytes */
    Print_String("Read Address =0x$", 0);
    Print_HEX2Str(i2cAddr_h, 0);
    Print_HEX2Str(0, 1);
    
    for(i=0; i<0x10; i++)
    {
      i2cAddr_l = i;
      i2cData = I2C_RANDOM_READ(SID, i2cAddr_h, i2cAddr_l);
//      Print_HEX2Str(i2cData, 1);
    }
}

/*****************************************************************************
 * Author:      Eric
 * Function:    TEST_01
 * Description: Test write 0x10 byte, and read again, check data
 *              for Sequential write and read
 *****************************************************************************/
void I2C_TEST_02(void)
{
uint8_t i = 0;
uint8_t SID = EPR64_SID;
//uint8_t i2cAddr_h = EPR64_MAX_SIZE>>8; 
uint8_t i2cAddr_h = 0x01; 
uint8_t i2cAddr_l = 0; 
uint8_t Check_Error = 0;
uint8_t i2cData[16] = {
0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
uint8_t i2cDataOne;

uint8_t i2cReadBuffer[16] ;

    /*  first write 0x10 bytes */
    Check_Error = I2C_PAGE_WRITE(SID, i2cAddr_h, i2cAddr_l, 16, i2cData);

    /* if error, display address & data */
    if(Check_Error != 0)
    {
      Print_String("Error Address =0x$", 0);
      Print_HEX2Str(Check_Error, 1);
      Print_HEX2Str(i2cAddr_h, 0);
      Print_HEX2Str(i2cAddr_l, 1);
    }

    /* after read 0x10 bytes */
    Print_String("Read Address =0x$", 0);
    Print_HEX2Str(i2cAddr_h, 0);
    Print_HEX2Str(0, 1);
    
    
    I2C_Sequential_READ(SID, i2cAddr_h, i2cAddr_l, 0x10, i2cReadBuffer);
    
    
    /* display read 0x10 bytes */
    for(i=0; i<0x10; i++)
    {
      Print_HEX2Str(*(i2cReadBuffer+i), 1);
    }
}




/*****************************************************************************
 * Author:      Eric
 * Function:    use to read 0xc0,0xc1 
 * Description: Test write 0x10 byte, and read again, check data
 *****************************************************************************/
void I2C_TEST_10(void)
{

#if 1

/*  read 0xC0, 0xC1 2 bytes data, need read 0x73,0x10 */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0xC0;    /* = address */
    *(BufferRec+2) = 0x02;    /* = length  */
//    I2C_MasterWrite(BufferRec, 3+1, 0x08, &I2CMS);
    I2C_mWrite(BufferRec, 3+1, ARDUINO_SID);
//    I2C_MasterRead(BufferRec, 2, 0x08, &I2CMS);     /* for test  */
    I2C_mREAD(BufferRec, 2, ARDUINO_SID);

    SR_0xA0_ADO_Error = *BufferRec;
    SR_0xA1_ADO_Request = *(BufferRec+1);

/*  print 0xA0, 0xA1 2 bytes data */
    Print_String("Check 0xC0 =0x$", 0);
    Print_HEX2Str(SR_0xA0_ADO_Error, 1);
    Print_String("Check 0xC1 =0x$", 0);
    Print_HEX2Str(SR_0xA1_ADO_Request, 1);    
#endif
}




/*****************************************************************************
 * Author:      eric
 * Function:    I2C_BYTE_WRITE
 * Description: write one byte
 slave_addr = 1010 + 000 + 0 = 0xC0
 reg_addr   = Address
 
 * 23 x 89 = 2047
 * 23 x 10 = 230
 * 
 * inside   0-9     10
 * ouside   10-98   89
 * 
 * return:  = 0     ok
 *          = 1     write error     HW error can't write save
 *          = 2     over error      no space to save
 *****************************************************************************/
uint8_t Save_QMD_EEPROM(uint8_t *DataBuffer)
{
uint8_t mdqCOUNT    = DATAEE_ReadByte(EROM_MDQ_COUNT); 
uint8_t mdqCURSOR   = DATAEE_ReadByte(EROM_MDQ_CURSOR);
uint8_t calCURSOR   = 0; 
uint16_t calADDRESS = 0;

uint8_t SID = EPR64_SID;
uint8_t i2cAddr_h = 0; 
uint8_t i2cAddr_l = 0; 
uint8_t Check_Error = 0;
//uint8_t i2cData[23];
uint8_t i = 0;


    /*  max = 98, over = error */
    if(mdqCOUNT >= 99)
        return 2;
    
    /*  QSave count +1 */
    mdqCOUNT++;
 
    /*  cal save number */
    calCURSOR = mdqCURSOR + mdqCOUNT;
        
    /*  if over max, from zero to go */
    if(calCURSOR >= 99)
        calCURSOR -= 99;
    
    /*  check use inside or outside space */
    /*  0-9     inside
        10-89   outside */
    if(calCURSOR > 10)
    {
        calADDRESS = (calCURSOR-10) *23;
        
        i2cAddr_h = calADDRESS >> 8;
        i2cAddr_l = calADDRESS && 0xFF;
        Check_Error = I2C_PAGE_WRITE(SID, i2cAddr_h, i2cAddr_l, 23, DataBuffer);
        
        if(Check_Error != 0)
        {
          Print_String("Error Address =0x$", 0);
          Print_HEX2Str(Check_Error, 1);
          Print_HEX2Str(i2cAddr_h, 0);
          Print_HEX2Str(i2cAddr_l, 1);
          return 1;
        }
    }
    else
    {
        i2cAddr_l = calCURSOR *23;
        for(i=0;i<23;i++)
            DATAEE_WriteByte(i2cAddr_l+i, *(DataBuffer+i));
    }


     
    
    return 0;
}



/*****************************************************************************
 * Author:      eric
 * Function:    I2C_BYTE_WRITE
 * Description: write one byte
 slave_addr = 1010 + 000 + 0 = 0xC0
 reg_addr   = Address
 
 * 23 x 89 = 2047
 * 23 x 10 = 230
 * 
 * inside   0-9     10
 * ouside   10-98   89
 * 
 * return:  = 0     ok
 *          = 1     no data need to read
  
 *****************************************************************************/
uint8_t Load_QMD_EEPROM(uint8_t *DataBuffer)
{
/*  how many data to keep */
uint8_t mdqCOUNT    = DATAEE_ReadByte(EROM_MDQ_COUNT); 
/*  file header */
uint8_t mdqCURSOR   = DATAEE_ReadByte(EROM_MDQ_CURSOR);
uint8_t calCURSOR   = 0; 
uint16_t calADDRESS = 0;

uint8_t SID = EPR64_SID;
uint8_t i2cAddr_h = 0; 
uint8_t i2cAddr_l = 0; 
uint8_t Check_Error = 0;
//uint8_t i2cData[23];
uint8_t i = 0;


    /*  max = 98, over = error */
    if(mdqCOUNT == 0)
        return 1;
    
    /*  QLoad count -1 */
    mdqCOUNT--;
 
    /*  cal save number */
    calCURSOR = mdqCURSOR;
    mdqCURSOR++;
        
    /*  if over max, from zero to go */
//    if(calCURSOR >= 99)
//        calCURSOR -= 99;
    
    /*  check use inside or outside space */
    /*  0-9     inside
        10-89   outside */
    if(calCURSOR > 10)
    {
        calADDRESS = (calCURSOR-10) *23;
        
        i2cAddr_h = calADDRESS >> 8;
        i2cAddr_l = calADDRESS && 0xFF;
        I2C_Sequential_READ(SID, i2cAddr_h, i2cAddr_l, 23, DataBuffer);
        
    }
    else
    {
        i2cAddr_l = calCURSOR *23;
        for(i=0;i<23;i++)
            *(DataBuffer+i) = DATAEE_ReadByte(i2cAddr_l+i); 
    }


     
    
    return 0;
}






/*****************************************************************************
 * Author:      Eric
 * Function:    
 * Description: 
 *****************************************************************************/
void check_ADO_I2C(void)
{
#if 1

    /*  read 0xC0, 0xC1 2 bytes data, need read 0x73,0x10 */
    *(BufferRec+0) = 0x00;    /* = 0 read, =1 write   */
    *(BufferRec+1) = 0xC0;    /* = address */
    *(BufferRec+2) = 0x02;    /* = length  */
    I2C_mWrite(BufferRec, 3+1, ARDUINO_SID);
    I2C_mREAD(BufferRec, 2, ARDUINO_SID);

    /*  print 0xC0, 0xC1 2 bytes data */
    Print_String("Check 0xC0 =0x$", 0);
    Print_HEX2Str(*BufferRec, 1);
    Print_String("Check 0xC1 =0x$", 0);
    Print_HEX2Str(*(BufferRec+1), 1);  
    
    if( (*BufferRec != 0x73) || (*(BufferRec+1) != 0x10) )
    {
        ErrorFlag = EF_I2C;
        Print_String("Set Error Flag = I2C$", 1);
    }
#endif
}






/**
 End of File
 */