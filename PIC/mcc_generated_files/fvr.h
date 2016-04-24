/**
  FVR Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    fvr.h

  @Summary
    This is the generated header file for the FVR driver using MPLAB� Code Configurator

  @Description
    This header file provides APIs for driver for FVR.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
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

#ifndef _FVR_H
#define _FVR_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: FVR APIs
     */

    /**
      @Summary
        Initializes the FVR

      @Description
        This routine initializes the FVR.
        This routine must be called before any other FVR routine is called.
        This routine should only be called once during system initialization.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment
    

      @Example
        <code>
        FVR_Initialize();
        </code>
     */
    void FVR_Initialize(void);

    /**
      @Summary
        Gets the FVR output ready status.

      @Description
        This routine gets the FVR output ready status.

      @Preconditions
        The FVR_Initialize() routine should be called
        prior to use this routine.

      @Param
        None

      @Returns
         true  - FVR module is ready for use.
         false - FVR module is not ready for use.

      @Example
        <code>
        FVR_Initialize();

        if(FVR_IsOutputReady())
        {
              //user code
        }
        else
        {
              //user code
        }
        </code>
     */
    bool FVR_IsOutputReady(void);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif // _FVR_H
/**
 End of File
 */

