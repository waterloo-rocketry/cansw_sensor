#ifndef LSM303AGR_H
#define LSM303AGR_H

#define LSM303_ACCEL_ADDR 0x19
#define LSM303_MAG_ADDR 0x1E

#include <stdint.h>
#include <stdbool.h>

// Set up magnetometer and acclerometer
// Current config: mag at 50Hz, accel at 50Hz and +/- 8g full scale
bool lsm303_init(uint8_t accel_addr_in, uint8_t mag_addr_in);

// Check if the device is alive. Fails if an I2C can't be established
// or if WHO_AM_I registers don't return default values.
bool lsm303_check_sanity(void);

// Get raw (unconverted from ADC bits) acceleration value.
// Returns false if I2C connection fails.
bool lsm303_get_accel_raw(int16_t *x, int16_t *y, int16_t *z);

// Get raw (unconverted from ADC bits) magnetometer value
// Returns false if I2C connection fails.
bool lsm303_get_mag_raw(int16_t *x, int16_t *y, int16_t *z);

#endif
