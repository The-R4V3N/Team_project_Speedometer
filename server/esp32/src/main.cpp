/**
 * @file main.cpp
 * @brief This file contains the main function that initializes the CAN module and configures the communication.
 *
 * It also contains the loop function that reads data from the serial port and sends it over the CAN bus.
 *
 */
#include <Arduino.h>
#include <CAN.h>
#include <CAN_config.h>
#include "setting.h"

CAN_device_t CAN_cfg;

void setup()
{
    CAN_init(); // initialize CAN Module

    // Config the communication
    CAN_cfg.tx_pin_id = GPIO_NUM_5;
    CAN_cfg.rx_pin_id = GPIO_NUM_35;
    CAN_cfg.speed = CAN_SPEED_500KBPS;

    Serial.begin(Setting::UART_Connection::BAUDRATE);
}

void loop()
{
    CAN_frame_t frame{0};

    frame.FIR.B.DLC = Setting::Signal::BUFSIZE;
    frame.FIR.B.RTR = CAN_no_RTR;
    frame.FIR.B.FF = CAN_frame_std;

    if (Setting::Signal::BUFSIZE == Serial.readBytes(frame.data.u8, Setting::Signal::BUFSIZE))
    {
        CAN_write_frame(&frame);
    }
}