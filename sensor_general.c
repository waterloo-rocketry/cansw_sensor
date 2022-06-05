#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/device_config.h"
#include <math.h>

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
    return voltage_raw; // For debugging purposes only

    
    // Resistor divider maps 0-5V output to 0-1.5V
    int voltage_5v = voltage_raw * 5 / 6;

    // No longer valid: 
    // Scaling factors taken from (for P1):
    // https://docs.google.com/spreadsheets/d/1NJDRvIkPtVGVRjQt-zyT8ZoKv0JL28MJ4FAHNd4Z_rc/edit#gid=0
    // Now, it's a 4-20 mA sensor going through a 100 ohm resistor. This is for 0-3000psi
    // TF 0.4-2V now.
    
    int32_t pressure_add = (0); 
    const double voltage_range = 1.6;
    const double pressure_scale = (3000)/(voltage_range);
    const double minimum_voltage = 0.4;
    
    double voltage_adj = voltage_raw - minimum_voltage;

    int32_t pressure_psi = (int32_t) (voltage_adj * pressure_scale + pressure_add);
    //if (pressure_psi < 0) { pressure_psi = 0; }

    return (uint32_t)pressure_psi;
}


uint16_t get_temperature_c(void) {
    adc_result_t voltage_raw = ADCC_GetSingleConversion(channel_THERM);

    const float beta = 3434.0;
    const float invBeta = 1.0 / beta;
    const float adcMax = 4096.0;
    const float invT0 = 1.0 / 298.15; // room temp in Kelvin
    float K, C;
    K = 1.0 / (invT0 + invBeta*(log(adcMax / (float) voltage_raw - 1.0)));
    C = K - 273.15; // convert to Celsius
  
    return (uint16_t) C;
}