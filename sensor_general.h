#ifndef SENSOR_GEN_H
#define	SENSOR_GEN_H

// Contains miscellaneous sensor board-specific code

#define MAX_LOOP_TIME_DIFF_ms 250

#define LED_ON() (LATB4 = 0)
#define LED_OFF() (LATB4 = 1)

void LED_init(void);

#endif	/* SENSOR_GEN_H */

