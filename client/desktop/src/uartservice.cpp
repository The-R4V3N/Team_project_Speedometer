/**
 * @file uartservice.cpp
 * @brief Implementation of the UARTService class.
 *
 * This file contains the implementation of the UARTService class, which is responsible for reading data from a serial port.
 *
 */

#include "uartservice.h"
#include "setting.h"
#include <QSerialPort>
#include <QDebug>

/**
 * @brief Runs the UARTService thread.
 *
 * This function sets up the serial port with the specified settings and continuously reads data from it until the 'end' flag is set.
 * The data is stored in a buffer and a mutex is used to ensure thread safety.
 *
 */
void UARTService::run(void)
{
    QSerialPort serial_port; /**<The serial port object.*/

    serial_port.setPortName(Setting::UART_Connection::PORT);     /**<Sets the serial prot which is defined in the shared setting.h file*/
    serial_port.setBaudRate(Setting::UART_Connection::BAUDRATE); /**<Sets the baud rate which is defined in the shared setting.h file*/
    serial_port.setParity(QSerialPort::NoParity);                /**<Sets the parity.*/
    serial_port.setDataBits(QSerialPort::Data8);                 /**<Sets the data bits.*/
    serial_port.setStopBits(QSerialPort::OneStop);               /**<Sets the stop bits.*/
    serial_port.setFlowControl(QSerialPort::NoFlowControl);      /**<Sets the flow control.*/

    while (!end) /**<run until the end flag is set*/
    {
        if (serial_port.open(QIODevice::ReadOnly)) /**<open the serial port*/
        {
            while (!end && serial_port.isReadable()) /**<read until the end flag is set or the serial port is not readable*/
            {
                serial_port.clear();               /**<clear the serial port*/
                uint8_t tmparr[sizeof(Buffer)]{0}; /**<create a temporary array to store the data*/

                if (serial_port.waitForReadyRead(Setting::INTERVAL)) /**<wait for data to be available*/
                {
                    if (sizeof(tmparr) == serial_port.read(reinterpret_cast<char *>(tmparr), sizeof(tmparr))) /**<read the data*/
                    {
                        status = true;                          /**<set the status flag to true*/
                        std::scoped_lock<std::mutex> lock(mtx); /**<lock the mutex*/
                        memcpy(Buffer, tmparr, sizeof(Buffer)); /**<copy the data to the buffer*/
                    }
                    else
                    {
                        qDebug() << "UART read error. Connection may be lost."; /**<print an error message*/
                        status = false;                                         /**<set the status flag to false*/
                        break;                                                  /**<break the loop*/
                    }
                }
                else
                {
                    qDebug() << "UART read timeout. Connection may be lost."; /**<print an error message*/
                    status = false;                                           /**<set the status flag to false*/
                    break;                                                    /**<break the loop*/
                }
            }
        }
        else
        {
            qDebug() << "Failed to open the port"; /**<print an error message*/
            status = false;                        /**<set the status flag to false*/
        }

        if (serial_port.isOpen()) /**<close the serial port*/
        {
            serial_port.close();
        }
    }
}
