#ifndef MPU_6050.h
#define MPU_6050.h

#define MPU_6050_ADDR 0b1101000

#include <stdint.h>
#include <stdbool.h>

// Set up gyro and acclerometer
bool MPU_6050_init(uint8_t MPU_6050_addr_in);

// Check if the device is alive. Fails if an I2C can't be established
// or if WHO_AM_I registers don't return default values.
bool MPU_6050_check_sanity(void);

bool MPU_6050_get_accel(int16_t *x, int16_t *y, int16_t *z);

bool MPU_6050_get_gyro(int16_t *x, int16_t *y, int16_t *z);

bool MPU_6050_get_temp_raw(int16_t *temp);

bool MPU_6050_get_temp(int16_t *temp);

#endif


