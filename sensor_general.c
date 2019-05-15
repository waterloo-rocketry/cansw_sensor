#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "sensor_general.h"

void LED_init(void) {
    TRISC5 = 0;     //set B4 as output
    LATC5 = 1;      // turn the led off
}

void LED_heartbeat(void) {
    static bool led_on = false;
    if (led_on) {
        LED_OFF();
        led_on = false;
    } else {
        LED_ON();
        led_on = true;
    }
}

uint32_t get_pressure_psi(void) {
    adc_result_t pressure_raw = ADCC_GetSingleConversion(channel_PRESSURE);

    int pressure_add = 0;
    int pressure_scale = 1;
    
    int pressure_psi = pressure_raw * pressure_scale + pressure_add;
    if (pressure_psi < 0) { pressure_psi = 0; }
    
    return (uint32_t)pressure_psi;
}