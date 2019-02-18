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

unsigned short C1;
unsigned short C2;
unsigned short C3;
unsigned short C4;
unsigned short C5;
unsigned short C6;

static void led_init() {
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
    
    TRISBbits.TRISB4 = 0;
    LATBbits.LATB4 = 1;
    
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;
}

void barometric_pressure_init() {
    baro_spi_select();
    
    spi_write(RESET);
    
    spi_write(PROM_READ_C1);
    unsigned char C1_high_val = spi_read();
    unsigned char C1_low_val = spi_read();
    C1 = (unsigned short)C1_high_val << 8 | C1_low_val;
    
    spi_write(PROM_READ_C2);
    unsigned char C2_high_val = spi_read();
    unsigned char C2_low_val = spi_read();
    C2 = (unsigned short)C2_high_val << 8 | C2_low_val;
    
    spi_write(PROM_READ_C3);
    unsigned char C3_high_val = spi_read();
    unsigned char C3_low_val = spi_read();
    C3 = (unsigned short)C3_high_val << 8 | C3_low_val;
    
    spi_write(PROM_READ_C4);
    unsigned char C4_high_val = spi_read();
    unsigned char C4_low_val = spi_read();
    C4 = (unsigned short)C4_high_val << 8 | C4_low_val;
    
    spi_write(PROM_READ_C5);
    unsigned char C5_high_val = spi_read();
    unsigned char C5_low_val = spi_read();
    C5 = (unsigned short)C5_high_val << 8 | C5_low_val;
    
    spi_write(PROM_READ_C6);
    unsigned char C6_high_val = spi_read();
    unsigned char C6_low_val = spi_read();
    C6 = (unsigned short)C6_high_val << 8 | C6_low_val;
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

