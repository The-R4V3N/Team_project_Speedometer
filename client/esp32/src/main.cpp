#include <Arduino.h>
#include <CAN.h>
#include <CAN_config.h>
#include "setting.h"

CAN_device_t CAN_cfg; /**<CAN config*/

void setup()
{
    Serial.begin(Setting::UART_Connection::BAUDRATE); /**<Start the serial communication*/

    // Config the communication
    CAN_cfg.tx_pin_id = GPIO_NUM_5;                          /**<CAN TX pin*/
    CAN_cfg.rx_pin_id = GPIO_NUM_35;                         /**<CAN RX pin*/
    CAN_cfg.speed = CAN_SPEED_500KBPS;                       /**<CAN speed*/
    CAN_cfg.rx_queue = xQueueCreate(1, sizeof(CAN_frame_t)); /**<CAN queue*/

    CAN_init(); /**<initialize CAN Module*/
}

void loop()
{
    CAN_frame_t frame{0}; /**<CAN frame*/

    frame.FIR.B.RTR = CAN_no_RTR;               /**<Set the RTR bit to 0*/
    frame.FIR.B.FF = CAN_frame_std;             /**<Set the FF bit to 0*/
    frame.FIR.B.DLC = Setting::Signal::BUFSIZE; /**<Set the DLC to the buffer size*/

    if (pdTRUE == xQueueReceive(CAN_cfg.rx_queue, &frame, portMAX_DELAY)) /**<Receive the data from the CAN bus*/
    {
        Serial.write(frame.data.u8, Setting::Signal::BUFSIZE); /**<Send the data to the serial port*/
    }
}
