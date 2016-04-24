/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB� Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
        Device            :  PIC16F1789
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set MESURE_DO aliases
#define MESURE_DO_TRIS               TRISA0
#define MESURE_DO_LAT                LATA0
#define MESURE_DO_PORT               RA0
#define MESURE_DO_WPU                WPUA0
#define MESURE_DO_ANS                ANSA0
#define MESURE_DO_SetHigh()    do { LATA0 = 1; } while(0)
#define MESURE_DO_SetLow()   do { LATA0 = 0; } while(0)
#define MESURE_DO_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define MESURE_DO_GetValue()         RA0
#define MESURE_DO_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define MESURE_DO_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define MESURE_DO_SetPullup()    do { WPUA0 = 1; } while(0)
#define MESURE_DO_ResetPullup()   do { WPUA0 = 0; } while(0)
#define MESURE_DO_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define MESURE_DO_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set OPA1OUT aliases
#define OPA1OUT_TRIS               TRISA1
#define OPA1OUT_LAT                LATA1
#define OPA1OUT_PORT               RA1
#define OPA1OUT_WPU                WPUA1
#define OPA1OUT_ANS                ANSA1
#define OPA1OUT_SetHigh()    do { LATA1 = 1; } while(0)
#define OPA1OUT_SetLow()   do { LATA1 = 0; } while(0)
#define OPA1OUT_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define OPA1OUT_GetValue()         RA1
#define OPA1OUT_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define OPA1OUT_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define OPA1OUT_SetPullup()    do { WPUA1 = 1; } while(0)
#define OPA1OUT_ResetPullup()   do { WPUA1 = 0; } while(0)
#define OPA1OUT_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define OPA1OUT_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set EN_AD8220 aliases
#define EN_AD8220_TRIS               TRISA2
#define EN_AD8220_LAT                LATA2
#define EN_AD8220_PORT               RA2
#define EN_AD8220_WPU                WPUA2
#define EN_AD8220_ANS                ANSA2
#define EN_AD8220_SetHigh()    do { LATA2 = 1; } while(0)
#define EN_AD8220_SetLow()   do { LATA2 = 0; } while(0)
#define EN_AD8220_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define EN_AD8220_GetValue()         RA2
#define EN_AD8220_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define EN_AD8220_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define EN_AD8220_SetPullup()    do { WPUA2 = 1; } while(0)
#define EN_AD8220_ResetPullup()   do { WPUA2 = 0; } while(0)
#define EN_AD8220_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define EN_AD8220_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set TDS_PWM aliases
#define TDS_PWM_TRIS               TRISA4
#define TDS_PWM_LAT                LATA4
#define TDS_PWM_PORT               RA4
#define TDS_PWM_WPU                WPUA4
#define TDS_PWM_ANS                ANSA4
#define TDS_PWM_SetHigh()    do { LATA4 = 1; } while(0)
#define TDS_PWM_SetLow()   do { LATA4 = 0; } while(0)
#define TDS_PWM_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define TDS_PWM_GetValue()         RA4
#define TDS_PWM_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define TDS_PWM_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

#define TDS_PWM_SetPullup()    do { WPUA4 = 1; } while(0)
#define TDS_PWM_ResetPullup()   do { WPUA4 = 0; } while(0)
#define TDS_PWM_SetAnalogMode()   do { ANSA4 = 1; } while(0)
#define TDS_PWM_SetDigitalMode()   do { ANSA4 = 0; } while(0)
// get/set OPA1INNeg aliases
#define OPA1INNeg_TRIS               TRISA5
#define OPA1INNeg_LAT                LATA5
#define OPA1INNeg_PORT               RA5
#define OPA1INNeg_WPU                WPUA5
#define OPA1INNeg_ANS                ANSA5
#define OPA1INNeg_SetHigh()    do { LATA5 = 1; } while(0)
#define OPA1INNeg_SetLow()   do { LATA5 = 0; } while(0)
#define OPA1INNeg_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define OPA1INNeg_GetValue()         RA5
#define OPA1INNeg_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define OPA1INNeg_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define OPA1INNeg_SetPullup()    do { WPUA5 = 1; } while(0)
#define OPA1INNeg_ResetPullup()   do { WPUA5 = 0; } while(0)
#define OPA1INNeg_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define OPA1INNeg_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set PH_CN aliases
#define PH_CN_TRIS               TRISA6
#define PH_CN_LAT                LATA6
#define PH_CN_PORT               RA6
#define PH_CN_WPU                WPUA6
#define PH_CN_SetHigh()    do { LATA6 = 1; } while(0)
#define PH_CN_SetLow()   do { LATA6 = 0; } while(0)
#define PH_CN_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define PH_CN_GetValue()         RA6
#define PH_CN_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define PH_CN_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

#define PH_CN_SetPullup()    do { WPUA6 = 1; } while(0)
#define PH_CN_ResetPullup()   do { WPUA6 = 0; } while(0)
// get/set NH3_CN aliases
#define NH3_CN_TRIS               TRISA7
#define NH3_CN_LAT                LATA7
#define NH3_CN_PORT               RA7
#define NH3_CN_WPU                WPUA7
#define NH3_CN_ANS                ANSA7
#define NH3_CN_SetHigh()    do { LATA7 = 1; } while(0)
#define NH3_CN_SetLow()   do { LATA7 = 0; } while(0)
#define NH3_CN_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define NH3_CN_GetValue()         RA7
#define NH3_CN_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define NH3_CN_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

#define NH3_CN_SetPullup()    do { WPUA7 = 1; } while(0)
#define NH3_CN_ResetPullup()   do { WPUA7 = 0; } while(0)
#define NH3_CN_SetAnalogMode()   do { ANSA7 = 1; } while(0)
#define NH3_CN_SetDigitalMode()   do { ANSA7 = 0; } while(0)
// get/set MESURE_ISE aliases
#define MESURE_ISE_TRIS               TRISB0
#define MESURE_ISE_LAT                LATB0
#define MESURE_ISE_PORT               RB0
#define MESURE_ISE_WPU                WPUB0
#define MESURE_ISE_ANS                ANSB0
#define MESURE_ISE_SetHigh()    do { LATB0 = 1; } while(0)
#define MESURE_ISE_SetLow()   do { LATB0 = 0; } while(0)
#define MESURE_ISE_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define MESURE_ISE_GetValue()         RB0
#define MESURE_ISE_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define MESURE_ISE_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define MESURE_ISE_SetPullup()    do { WPUB0 = 1; } while(0)
#define MESURE_ISE_ResetPullup()   do { WPUB0 = 0; } while(0)
#define MESURE_ISE_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define MESURE_ISE_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set OPA2OUT aliases
#define OPA2OUT_TRIS               TRISB1
#define OPA2OUT_LAT                LATB1
#define OPA2OUT_PORT               RB1
#define OPA2OUT_WPU                WPUB1
#define OPA2OUT_ANS                ANSB1
#define OPA2OUT_SetHigh()    do { LATB1 = 1; } while(0)
#define OPA2OUT_SetLow()   do { LATB1 = 0; } while(0)
#define OPA2OUT_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define OPA2OUT_GetValue()         RB1
#define OPA2OUT_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define OPA2OUT_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define OPA2OUT_SetPullup()    do { WPUB1 = 1; } while(0)
#define OPA2OUT_ResetPullup()   do { WPUB1 = 0; } while(0)
#define OPA2OUT_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define OPA2OUT_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set OPA2INNeg aliases
#define OPA2INNeg_TRIS               TRISB2
#define OPA2INNeg_LAT                LATB2
#define OPA2INNeg_PORT               RB2
#define OPA2INNeg_WPU                WPUB2
#define OPA2INNeg_ANS                ANSB2
#define OPA2INNeg_SetHigh()    do { LATB2 = 1; } while(0)
#define OPA2INNeg_SetLow()   do { LATB2 = 0; } while(0)
#define OPA2INNeg_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define OPA2INNeg_GetValue()         RB2
#define OPA2INNeg_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define OPA2INNeg_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define OPA2INNeg_SetPullup()    do { WPUB2 = 1; } while(0)
#define OPA2INNeg_ResetPullup()   do { WPUB2 = 0; } while(0)
#define OPA2INNeg_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define OPA2INNeg_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set OPA2INPos aliases
#define OPA2INPos_TRIS               TRISB3
#define OPA2INPos_LAT                LATB3
#define OPA2INPos_PORT               RB3
#define OPA2INPos_WPU                WPUB3
#define OPA2INPos_ANS                ANSB3
#define OPA2INPos_SetHigh()    do { LATB3 = 1; } while(0)
#define OPA2INPos_SetLow()   do { LATB3 = 0; } while(0)
#define OPA2INPos_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define OPA2INPos_GetValue()         RB3
#define OPA2INPos_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define OPA2INPos_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define OPA2INPos_SetPullup()    do { WPUB3 = 1; } while(0)
#define OPA2INPos_ResetPullup()   do { WPUB3 = 0; } while(0)
#define OPA2INPos_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define OPA2INPos_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set MESURE_TDS aliases
#define MESURE_TDS_TRIS               TRISB4
#define MESURE_TDS_LAT                LATB4
#define MESURE_TDS_PORT               RB4
#define MESURE_TDS_WPU                WPUB4
#define MESURE_TDS_ANS                ANSB4
#define MESURE_TDS_SetHigh()    do { LATB4 = 1; } while(0)
#define MESURE_TDS_SetLow()   do { LATB4 = 0; } while(0)
#define MESURE_TDS_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define MESURE_TDS_GetValue()         RB4
#define MESURE_TDS_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define MESURE_TDS_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define MESURE_TDS_SetPullup()    do { WPUB4 = 1; } while(0)
#define MESURE_TDS_ResetPullup()   do { WPUB4 = 0; } while(0)
#define MESURE_TDS_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define MESURE_TDS_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set REFEL_CN aliases
#define REFEL_CN_TRIS               TRISB5
#define REFEL_CN_LAT                LATB5
#define REFEL_CN_PORT               RB5
#define REFEL_CN_WPU                WPUB5
#define REFEL_CN_ANS                ANSB5
#define REFEL_CN_SetHigh()    do { LATB5 = 1; } while(0)
#define REFEL_CN_SetLow()   do { LATB5 = 0; } while(0)
#define REFEL_CN_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define REFEL_CN_GetValue()         RB5
#define REFEL_CN_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define REFEL_CN_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define REFEL_CN_SetPullup()    do { WPUB5 = 1; } while(0)
#define REFEL_CN_ResetPullup()   do { WPUB5 = 0; } while(0)
#define REFEL_CN_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define REFEL_CN_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set RST_ADO aliases
#define RST_ADO_TRIS               TRISB6
#define RST_ADO_LAT                LATB6
#define RST_ADO_PORT               RB6
#define RST_ADO_WPU                WPUB6
#define RST_ADO_ANS                ANSB6
#define RST_ADO_SetHigh()    do { LATB6 = 1; } while(0)
#define RST_ADO_SetLow()   do { LATB6 = 0; } while(0)
#define RST_ADO_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define RST_ADO_GetValue()         RB6
#define RST_ADO_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define RST_ADO_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define RST_ADO_SetPullup()    do { WPUB6 = 1; } while(0)
#define RST_ADO_ResetPullup()   do { WPUB6 = 0; } while(0)
#define RST_ADO_SetAnalogMode()   do { ANSB6 = 1; } while(0)
#define RST_ADO_SetDigitalMode()   do { ANSB6 = 0; } while(0)
// get/set EN_WIFI aliases
#define EN_WIFI_TRIS               TRISB7
#define EN_WIFI_LAT                LATB7
#define EN_WIFI_PORT               RB7
#define EN_WIFI_WPU                WPUB7
#define EN_WIFI_SetHigh()    do { LATB7 = 1; } while(0)
#define EN_WIFI_SetLow()   do { LATB7 = 0; } while(0)
#define EN_WIFI_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define EN_WIFI_GetValue()         RB7
#define EN_WIFI_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define EN_WIFI_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define EN_WIFI_SetPullup()    do { WPUB7 = 1; } while(0)
#define EN_WIFI_ResetPullup()   do { WPUB7 = 0; } while(0)
// get/set MG_CN aliases
#define MG_CN_TRIS               TRISC0
#define MG_CN_LAT                LATC0
#define MG_CN_PORT               RC0
#define MG_CN_WPU                WPUC0
#define MG_CN_ANS                ANSC0
#define MG_CN_SetHigh()    do { LATC0 = 1; } while(0)
#define MG_CN_SetLow()   do { LATC0 = 0; } while(0)
#define MG_CN_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define MG_CN_GetValue()         RC0
#define MG_CN_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define MG_CN_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

#define MG_CN_SetPullup()    do { WPUC0 = 1; } while(0)
#define MG_CN_ResetPullup()   do { WPUC0 = 0; } while(0)
#define MG_CN_SetAnalogMode()   do { ANSC0 = 1; } while(0)
#define MG_CN_SetDigitalMode()   do { ANSC0 = 0; } while(0)
// get/set CA_CN aliases
#define CA_CN_TRIS               TRISC1
#define CA_CN_LAT                LATC1
#define CA_CN_PORT               RC1
#define CA_CN_WPU                WPUC1
#define CA_CN_ANS                ANSC1
#define CA_CN_SetHigh()    do { LATC1 = 1; } while(0)
#define CA_CN_SetLow()   do { LATC1 = 0; } while(0)
#define CA_CN_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define CA_CN_GetValue()         RC1
#define CA_CN_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define CA_CN_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define CA_CN_SetPullup()    do { WPUC1 = 1; } while(0)
#define CA_CN_ResetPullup()   do { WPUC1 = 0; } while(0)
#define CA_CN_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define CA_CN_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set TDS_CN aliases
#define TDS_CN_TRIS               TRISC2
#define TDS_CN_LAT                LATC2
#define TDS_CN_PORT               RC2
#define TDS_CN_WPU                WPUC2
#define TDS_CN_ANS                ANSC2
#define TDS_CN_SetHigh()    do { LATC2 = 1; } while(0)
#define TDS_CN_SetLow()   do { LATC2 = 0; } while(0)
#define TDS_CN_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define TDS_CN_GetValue()         RC2
#define TDS_CN_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define TDS_CN_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define TDS_CN_SetPullup()    do { WPUC2 = 1; } while(0)
#define TDS_CN_ResetPullup()   do { WPUC2 = 0; } while(0)
#define TDS_CN_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define TDS_CN_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set PIC_SCL aliases
#define PIC_SCL_TRIS               TRISC3
#define PIC_SCL_LAT                LATC3
#define PIC_SCL_PORT               RC3
#define PIC_SCL_WPU                WPUC3
#define PIC_SCL_ANS                ANSC3
#define PIC_SCL_SetHigh()    do { LATC3 = 1; } while(0)
#define PIC_SCL_SetLow()   do { LATC3 = 0; } while(0)
#define PIC_SCL_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define PIC_SCL_GetValue()         RC3
#define PIC_SCL_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define PIC_SCL_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define PIC_SCL_SetPullup()    do { WPUC3 = 1; } while(0)
#define PIC_SCL_ResetPullup()   do { WPUC3 = 0; } while(0)
#define PIC_SCL_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define PIC_SCL_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set PIC_SDA aliases
#define PIC_SDA_TRIS               TRISC4
#define PIC_SDA_LAT                LATC4
#define PIC_SDA_PORT               RC4
#define PIC_SDA_WPU                WPUC4
#define PIC_SDA_ANS                ANSC4
#define PIC_SDA_SetHigh()    do { LATC4 = 1; } while(0)
#define PIC_SDA_SetLow()   do { LATC4 = 0; } while(0)
#define PIC_SDA_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define PIC_SDA_GetValue()         RC4
#define PIC_SDA_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define PIC_SDA_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define PIC_SDA_SetPullup()    do { WPUC4 = 1; } while(0)
#define PIC_SDA_ResetPullup()   do { WPUC4 = 0; } while(0)
#define PIC_SDA_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define PIC_SDA_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set DO_CN aliases
#define DO_CN_TRIS               TRISC5
#define DO_CN_LAT                LATC5
#define DO_CN_PORT               RC5
#define DO_CN_WPU                WPUC5
#define DO_CN_ANS                ANSC5
#define DO_CN_SetHigh()    do { LATC5 = 1; } while(0)
#define DO_CN_SetLow()   do { LATC5 = 0; } while(0)
#define DO_CN_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define DO_CN_GetValue()         RC5
#define DO_CN_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define DO_CN_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define DO_CN_SetPullup()    do { WPUC5 = 1; } while(0)
#define DO_CN_ResetPullup()   do { WPUC5 = 0; } while(0)
#define DO_CN_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define DO_CN_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set TX aliases
#define TX_TRIS               TRISC6
#define TX_LAT                LATC6
#define TX_PORT               RC6
#define TX_WPU                WPUC6
#define TX_ANS                ANSC6
#define TX_SetHigh()    do { LATC6 = 1; } while(0)
#define TX_SetLow()   do { LATC6 = 0; } while(0)
#define TX_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX_GetValue()         RC6
#define TX_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX_SetPullup()    do { WPUC6 = 1; } while(0)
#define TX_ResetPullup()   do { WPUC6 = 0; } while(0)
#define TX_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX aliases
#define RX_TRIS               TRISC7
#define RX_LAT                LATC7
#define RX_PORT               RC7
#define RX_WPU                WPUC7
#define RX_ANS                ANSC7
#define RX_SetHigh()    do { LATC7 = 1; } while(0)
#define RX_SetLow()   do { LATC7 = 0; } while(0)
#define RX_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX_GetValue()         RC7
#define RX_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX_SetPullup()    do { WPUC7 = 1; } while(0)
#define RX_ResetPullup()   do { WPUC7 = 0; } while(0)
#define RX_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX_SetDigitalMode()   do { ANSC7 = 0; } while(0)
// get/set OPA3INPos aliases
#define OPA3INPos_TRIS               TRISD0
#define OPA3INPos_LAT                LATD0
#define OPA3INPos_PORT               RD0
#define OPA3INPos_WPU                WPUD0
#define OPA3INPos_ANS                ANSD0
#define OPA3INPos_SetHigh()    do { LATD0 = 1; } while(0)
#define OPA3INPos_SetLow()   do { LATD0 = 0; } while(0)
#define OPA3INPos_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define OPA3INPos_GetValue()         RD0
#define OPA3INPos_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define OPA3INPos_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define OPA3INPos_SetPullup()    do { WPUD0 = 1; } while(0)
#define OPA3INPos_ResetPullup()   do { WPUD0 = 0; } while(0)
#define OPA3INPos_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define OPA3INPos_SetDigitalMode()   do { ANSD0 = 0; } while(0)
// get/set OPA3OUT aliases
#define OPA3OUT_TRIS               TRISD1
#define OPA3OUT_LAT                LATD1
#define OPA3OUT_PORT               RD1
#define OPA3OUT_WPU                WPUD1
#define OPA3OUT_ANS                ANSD1
#define OPA3OUT_SetHigh()    do { LATD1 = 1; } while(0)
#define OPA3OUT_SetLow()   do { LATD1 = 0; } while(0)
#define OPA3OUT_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define OPA3OUT_GetValue()         RD1
#define OPA3OUT_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define OPA3OUT_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define OPA3OUT_SetPullup()    do { WPUD1 = 1; } while(0)
#define OPA3OUT_ResetPullup()   do { WPUD1 = 0; } while(0)
#define OPA3OUT_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define OPA3OUT_SetDigitalMode()   do { ANSD1 = 0; } while(0)
// get/set OPA3INNeg aliases
#define OPA3INNeg_TRIS               TRISD2
#define OPA3INNeg_LAT                LATD2
#define OPA3INNeg_PORT               RD2
#define OPA3INNeg_WPU                WPUD2
#define OPA3INNeg_ANS                ANSD2
#define OPA3INNeg_SetHigh()    do { LATD2 = 1; } while(0)
#define OPA3INNeg_SetLow()   do { LATD2 = 0; } while(0)
#define OPA3INNeg_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define OPA3INNeg_GetValue()         RD2
#define OPA3INNeg_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define OPA3INNeg_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define OPA3INNeg_SetPullup()    do { WPUD2 = 1; } while(0)
#define OPA3INNeg_ResetPullup()   do { WPUD2 = 0; } while(0)
#define OPA3INNeg_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define OPA3INNeg_SetDigitalMode()   do { ANSD2 = 0; } while(0)
// get/set LED_GREEN aliases
#define LED_GREEN_TRIS               TRISD3
#define LED_GREEN_LAT                LATD3
#define LED_GREEN_PORT               RD3
#define LED_GREEN_WPU                WPUD3
#define LED_GREEN_SetHigh()    do { LATD3 = 1; } while(0)
#define LED_GREEN_SetLow()   do { LATD3 = 0; } while(0)
#define LED_GREEN_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define LED_GREEN_GetValue()         RD3
#define LED_GREEN_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define LED_GREEN_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define LED_GREEN_SetPullup()    do { WPUD3 = 1; } while(0)
#define LED_GREEN_ResetPullup()   do { WPUD3 = 0; } while(0)
// get/set TEMP_DQ aliases
#define TEMP_DQ_TRIS               TRISD4
#define TEMP_DQ_LAT                LATD4
#define TEMP_DQ_PORT               RD4
#define TEMP_DQ_WPU                WPUD4
#define TEMP_DQ_SetHigh()    do { LATD4 = 1; } while(0)
#define TEMP_DQ_SetLow()   do { LATD4 = 0; } while(0)
#define TEMP_DQ_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define TEMP_DQ_GetValue()         RD4
#define TEMP_DQ_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define TEMP_DQ_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define TEMP_DQ_SetPullup()    do { WPUD4 = 1; } while(0)
#define TEMP_DQ_ResetPullup()   do { WPUD4 = 0; } while(0)
// get/set ADO_INT aliases
#define ADO_INT_TRIS               TRISD5
#define ADO_INT_LAT                LATD5
#define ADO_INT_PORT               RD5
#define ADO_INT_WPU                WPUD5
#define ADO_INT_SetHigh()    do { LATD5 = 1; } while(0)
#define ADO_INT_SetLow()   do { LATD5 = 0; } while(0)
#define ADO_INT_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define ADO_INT_GetValue()         RD5
#define ADO_INT_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define ADO_INT_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define ADO_INT_SetPullup()    do { WPUD5 = 1; } while(0)
#define ADO_INT_ResetPullup()   do { WPUD5 = 0; } while(0)
// get/set LED_RED aliases
#define LED_RED_TRIS               TRISD6
#define LED_RED_LAT                LATD6
#define LED_RED_PORT               RD6
#define LED_RED_WPU                WPUD6
#define LED_RED_SetHigh()    do { LATD6 = 1; } while(0)
#define LED_RED_SetLow()   do { LATD6 = 0; } while(0)
#define LED_RED_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define LED_RED_GetValue()         RD6
#define LED_RED_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define LED_RED_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define LED_RED_SetPullup()    do { WPUD6 = 1; } while(0)
#define LED_RED_ResetPullup()   do { WPUD6 = 0; } while(0)
// get/set ISE_M aliases
#define ISE_M_TRIS               TRISD7
#define ISE_M_LAT                LATD7
#define ISE_M_PORT               RD7
#define ISE_M_WPU                WPUD7
#define ISE_M_SetHigh()    do { LATD7 = 1; } while(0)
#define ISE_M_SetLow()   do { LATD7 = 0; } while(0)
#define ISE_M_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define ISE_M_GetValue()         RD7
#define ISE_M_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define ISE_M_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define ISE_M_SetPullup()    do { WPUD7 = 1; } while(0)
#define ISE_M_ResetPullup()   do { WPUD7 = 0; } while(0)
// get/set OCPGAIN_CN0 aliases
#define OCPGAIN_CN0_TRIS               TRISE0
#define OCPGAIN_CN0_LAT                LATE0
#define OCPGAIN_CN0_PORT               RE0
#define OCPGAIN_CN0_WPU                WPUE0
#define OCPGAIN_CN0_ANS                ANSE0
#define OCPGAIN_CN0_SetHigh()    do { LATE0 = 1; } while(0)
#define OCPGAIN_CN0_SetLow()   do { LATE0 = 0; } while(0)
#define OCPGAIN_CN0_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define OCPGAIN_CN0_GetValue()         RE0
#define OCPGAIN_CN0_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define OCPGAIN_CN0_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define OCPGAIN_CN0_SetPullup()    do { WPUE0 = 1; } while(0)
#define OCPGAIN_CN0_ResetPullup()   do { WPUE0 = 0; } while(0)
#define OCPGAIN_CN0_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define OCPGAIN_CN0_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set OCPGAIN_CN1 aliases
#define OCPGAIN_CN1_TRIS               TRISE1
#define OCPGAIN_CN1_LAT                LATE1
#define OCPGAIN_CN1_PORT               RE1
#define OCPGAIN_CN1_WPU                WPUE1
#define OCPGAIN_CN1_ANS                ANSE1
#define OCPGAIN_CN1_SetHigh()    do { LATE1 = 1; } while(0)
#define OCPGAIN_CN1_SetLow()   do { LATE1 = 0; } while(0)
#define OCPGAIN_CN1_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define OCPGAIN_CN1_GetValue()         RE1
#define OCPGAIN_CN1_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define OCPGAIN_CN1_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define OCPGAIN_CN1_SetPullup()    do { WPUE1 = 1; } while(0)
#define OCPGAIN_CN1_ResetPullup()   do { WPUE1 = 0; } while(0)
#define OCPGAIN_CN1_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define OCPGAIN_CN1_SetDigitalMode()   do { ANSE1 = 0; } while(0)
// get/set ORP_CN aliases
#define ORP_CN_TRIS               TRISE2
#define ORP_CN_LAT                LATE2
#define ORP_CN_PORT               RE2
#define ORP_CN_WPU                WPUE2
#define ORP_CN_ANS                ANSE2
#define ORP_CN_SetHigh()    do { LATE2 = 1; } while(0)
#define ORP_CN_SetLow()   do { LATE2 = 0; } while(0)
#define ORP_CN_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define ORP_CN_GetValue()         RE2
#define ORP_CN_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define ORP_CN_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define ORP_CN_SetPullup()    do { WPUE2 = 1; } while(0)
#define ORP_CN_ResetPullup()   do { WPUE2 = 0; } while(0)
#define ORP_CN_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define ORP_CN_SetDigitalMode()   do { ANSE2 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */