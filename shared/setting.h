/**
 * @file setting.h
 * @brief This file contains the declaration of the Setting namespace which contains constants for server and client window sizes, signal values, and buffer size.
 */
#ifndef SETTING_H
#define SETTING_H

namespace Setting
{
    namespace Server
    {
        namespace Window
        {
            constexpr int Width{800}; /**<The width of the server window*/

            constexpr int Height{200}; /**<The height of the server window*/

        }
    }
    namespace Client
    {
        namespace Windows
        {
            constexpr int Width{800};  /**<The width of the client window*/
            constexpr int Height{560}; /**<The height of the client window*/
        }
    }

    constexpr int INTERVAL{50}; /**<The interval of the timer in milliseconds*/

    namespace Signal
    {
        namespace Speed
        {
            constexpr int MIN{0};    /**<The minimum speed value*/
            constexpr int MAX{240};  /**<The maximum speed value*/
            constexpr int START{0};  /**<The start bit of the speed signal*/
            constexpr int LENGTH{8}; /**<The length of the speed signal*/

            namespace Temperature
            {
                constexpr int MIN{-60};  /**<The minimum temperature value*/
                constexpr int MAX{60};   /**<The maximum temperature value*/
                constexpr int START{8};  /**<The start bit of the temperature signal*/
                constexpr int LENGTH{7}; /**<The length of the temperature signal*/
            }
            namespace BatteryLevel
            {
                constexpr int MIN{0};    /**<The minimum battery level value*/
                constexpr int MAX{100};  /**<The maximum battery level value*/
                constexpr int START{15}; /**<The start bit of the battery level signal*/
                constexpr int LENGTH{7}; /**<The length of the battery level signal*/
            }
            namespace Light
            {
                namespace Left
                {
                    constexpr int MIN{0};    /**<The minimum light value*/
                    constexpr int MAX{1};    /**<The maximum light value*/
                    constexpr int START{22}; /**<The start bit of the light signal*/
                    constexpr int LENGTH{1}; /**<The length of the light signal*/
                }
                namespace Right
                {
                    constexpr int MIN{0};    /**<The minimum light value*/
                    constexpr int MAX{1};    /**<The maximum light value*/
                    constexpr int START{23}; /**<The start bit of the light signal*/
                    constexpr int LENGTH{1}; /**<The length of the light signal*/
                }

            }

            constexpr int BUFSIZE{3};  /**<The size of the buffer*/
            constexpr int BYTE_LEN{8}; /**<The length of a byte*/
        }

#ifdef UARTCOM
        namespace UART_Connection
        {
            constexpr int BAUDRATE{115200};         /**<The baudrate of the UART connection*/
            constexpr char PORT[] = "/dev/ttyUSB0"; /**<The port of the UART connection*/
        }
#else
        namespace tcp_connection
        {
            namespace tcp_port
            {
                constexpr int PORT{15045}; /**<The port of the TCP connection*/
            }
            namespace tcp_ip
            {
                constexpr char IP[] = "127.0.0.1"; /**<The IP of the TCP connection*/
            }
        }
#endif // UARTCOM
    }
#endif // SETTING_H
}