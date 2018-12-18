#include "spi.h"
#include "mcc_generated_files/mcc.h"
#include <libpic30.h>

void spi_write(uint8_t data) {
    __delay32(_XTAL_FREQ / 1000);
    while(SPI2STATbits.SPITBF) {}
    SPI2BUF = data;
    while(!SPI2STATbits.SPIRBF) {}
    
    // gotta read the buffer or it'll stay in memory forever
    uint8_t temp = SPI2BUF;
}

uint8_t spi_read(void) {
    __delay32(_XTAL_FREQ / 1000);
    while(SPI2STATbits.SPITBF) {};
    SPI2BUF = 0xFF;
    while(!SPI2STATbits.SPIRBF) {};
    uint8_t temp = SPI2BUF;
    // wait until SPIBEC is 0
    return temp;
}

void spi_init() {
    // enable spi module 2 as master mode
    SPI2CON1bits.DISSCK = 0; // enable sck
    SPI2CON1bits.DISSDO = 0; // enable SDO
    SPI2CON1bits.MODE16 = 0; // 8 bit things
    SPI2CON1bits.SMP    = 0; // sample at middle of data time
    SPI2CON1bits.CKE    = 0; // switch output on rising edge of SCK
    SPI2CON1bits.SSEN   = 0; // we are not in slave mode, leave CS GPIO
    SPI2CON1bits.CKP    = 1; // idle clock level high.
    SPI2CON1bits.MSTEN  = 1; // use master mode
    SPI2CON1bits.SPRE   = 0; // secondary prescale 8:1
    SPI2CON1bits.PPRE   = 0; // primary prescale 8:1
    SPI2CON2bits.FRMEN  = 0; // don't use framed mode
    SPI2CON2bits.SPIBEN = 0; // use standard mode, not enhanced mode

    // set SCK output to RP40, and input to RP32 (both must be set)
    RPOR3bits.RP40R = 0x09;
    RPINR22bits.SCK2R = 0x28;

    // set MOSI output to RP39 (RB7)
    RPOR2bits.RP39R = 0x08;

    // set MISO input to RP41 (RB9)
    RPINR22bits.SDI2R = 0x29;
    TRISBbits.TRISB6 = 1;

    // enable spi module 2
    SPI2STATbits.SPIEN = 1;
}

void chip_select_init() {
    // barometric pressure sensor
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    
    // IMU 1
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 1;
    
    // IMU 2
    TRISBbits.TRISB14 = 0;
    LATBbits.LATB14 = 1;
}

void imu1_spi_select() { LATBbits.LATB13 = 0; }
void imu1_spi_release() { LATBbits.LATB13 = 1; }

void imu2_spi_select() { LATBbits.LATB14 = 0; }
void imu2_spi_release(){ LATBbits.LATB14 = 1; }

void baro_spi_select() { LATBbits.LATB12 = 0; }
void baro_spi_release() { LATBbits.LATB12 = 1; }
