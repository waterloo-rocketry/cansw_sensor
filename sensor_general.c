#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/device_config.h"
#include <math.h>

#include "sensor_general.h"

const float VREF = 3.3;

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

    float v = (voltage_raw + 0.5f) / 4096.0f * VREF;
    
    const double r = 99.8;
    const double pressure_range = 3000;

    double current = v / r;

    int32_t pressure_psi = (int32_t) ((current - 0.004) / (0.02 - 0.004) * pressure_range);
    //if (pressure_psi < 0) { pressure_psi = 0; }

    return (uint32_t) pressure_psi;
}


uint16_t get_temperature_c(void) {
    adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_THERM);

    const float rdiv = 10000.0; // 10kohm dividor resistor

    // beta, r0, t0 from https://media.digikey.com/pdf/Data%20Sheets/Thermometrics%20Global%20Business%20PDFs/TG_Series.pdf
    const float beta = 3434.0;
    const float r0 = 10000.0;
    const float t0 = 298.15;   // 25 C in Kelvin

    float v = (voltage_raw + 0.5f) / 4096.0f * VREF; // (raw + contiuity correction) / 12bit adc * vref
    float r = v * rdiv / (VREF - v);

    float invk = 1 / t0 + 1 / beta * log (r / r0);
  
    return (uint16_t) (1/invk);
}
