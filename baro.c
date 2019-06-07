#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/device_config.h"
#include <xc.h>

#include "baro.h"

// i2c commands
#define BARO_RESET    0x1E    // perform reset
#define ADC_READ 0x00    // initiate read sequence
#define ADC_CONV 0x40    // start conversion
#define ADC_D1   0x00    // read ADC 1
#define ADC_D2   0x10    // read ADC 2
#define ADC_256  0x00    // set ADC oversampling ratio to 256
#define ADC_512  0x02    // set ADC oversampling ratio to 512
#define ADC_1024 0x04    // set ADC oversampling ratio to 1024
#define ADC_2048 0x06    // set ADC oversampling ratio to 2048
#define ADC_4096 0x08    // set ADC oversampling ratio to 4096

// PROM addresses
#define PROM_INFO  0xA0    // read factory info
#define PROM_C1    0xA2    // read correction factor 1
#define PROM_C2    0xA4    // read correction factor 2
#define PROM_C3    0xA6    // read correction factor 3
#define PROM_C4    0xA8    // read correction factor 4
#define PROM_C5    0xAA    // read correction factor 5
#define PROM_C6    0xAC    // read correction factor 6
#define PROM_CRC   0xAE    // read CRC (unused)

static uint8_t sensor_addr = 0x0;

// Correction factors
static uint16_t c1;
static uint16_t c2;
static uint16_t c3;
static uint16_t c4;
static uint16_t c5;
static uint16_t c6;

bool baro_init(uint8_t i2c_addr) {
    sensor_addr = i2c_addr;

    i2c1_writeCmd(sensor_addr, BARO_RESET);
    __delay_ms(100);

    // get correction factors from PROM
    c1 = i2c1_read2ByteRegister(sensor_addr, PROM_C1);
    c2 = i2c1_read2ByteRegister(sensor_addr, PROM_C2);
    c3 = i2c1_read2ByteRegister(sensor_addr, PROM_C3);
    c4 = i2c1_read2ByteRegister(sensor_addr, PROM_C4);
    c5 = i2c1_read2ByteRegister(sensor_addr, PROM_C5);
    c6 = i2c1_read2ByteRegister(sensor_addr, PROM_C6);

    i2c1_error error = i2c1_getLastError();
    return error == I2C1_GOOD;
}

bool baro_start_conversion(void) {
    i2c1_writeCmd(sensor_addr, ADC_2048);
    i2c1_writeCmd(sensor_addr, ADC_CONV);
    i2c1_error error = i2c1_getLastError();
    return error == I2C1_GOOD;
}

bool baro_read(int32_t *temperature, int32_t *pressure) {
    return true;
}

bool baro_read_async(int32_t *temperature, int32_t *pressure) {
    return true;
}
