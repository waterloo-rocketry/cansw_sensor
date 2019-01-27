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
    spi_init();
    chip_select_init();
    
    __delay32(100 * (_XTAL_FREQ / 1000));
    
    while (1) {
        WHITE_LED_ON();
        RED_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

        RED_LED_ON();
        WHITE_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

    }

    return (EXIT_SUCCESS);
}

