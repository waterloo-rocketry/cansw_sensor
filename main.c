#include <stdio.h>
#include <stdlib.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/pin_manager.h"

#include "sensor_general.h"
#include "timer.h"
#include <xc.h>

static void can_msg_handler(const can_msg_t *msg);
static void send_status_ok(void);

//memory pool for the CAN tx buffer
uint8_t tx_pool[100];

int main(int argc, char** argv) {
    // MCC generated initializer
    SYSTEM_Initialize();

    ADCC_DisableContinuousConversion();
    LED_init();

    // init our millisecond function
    timer0_init();

    // Enable global interrupts
    INTCON0bits.GIE = 1;

    // Set up CAN TX
    TRISC0 = 0;
    RC0PPS = 0x33;

    // Set up CAN RX
    TRISC1 = 1;
    ANSELC1 = 0;
    CANRXPPS = 0x11;

    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);

    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    // loop timer
    uint32_t last_millis = millis();

    while (1) {
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {

            // check for general board status
            // TODO
            bool status_ok = true;
            if (status_ok) { send_status_ok(); }

            // get pressure
            uint16_t pressure_psi = get_pressure_psi();
            can_msg_t sensor_msg;
            build_analog_data_msg(millis(), SENSOR_PRESSURE, pressure_psi, &sensor_msg);
            txb_enqueue(&sensor_msg);

            // visual heartbeat indicator
            LED_heartbeat();

            // update our loop counter
            last_millis = millis();
        }

        //send any queued CAN messages
        txb_heartbeat();
    }

    // unreachable
    return (EXIT_SUCCESS);
}

static void __interrupt() interrupt_handler() {
    if (PIR5) {
        can_handle_interrupt();
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

static void can_msg_handler(const can_msg_t *msg) {
    uint16_t msg_type = get_message_type(msg);

    // ignore messages that were sent from this board
    if (get_board_unique_id(msg) == BOARD_UNIQUE_ID) {
        return;
    }

    switch (msg_type) {
        case MSG_GENERAL_CMD:
            // nothing right now
            break;

        case MSG_LEDS_ON:
            LED_ON();
            break;

        case MSG_LEDS_OFF:
            LED_OFF();
            break;

        // all the other ones - do nothing
        case MSG_INJ_VALVE_CMD:
        case MSG_VENT_VALVE_CMD:
        case MSG_DEBUG_MSG:
        case MSG_DEBUG_PRINTF:
        case MSG_VENT_VALVE_STATUS:
        case MSG_INJ_VALVE_STATUS:
        case MSG_SENSOR_ACC:
        case MSG_SENSOR_GYRO:
        case MSG_SENSOR_MAG:
        case MSG_SENSOR_ANALOG:
        case MSG_GENERAL_BOARD_STATUS:
            break;

        // illegal message type - should never get here
        default:
            // send a message or something
            break;
    }
}

// Send a CAN message with nominal status
static void send_status_ok(void) {
    can_msg_t board_stat_msg;
    build_board_stat_msg(millis(), E_NOMINAL, NULL, 0, &board_stat_msg);

    // send it off at low priority
    txb_enqueue(&board_stat_msg);
}
