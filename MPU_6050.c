#ifndef LSM303AGR_H
#define LSM303AGR_H

#define LSM303_ACCEL_ADDR 

#include "mcc_generated_files/device_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "my2c.h"
#include "MPU_6050.h"   
#include "MPU_6050_regmap.h"

static uint8_t MPU_6050_addr;

// This driver assumes that I2C is already initialized
bool MPU_6050_init(uint8_t MPU_6050_addr_in) {
    MPU_6050_addr = MPU_6050_addr_in;
    
    //Set to use internal clock and reset device
    MY2C_write1ByteRegister(MPU_6050_addr, PWR_MGMT_1,  0x80);
    MY2C_write1ByteRegister(MPU_6050_addr, 0x68, 0b00000111);
    MY2C_write1ByteRegister(MPU_6050_addr, 0x6B, 0x00);
    
    //Set to +-2000 deg / s
    MY2C_write1ByteRegister(MPU_6050_addr, GYRO_CONFIG, 0x18);
    
    //Set to +- 16g / s
    MY2C_write1ByteRegister(MPU_6050_addr, ACCEL_CONFIG, 0x18);

    return true;
}

bool MPU_6050_check_sanity(void) {
    uint8_t MPU_6050_sanity = MY2C_read1ByteRegister(MPU_6050_addr, MPU_6050_WHO_AM_I);
    // Sanity fails if the "who am i" registers don't match
    if (MPU_6050_sanity != 0x68) {
        return false;
    }

    // checks pass
    return true;
}

bool MPU_6050_get_accel(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }

    uint8_t x_h = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_XOUT_H);
    uint8_t x_l = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_XOUT_L);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_YOUT_H);
    uint8_t y_l = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_YOUT_L);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_ZOUT_H);
    uint8_t z_l = MY2C_read1ByteRegister(MPU_6050_addr, ACCEL_ZOUT_L);
    *z = (int16_t)((uint16_t)z_h << 8 | z_l);

    return true;
}

bool MPU_6050_get_gyro(int16_t *x, int16_t *y, int16_t *z) {
    if (!x || !y || !z) { return false; }
    
    uint8_t x_h = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_XOUT_H);
    uint8_t x_l = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_XOUT_L);
    *x = (int16_t)((uint16_t)x_h << 8 | x_l);

    uint8_t y_h = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_YOUT_H);
    uint8_t y_l = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_YOUT_L);
    *y = (int16_t)((uint16_t)y_h << 8 | y_l);

    uint8_t z_h = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_ZOUT_H);
    uint8_t z_l = MY2C_read1ByteRegister(MPU_6050_addr, GYRO_ZOUT_L);
    *z = (int16_t)((uint16_t)z_h << 8 | z_l);

    return true;
}

bool MPU_6050_get_temp_raw(int16_t *temp) {
    uint8_t t_h = MY2C_read1ByteRegister(MPU_6050_addr, TEMP_OUT_H);
    uint8_t t_l = MY2C_read1ByteRegister(MPU_6050_addr, TEMP_OUT_L);
    *temp = (int16_t)((uint16_t)t_h << 8 | t_l);
}

bool MPU_6050_get_temp(int16_t *temp) {
    MPU_6050_get_temp_raw(temp);
    *temp /= 340;
    *temp += 36.53;
    return true;
}

#endif
