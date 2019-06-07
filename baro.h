#ifndef BARO_H
#define BARO_H

#include <stdint.h>
#include <stdbool.h>

#define BARO_ADDR 0b1110110
#define BARO_LATENCY_MS 5
#define BARO_RESOLUTION_MBAR 0.036f

bool baro_init(uint8_t i2c_addr);

bool baro_start_conversion(void);

// Starts a new ADC conversion, waits for it to complete, and
// computes pressure and temperature from the results.
bool baro_read(int32_t *temperature, int32_t *pressure);

// Returns whatever is in the ADC at this time and converts it
// to pressure and temperature .Does not start a new ADC conversion.
bool baro_read_async(int32_t *temperature, int32_t *pressure);

#endif