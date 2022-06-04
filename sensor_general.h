#ifndef SENSOR_GEN_H
#define	SENSOR_GEN_H

#include <stdint.h>

// Contains miscellaneous sensor board-specific code

#define MAX_LOOP_TIME_DIFF_ms 600
#define MAX_LOOP_SENSOR_TIME_DIFF_ms 200

#define LED_ON() (LATB4 = 0)
#define LED_OFF() (LATB4 = 1)

// Initialize LEDS
void LED_init(void);

// Blink the LED on or off each time it's called. Can be used to provide a visual
// heartbeat for the board.
void LED_heartbeat(void);

// Read pressure sensor ADC and convert to PSI. Replace all negative values with
// zero since canlib and RLCS don't like it.
uint32_t get_pressure_psi(void);
uint16_t get_temperature_c(void);

#endif	/* SENSOR_GEN_H */

