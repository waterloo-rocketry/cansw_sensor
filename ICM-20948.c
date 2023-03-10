#ifndef LSM303AGR_H
#define LSM303AGR_H

#include "mcc_generated_files/device_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "my2c.h"
#include "ICM-20948.h"   
#include "ICM-20948_regmap.h"

static uint8_t ICM_20948_addr;

// This driver assumes that I2C is already initialized
bool ICM_20948_init(uint8_t ICM_20948_addr_in) {
    ICM_20948_addr = ICM_20948_addr_in;
    // Select user bank 0
    MY2C_write1ByteRegister(ICM_20948_addr, REG_BANK_SEL, 0x00);
    // Reset device & set clock to 20 MHz interal oscillator
    MY2C_write1ByteRegister(ICM_20948_addr, PWR_MGMT_1, 0x80);
    // Enable accelerometer and gyroscope
    MY2C_write1ByteRegister(ICM_20948_addr, PWR_MGMT_2, 0x00);
    
    // Select user bank 2
    MY2C_write1ByteRegister(ICM_20948_addr, REG_BANK_SEL, 0x20);
    // Set gyroscope full scale to +/-2000dps, rate = 9000 Hz
    MY2C_write1ByteRegister(ICM_20948_addr, GYRO_CONFIG_1, 0x06);
    // Set accelerometer full scale to +/- 16g, rate = 4500 Hz
    MY2C_write1ByteRegister(ICM_20948_addr, ACCEL_CONFIG, 0x06);
    // Reset magnetometer & set to continuous measurement mode 
    MY2C_write1ByteRegister(ICM_20948_addr, CNTL3, 0x01);
    MY2C_write1ByteRegister(ICM_20948_addr, CNTL2, 0x02);
    
    return true;
}

bool ICM_20948_check_sanity(void) {
    uint8_t addr_sanity = MY2C_read1ByteRegister(ICM_20948_addr, WHO_AM_I);
    uint8_t mag_addr_sanity = MY2C_read1ByteRegister(ICM_20948_addr, WIA2);
    
    // Sanity fails if the "who am i" registers doesn't match
    if (addr_sanity != 0xEA || mag_addr_sanity != 0x09) {
        return false;
    }

    // checks pass
    return true;
}

bool ICM_20948_get_accel_raw(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }

    // Check if magnetometer data is ready, fail if it is not
    uint8_t mag_data_status_1 = MY2C_read1ByteRegister(ICM_20948_addr, ST1);
    
    if (mag_data_status_1 != 0x01 || mag_data_status_1!= 0x03) {
        TRISB3 = 0;     //set B3 as output, blue LED
        LATB3 = 0;      // turn blue LED on
        return false;
    }
    
    // Magnetometer measurement data
    uint8_t x_h = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_XOUT_H);
    uint8_t x_l = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_XOUT_L);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_YOUT_H);
    uint8_t y_l = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_YOUT_L);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_ZOUT_H);
    uint8_t z_l = MY2C_read1ByteRegister(ICM_20948_addr, ACCEL_ZOUT_L);
    *z = (int16_t)((uint16_t)z_h << 8 | z_l);

    // Must read ST2 register after measurement, see datasheet register 13.4 ST2
    uint8_t mag_status_2 = MY2C_read1ByteRegister(ICM_20948_addr, ST2);
    return true; 
}

bool ICM_20948_get_gyro_raw(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }
    
    uint8_t x_h = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_XOUT_H);
    uint8_t x_l = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_XOUT_L);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_YOUT_H);
    uint8_t y_l = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_YOUT_L);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_ZOUT_H);
    uint8_t z_l = MY2C_read1ByteRegister(ICM_20948_addr, GYRO_ZOUT_L);
    *z = (int16_t)((uint16_t)z_h << 8 | z_l);

    return true;
}

bool ICM_20948_get_mag_raw(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }
    
    uint8_t x_h = MY2C_read1ByteRegister(ICM_20948_addr, HXH);
    uint8_t x_l = MY2C_read1ByteRegister(ICM_20948_addr, HXL);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = MY2C_read1ByteRegister(ICM_20948_addr, HYH);
    uint8_t y_l = MY2C_read1ByteRegister(ICM_20948_addr, HYL);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = MY2C_read1ByteRegister(ICM_20948_addr, HZH);
    uint8_t z_l = MY2C_read1ByteRegister(ICM_20948_addr, HZL);
    *z = (int16_t)((uint16_t)z_h << 8 | z_l);

    return true;
}

bool ICM_20948_get_temp_raw(int16_t *temp) {
    uint8_t t_h = MY2C_read1ByteRegister(ICM_20948_addr, TEMP_OUT_H);
    uint8_t t_l = MY2C_read1ByteRegister(ICM_20948_addr, TEMP_OUT_L);
    *temp = (int16_t)((uint16_t)t_h << 8 | t_l);
}

bool ICM_20948_get_temp(int16_t *temp) {
    ICM_20948_get_temp_raw(temp);
    *temp /= 333.87;
    return true;
}

#endif