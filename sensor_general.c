#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/device_config.h"
#include <math.h>

#include "sensor_general.h"

#define USE_4_20_MA_SENSOR 1
#define PT_OFFSET 0

const float VREF = 3.3;

void LED_init(void) {
    TRISB4 = 0;     //set B4, B3, B2 as output
    TRISB3 = 0;
    TRISB2 = 0;
    LATB4 = 1;      // turn the leds off
    LATB3 = 1;
    LATB2 = 1;
}

// Green LED
void LED_heartbeat_G(void) {
    static bool led_on = false;
    if (led_on) {
        LED_OFF_G();
        led_on = false;
    } else {
        LED_ON_G();
        led_on = true;
    }
}

// Blue LED
void LED_heartbeat_B(void) {
    static bool led_on = false;
    if (led_on) {
        LED_OFF_B();
        led_on = false;
    } else {
        LED_ON_B();
        led_on = true;
    }
}

// White LED
void LED_heartbeat_W(void) {
    static bool led_on = false;
    if (led_on) {
        LED_OFF_W();
        led_on = false;
    } else {
        LED_ON_W();
        led_on = true;
    }
}

 uint32_t get_pressure_psi(void) {
     adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_SENSOR_1);

     float v = (voltage_raw + 0.5f) / 4096.0f * VREF;
    
#if USE_4_20_MA_SENSOR
    
    const double r = 100;
    const double pressure_range = 3000;

    double current = v / r;

    int32_t pressure_psi = (int32_t) (((current - 0.004) / (0.02 - 0.004)) * pressure_range);
#else
    int32_t pressure_psi = (int32_t) (v * 39.2f*3.0f - 39.2f);
#endif

    return (uint32_t) pressure_psi + PT_OFFSET;

 }

uint16_t get_temperature_c(void) {
    adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_SENSOR_4);
    const float rdiv = 10000.0; // 10kohm dividor resistor

    // beta, r0, t0 from https://media.digikey.com/pdf/Data%20Sheets/Thermometrics%20Global%20Business%20PDFs/TG_Series.pdf
    const float beta = 3434.0;
    const float r0 = 10000.0;
    const float t0 = 298.15;   // 25 C in Kelvin

    float v = (voltage_raw + 0.5f) / 4096.0f * VREF; // (raw + contiuity correction) / 12bit adc * vref
    float r = v * rdiv / (VREF - v);

    float invk = 1 / t0 + 1 / beta * log (r / r0);
  
    return (uint16_t) (1/invk - 273);
}
