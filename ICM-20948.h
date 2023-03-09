#ifndef ICM_20948_H
#define	ICM_20948_H

#define ICM_20948_ADDR 0x69

#include <stint.h>
#include <stdbool.h>

// Set up gyroscope, accelerometer, and magnetometer
bool ICM_20948_init(uint8_t ICM_20948_addr_in);

// Check if the device is alive. Fails if an I2C can't be established
// or if WHO_AM_I registers don't return default values.

bool ICM_20948_check_sanity(void);

bool ICM_20948_get_accel_raw(int16_t *x, int16_t *y, int16_t *z);

bool ICM_20948_get_gyro_raw(int16_t *x, int16_t *y, int16_t *z);

bool ICM_20948_get_temp_raw(int16_t *temp);

bool ICM_20948_get_temp(int16_t *temp);  

#endif	/* ICM_20948_H */
