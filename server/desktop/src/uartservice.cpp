#include "uartservice.h"
#include <QSerialPort>
#include "setting.h"
#include <QDebug>
#include <mutex>

/**
 * @brief This function runs the UART service by configuring the serial port settings and writing data to it.
 *
 * @details This function sets the port name, baud rate, parity, data bits, stop bits, and flow control of the serial port.
 * It then enters a loop where it writes data to the serial port until the "end" flag is set. It locks the buffer with a mutex
 * before copying its contents to a temporary array, which is then written to the serial port. If the write operation is successful,
 * it waits for the bytes to be written and sets the status flag to true. If the write operation fails, it sets the status flag to false
 * and breaks out of the loop. If the bytes are not written within the specified interval, it sets the status flag to false and breaks
 * out of the loop. If the serial port fails to open, it prints an error message. If the serial port is open, it closes it before
 * restarting the loop.
 */
void UARTService::run()
{
    QSerialPort serial;

    // Configure the serial port settings
    serial.setPortName(Setting::UART_Connection::PORT);
    serial.setBaudRate(Setting::UART_Connection::BAUDRATE);
    serial.setParity(QSerialPort::NoParity);
    serial.setDataBits(QSerialPort::Data8);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    while (!end)
    {
        if (serial.open(QIODevice::WriteOnly))
        {
            while (!end && serial.isWritable())
            {
                uint8_t tmparr[sizeof(Buffer)]{0};

                {
                    std::scoped_lock<std::mutex> locker{mtx};
                    memcpy(tmparr, Buffer, sizeof(Buffer));
                }

                if (sizeof(tmparr) == serial.write(reinterpret_cast<char *>(tmparr), sizeof(tmparr)))
                {
                    if (serial.waitForBytesWritten(Setting::INTERVAL))
                    {
                        status = true;
                        msleep(Setting::INTERVAL / 2);
                    }
                    else
                    {
                        status = false;
                        break;
                    }
                }
                else
                {
                    status = false;
                    qDebug() << "UART read error. Connection may be lost.";
                    break;
                }
            }
        }
        else
        {
            qDebug() << "Failed to open the port";
        }

        if (serial.isOpen())
        {
            serial.close();
        }
    }
}