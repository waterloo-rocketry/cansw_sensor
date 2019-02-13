#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <math.h>

#include "Spi_command_header.h"
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

void barometric_pressure_init() {
    RESET;
    PROM_READ_C1;
    PROM_READ_C2;
    PROM_READ_C3;
    PROM_READ_C4;
    PROM_READ_C5;
    PROM_READ_C6;
}

int main(int argc, char** argv) {
    SYSTEM_Initialize();
    CLOCK_Initialize();
    
    led_init();
    spi_init();
    chip_select_init();
    
    barometric_pressure_init();
    
    /*__delay32(100 * (_XTAL_FREQ / 1000));
    
    while (1) {
        WHITE_LED_ON();
        RED_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

        RED_LED_ON();
        WHITE_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

    }*/
    
    CONVERT_D1_OSR1024;
    CONVERT_D2_OSR1024;
    
    signed int dT = CONVERT_D2_OSR1024 - PROM_READ_C5 * pow(2,8);
    signed int TEMP = 2000 + dT * PROM_READ_C6 / pow(2,23);
    ADC_READ;
    
    long signed int OFF = PROM_READ_C2 * pow(2,16) + (PROM_READ_C4 * dT) / pow(2,7);
    long signed int SENS = PROM_READ_C1 * pow(2,15) + (PROM_READ_C3 * dT ) / pow(2,8);
    signed int P = (CONVERT_D1_OSR1024 * SENS / pow(2,21) - OFF) / pow(2,15);
    ADC_READ;
    
    return (EXIT_SUCCESS);
}

