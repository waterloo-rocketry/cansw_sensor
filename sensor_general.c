#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/device_config.h"

#include "sensor_general.h"

void LED_init(void) {
    TRISB4 = 0;     //set B4 as output
    LATB4 = 1;      // turn the led off
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
    adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_PRESSURE);
    return voltage_raw;

    // Resistor divider maps 0-5V output to 0-1.5V
    int voltage_5v = voltage_raw * 5 / 6;

    // Scaling factors taken from (for P1):
    // https://docs.google.com/spreadsheets/d/1NJDRvIkPtVGVRjQt-zyT8ZoKv0JL28MJ4FAHNd4Z_rc/edit#gid=0
    int32_t pressure_add = (40); // adjusted scaling values from june 12th
    double pressure_scale = (621.55265);

    int32_t pressure_psi = (int32_t) voltage_5v * pressure_scale / (1000) + pressure_add;
    if (pressure_psi < 0) { pressure_psi = 0; }

    return (uint32_t)pressure_psi;
}


uint16_t get_temperature_c(void) {
    adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_THERM);

    return voltage_raw;
}