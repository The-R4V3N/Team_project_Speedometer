#include "tcpservice.h"
#include "setting.h"
#include "canvas.h"
#include <arpa/inet.h>
#include <QDebug>

/**
 * @brief This function runs the TCP service and connects to the server.
 *
 * @details It creates a socket and connects to the server using the IP address and port number specified in the Setting namespace.
 * It then receives data from the server and stores it in the Buffer array until the end flag is set to true.
 *
 * @note This function is a member function of the TCPService class.
 *
 * @param None.
 *
 * @return None.
 */
void TCPService::run(void)
{
    sockaddr_in server_address{0}; /**<The server address.*/

    server_address.sin_family = AF_INET;                                               /**<Sets the address family.*/
    server_address.sin_port = htons(Setting::tcp_connection::tcp_port::PORT);          /**<Sets the port number which is defined in the shared setting.h file.*/
    inet_pton(AF_INET, Setting::tcp_connection::tcp_ip::IP, &server_address.sin_addr); /**<Sets the IP address which is defined in the shared setting.h file.*/

    while (!end) /**<run until the end flag is set*/
    {

        do // try to connect
        {
            socket_fd = socket(AF_INET, SOCK_STREAM, 0); // create socket
            if (socket_fd == -1)                         // check if socket was created
            {
                continue; /**<Try again*/
            }
            if (0 == ::connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) /**<Try to connect*/
            {
                status = true; /**<set the status flag to true*/
            }
            else
            {
                status = false;   /**<set the status flag to false*/
                close(socket_fd); // close socket
                continue;         /**<Try again*/
            }
        } while (!status && !end); /**<run until the status flag is true or the end flag is set*/

        while (!end) /**<run until the end flag is set*/
        {
            uint8_t tmparr[sizeof(Buffer)]{0}; /**<create a temporary array to store the data*/

            if (sizeof(Buffer) == read(socket_fd, tmparr, sizeof(Buffer))) /**<read the data*/
            {
                std::scoped_lock<std::mutex> lock(mtx); /**<lock the mutex*/
                memcpy(Buffer, tmparr, sizeof(Buffer)); /**<copy the data to the buffer*/
            }
            else
            {
                close(socket_fd); /**<close the socket*/
                status = false;   /**<set the status flag to false*/
                break;            /**<break the loop*/
            }
        }
    }
}
