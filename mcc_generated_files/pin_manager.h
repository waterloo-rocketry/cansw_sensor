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

// get/set channel_CURR_12V aliases
#define channel_CURR_12V_TRIS                 TRISAbits.TRISA1
#define channel_CURR_12V_LAT                  LATAbits.LATA1
#define channel_CURR_12V_PORT                 PORTAbits.RA1
#define channel_CURR_12V_WPU                  WPUAbits.WPUA1
#define channel_CURR_12V_OD                   ODCONAbits.ODCA1
#define channel_CURR_12V_ANS                  ANSELAbits.ANSELA1
#define channel_CURR_12V_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define channel_CURR_12V_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define channel_CURR_12V_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define channel_CURR_12V_GetValue()           PORTAbits.RA1
#define channel_CURR_12V_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define channel_CURR_12V_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define channel_CURR_12V_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define channel_CURR_12V_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define channel_CURR_12V_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define channel_CURR_12V_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define channel_CURR_12V_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define channel_CURR_12V_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set channel_SENSOR_3 aliases
#define channel_SENSOR_3_TRIS                 TRISAbits.TRISA2
#define channel_SENSOR_3_LAT                  LATAbits.LATA2
#define channel_SENSOR_3_PORT                 PORTAbits.RA2
#define channel_SENSOR_3_WPU                  WPUAbits.WPUA2
#define channel_SENSOR_3_OD                   ODCONAbits.ODCA2
#define channel_SENSOR_3_ANS                  ANSELAbits.ANSELA2
#define channel_SENSOR_3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define channel_SENSOR_3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define channel_SENSOR_3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define channel_SENSOR_3_GetValue()           PORTAbits.RA2
#define channel_SENSOR_3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define channel_SENSOR_3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define channel_SENSOR_3_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define channel_SENSOR_3_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define channel_SENSOR_3_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define channel_SENSOR_3_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define channel_SENSOR_3_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define channel_SENSOR_3_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set channel_SENSOR_4 aliases
#define channel_SENSOR_4_TRIS                 TRISAbits.TRISA3
#define channel_SENSOR_4_LAT                  LATAbits.LATA3
#define channel_SENSOR_4_PORT                 PORTAbits.RA3
#define channel_SENSOR_4_WPU                  WPUAbits.WPUA3
#define channel_SENSOR_4_OD                   ODCONAbits.ODCA3
#define channel_SENSOR_4_ANS                  ANSELAbits.ANSELA3
#define channel_SENSOR_4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define channel_SENSOR_4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define channel_SENSOR_4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define channel_SENSOR_4_GetValue()           PORTAbits.RA3
#define channel_SENSOR_4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define channel_SENSOR_4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define channel_SENSOR_4_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define channel_SENSOR_4_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define channel_SENSOR_4_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define channel_SENSOR_4_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define channel_SENSOR_4_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define channel_SENSOR_4_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set channel_SENSOR_1 aliases
#define channel_SENSOR_1_TRIS                 TRISAbits.TRISA4
#define channel_SENSOR_1_LAT                  LATAbits.LATA4
#define channel_SENSOR_1_PORT                 PORTAbits.RA4
#define channel_SENSOR_1_WPU                  WPUAbits.WPUA4
#define channel_SENSOR_1_OD                   ODCONAbits.ODCA4
#define channel_SENSOR_1_ANS                  ANSELAbits.ANSELA4
#define channel_SENSOR_1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define channel_SENSOR_1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define channel_SENSOR_1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define channel_SENSOR_1_GetValue()           PORTAbits.RA4
#define channel_SENSOR_1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define channel_SENSOR_1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define channel_SENSOR_1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define channel_SENSOR_1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define channel_SENSOR_1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define channel_SENSOR_1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define channel_SENSOR_1_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define channel_SENSOR_1_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set channel_SENSOR_2 aliases
#define channel_SENSOR_2_TRIS                 TRISAbits.TRISA5
#define channel_SENSOR_2_LAT                  LATAbits.LATA5
#define channel_SENSOR_2_PORT                 PORTAbits.RA5
#define channel_SENSOR_2_WPU                  WPUAbits.WPUA5
#define channel_SENSOR_2_OD                   ODCONAbits.ODCA5
#define channel_SENSOR_2_ANS                  ANSELAbits.ANSELA5
#define channel_SENSOR_2_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define channel_SENSOR_2_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define channel_SENSOR_2_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define channel_SENSOR_2_GetValue()           PORTAbits.RA5
#define channel_SENSOR_2_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define channel_SENSOR_2_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define channel_SENSOR_2_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define channel_SENSOR_2_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define channel_SENSOR_2_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define channel_SENSOR_2_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define channel_SENSOR_2_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define channel_SENSOR_2_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

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