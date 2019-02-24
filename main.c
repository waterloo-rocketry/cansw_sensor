#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <math.h>
#include <stdint.h>

#include "Spi_command_header.h"
#include "mcc_generated_files/mcc.h"
#include "spi.h"

#define WHITE_LED_ON() (LATAbits.LATA0 = 0)
#define WHITE_LED_OFF() (LATAbits.LATA0 = 1)
#define BLUE_LED_ON() (LATBbits.LATB4 = 0)
#define BLUE_LED_OFF() (LATBbits.LATB4 = 1)    
#define RED_LED_ON() (LATBbits.LATB15 = 0)
#define RED_LED_OFF() (LATBbits.LATB15 = 1) 

uint16_t C1;
uint16_t C2;
uint16_t C3;
uint16_t C4;
uint16_t C5;
uint16_t C6;

static void led_init() {
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
    
    TRISBbits.TRISB4 = 0;
    LATBbits.LATB4 = 1;
    
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;
}

void barometric_pressure_init() {
    spi_write(RESET);
    
    spi_write(PROM_READ_C1);
    uint8_t C1_high_val = spi_read();
    uint8_t C1_low_val = spi_read();
    C1 = (uint16_t)C1_high_val << 8 | C1_low_val;
    
    spi_write(PROM_READ_C2);
    uint8_t C2_high_val = spi_read();
    uint8_t C2_low_val = spi_read();
    C2 = (uint16_t)C2_high_val << 8 | C2_low_val;
    
    spi_write(PROM_READ_C3);
    uint8_t C3_high_val = spi_read();
    uint8_t C3_low_val = spi_read();
    C3 = (uint16_t)C3_high_val << 8 | C3_low_val;
    
    spi_write(PROM_READ_C4);
    uint8_t C4_high_val = spi_read();
    uint8_t C4_low_val = spi_read();
    C4 = (uint16_t)C4_high_val << 8 | C4_low_val;
    
    spi_write(PROM_READ_C5);
    uint8_t C5_high_val = spi_read();
    uint8_t C5_low_val = spi_read();
    C5 = (uint16_t)C5_high_val << 8 | C5_low_val;
    
    spi_write(PROM_READ_C6);
    uint8_t C6_high_val = spi_read();
    uint8_t C6_low_val = spi_read();
    C6 = (uint16_t)C6_high_val << 8 | C6_low_val;
}

int main(int argc, char** argv) {
    SYSTEM_Initialize();
    CLOCK_Initialize();
    
    led_init();
    spi_init();
    chip_select_init();
    
    baro_spi_select();
    
    barometric_pressure_init();
    
    spi_write(CONVERT_D1_OSR1024);
    spi_write(ADC_READ);
    
    uint8_t D1_high_val = spi_read();
    uint8_t D1_mid_val = spi_read();
    uint8_t D1_low_val = spi_read();
    uint32_t D1 = (uint32_t)D1_high_val << 16 | D1_mid_val << 8 | D1_low_val;
    
    spi_write(CONVERT_D2_OSR1024);
    spi_write(ADC_READ);
    
    uint8_t D2_high_val = spi_read();
    uint8_t D2_mid_val = spi_read();
    uint8_t D2_low_val = spi_read();
    uint32_t D2 = (uint32_t)D2_high_val << 16 | D2_mid_val << 8 | D2_low_val;
    
    int32_t dT = D2 - C5 * pow(2,8);
    int32_t TEMP = 2000 + dT * C6 / pow(2,23);
    
    printf("%d", TEMP);
    
    int64_t OFF = C2 * pow(2,16) + (C4 * dT) / pow(2,7);
    int64_t SENS = C1 * pow(2,15) + (C3 * dT ) / pow(2,8);
    int32_t P = (D1 * SENS / pow(2,21) - OFF) / pow(2,15);
    
    printf("%d", TEMP);
    
    baro_spi_release();
    
    /*__delay32(100 * (_XTAL_FREQ / 1000));
    
    while (1) {
        WHITE_LED_ON();
        RED_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

        RED_LED_ON();
        WHITE_LED_OFF();
        __delay32(100 * (_XTAL_FREQ / 1000));

    }*/
    
    return (EXIT_SUCCESS);
}
