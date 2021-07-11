#include <xc.h>
#include <stdbool.h>

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/i2c1.h"
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

void test_digital_sensors(void) {
    uint8_t baro_addr = 0b1110110;        // barometer (U10)
    uint8_t imu_accel_addr = 0b0011001;   // accelerometer in IC U7
    uint8_t imu_mag_addr = 0b0011110;     // magnetometer in IC U7
    uint8_t gyro_addr = 0b1101011;

    // Uncomment the sensor you want to test
    uint8_t sensor_addr = baro_addr;
    // uint8_t sensor_addr = imu_accel_addr;
    // uint8_t sensor_addr = imu_mag_addr;
    // uint8_t sensor_addr = gyro_addr;

    // read from a random register and check the error
    i2c1_read1ByteRegister(sensor_addr, 0x20);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT) {

        // No response from the sensor, turn the LED on in sadness
        LED_ON();
        while (1);
    } else {

        // The sensor responded, blink an LED in victory!
        while (1) {
            LED_heartbeat();
            __delay_ms(200);
        }
    }
}
