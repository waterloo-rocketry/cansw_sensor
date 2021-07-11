#ifndef LSM303AGR_H
#define LSM303AGR_H

#define LSM303_ACCEL_ADDR 

#include "mcc_generated_files/i2c1.h"

#include <stdint.h>
#include <stdbool.h>
#include "lsm303agr.h"
#include "lsm303agr_regmap.h"

static uint8_t accel_addr;
static uint8_t mag_addr;

// This driver assumes that I2C is already initialized
bool lsm303_init(uint8_t accel_addr_in, uint8_t mag_addr_in) {
    accel_addr = accel_addr_in;
    mag_addr = mag_addr_in;

    // set ODR for magnetometer to 50Hz
    // See Table 93 in datasheet
    i2c1_write1ByteRegister(mag_addr, CFG_REG_A_M, 0x8);

    // set Block Data Update mode
    i2c1_write1ByteRegister(mag_addr, CFG_REG_C_M, 0x10);

    // Set ODR for accelerometer to 50Hz
    // Enable measurement along x, y, z axes
    i2c1_write1ByteRegister(accel_addr, CTRL_REG1_A, 0x47);

    // Set Block Data Update mode
    // Set full scale range to +/- 8g
    // Set normal mode (not low power or high res)
    i2c1_write1ByteRegister(accel_addr, CTRL_REG4_A, 0xA0);

    i2c1_error error = i2c1_getLastError();
    return error == I2C1_GOOD;
}

bool lsm303_check_sanity(void) {
    uint8_t accel_sanity = i2c1_read1ByteRegister(accel_addr, WHO_AM_I_A);
    uint8_t mag_sanity = i2c1_read1ByteRegister(accel_addr, WHO_AM_I_M);

    // Sanity fails if we can't connect to the sensor
    if (i2c1_getLastError() != I2C1_GOOD) {
        return false;
    }

    // Sanity fails if the "who am i" registers don't match
    if (accel_sanity != 0x33 || mag_sanity != 0x40) {
        return false;
    }

    // checks pass
    return true;
}

bool lsm303_get_accel_raw(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }

    uint8_t x_h = i2c1_read1ByteRegister(accel_addr, OUT_X_H_A);
    uint8_t x_l = i2c1_read1ByteRegister(accel_addr, OUT_X_L_A);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = i2c1_read1ByteRegister(accel_addr, OUT_Y_H_A);
    uint8_t y_l = i2c1_read1ByteRegister(accel_addr, OUT_Y_L_A);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = i2c1_read1ByteRegister(accel_addr, OUT_Z_H_A);
    uint8_t z_l = i2c1_read1ByteRegister(accel_addr, OUT_Z_L_A);
    *x = (int16_t)((uint16_t)z_h << 8 | z_l);

    i2c1_error error = i2c1_getLastError();
    return error == I2C1_GOOD;
}

bool lsm303_get_mag_raw(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }
    
    uint8_t x_h = i2c1_read1ByteRegister(mag_addr, OUTX_H_REG_M);
    uint8_t x_l = i2c1_read1ByteRegister(mag_addr, OUTX_L_REG_M);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = i2c1_read1ByteRegister(mag_addr, OUTY_H_REG_M);
    uint8_t y_l = i2c1_read1ByteRegister(mag_addr, OUTY_L_REG_M);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = i2c1_read1ByteRegister(mag_addr, OUTZ_H_REG_M);
    uint8_t z_l = i2c1_read1ByteRegister(mag_addr, OUTZ_L_REG_M);
    *x = (int16_t)((uint16_t)z_h << 8 | z_l);

    i2c1_error error = i2c1_getLastError();
    return error == I2C1_GOOD;
}

bool lsm303_get_mag_conv(int16_t *x, int16_t *y, int16_t *z);

#endif
