#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>

#include "mcc_generated_files/mcc.h"
#include "spi.h"

#define WHITE_LED_ON() (LATAbits.LATA0 = 0)
#define WHITE_LED_OFF() (LATAbits.LATA0 = 1)
#define BLUE_LED_ON() (LATBbits.LATB4 = 0)
#define BLUE_LED_OFF() (LATBbits.LATB4 = 1)    
#define RED_LED_ON() (LATBbits.LATB15 = 0)
#define RED_LED_OFF() (LATBbits.LATB15 = 1) 

static void led_init() {
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
    
    TRISBbits.TRISB4 = 0;
    LATBbits.LATB4 = 1;
    
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;
}

int main(int argc, char** argv) {
    SYSTEM_Initialize();
    CLOCK_Initialize();
    
    led_init();
    // spi_init();
    // schip_select_init();
    
    /*
    __delay32(100 * (_XTAL_FREQ / 1000));
    
    imu1_spi_select();
    spi_write(0x3);
    spi_write(1 << 3);
    imu1_spi_release();
     */
    
    while (1) {
        //imu1_spi_select();
        
        // read from address 0x0 (WHO_AM_I)
        //spi_write(1 << 7);
        //uint8_t result = spi_read();
        //imu1_spi_release();

        if (result == 0xea) {
            WHITE_LED_ON();
            RED_LED_OFF();
        } else {
            RED_LED_ON();
            WHITE_LED_OFF();
        }
        __delay32(100 * (_XTAL_FREQ / 1000));

    }

    return (EXIT_SUCCESS);
}

