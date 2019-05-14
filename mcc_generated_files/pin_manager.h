/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18LF26K83
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_CURR_5V aliases
#define channel_CURR_5V_TRIS                 TRISAbits.TRISA0
#define channel_CURR_5V_LAT                  LATAbits.LATA0
#define channel_CURR_5V_PORT                 PORTAbits.RA0
#define channel_CURR_5V_WPU                  WPUAbits.WPUA0
#define channel_CURR_5V_OD                   ODCONAbits.ODCA0
#define channel_CURR_5V_ANS                  ANSELAbits.ANSELA0
#define channel_CURR_5V_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_CURR_5V_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_CURR_5V_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_CURR_5V_GetValue()           PORTAbits.RA0
#define channel_CURR_5V_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_CURR_5V_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_CURR_5V_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define channel_CURR_5V_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define channel_CURR_5V_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define channel_CURR_5V_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define channel_CURR_5V_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define channel_CURR_5V_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set channel_THERM aliases
#define channel_THERM_TRIS                 TRISAbits.TRISA1
#define channel_THERM_LAT                  LATAbits.LATA1
#define channel_THERM_PORT                 PORTAbits.RA1
#define channel_THERM_WPU                  WPUAbits.WPUA1
#define channel_THERM_OD                   ODCONAbits.ODCA1
#define channel_THERM_ANS                  ANSELAbits.ANSELA1
#define channel_THERM_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define channel_THERM_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define channel_THERM_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define channel_THERM_GetValue()           PORTAbits.RA1
#define channel_THERM_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define channel_THERM_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define channel_THERM_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define channel_THERM_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define channel_THERM_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define channel_THERM_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define channel_THERM_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define channel_THERM_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set channel_PRESSURE aliases
#define channel_PRESSURE_TRIS                 TRISAbits.TRISA2
#define channel_PRESSURE_LAT                  LATAbits.LATA2
#define channel_PRESSURE_PORT                 PORTAbits.RA2
#define channel_PRESSURE_WPU                  WPUAbits.WPUA2
#define channel_PRESSURE_OD                   ODCONAbits.ODCA2
#define channel_PRESSURE_ANS                  ANSELAbits.ANSELA2
#define channel_PRESSURE_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define channel_PRESSURE_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define channel_PRESSURE_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define channel_PRESSURE_GetValue()           PORTAbits.RA2
#define channel_PRESSURE_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define channel_PRESSURE_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define channel_PRESSURE_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define channel_PRESSURE_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define channel_PRESSURE_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define channel_PRESSURE_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define channel_PRESSURE_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define channel_PRESSURE_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set channel_CURR_12V aliases
#define channel_CURR_12V_TRIS                 TRISAbits.TRISA3
#define channel_CURR_12V_LAT                  LATAbits.LATA3
#define channel_CURR_12V_PORT                 PORTAbits.RA3
#define channel_CURR_12V_WPU                  WPUAbits.WPUA3
#define channel_CURR_12V_OD                   ODCONAbits.ODCA3
#define channel_CURR_12V_ANS                  ANSELAbits.ANSELA3
#define channel_CURR_12V_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define channel_CURR_12V_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define channel_CURR_12V_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define channel_CURR_12V_GetValue()           PORTAbits.RA3
#define channel_CURR_12V_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define channel_CURR_12V_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define channel_CURR_12V_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define channel_CURR_12V_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define channel_CURR_12V_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define channel_CURR_12V_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define channel_CURR_12V_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define channel_CURR_12V_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

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