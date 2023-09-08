/**
 * @brief This function runs the TCP service.
 *
 * It creates a socket and binds it to the specified IP address and port number.
 * It listens for incoming connections and accepts them.
 * It sends the buffer to the client until the 'end' flag is set.
 *
 * @return void
 */
#include "tcpservice.h"
#include "setting.h"
#include <arpa/inet.h>
#include <QDebug>
#include <ostream>

void TCPService::run(void)
{
    bool enable{0};

    sockaddr_in server_address{0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(Setting::tcp_connection::tcp_port::PORT);
    inet_pton(AF_INET, Setting::tcp_connection::tcp_ip::IP, &server_address.sin_addr);

    while (!end) // Continue until 'end' flag is set
    {
        do
        {
            socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (socket_fd == -1)
            {
                continue; // try again
            }
            else
            {
                enable = 1;
            }

            if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            {
                close(socket_fd);
                continue; // try again
            }

            if (0 != bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)))
            {
                close(socket_fd);
                continue; // try again :)
            }

            if (0 != listen(socket_fd, 1))
            {
                close(socket_fd);
                continue; // try again :)
            }
            else
            {
                break;
            }

        } while (!end);

        sockaddr_in cli{0};
        socklen_t len = sizeof(cli);

        int connfd = accept(socket_fd, (sockaddr *)&cli, &len);
        if (connfd < 0)
        {
            close(socket_fd); // Close the main server socket when we're done
            continue;         // Go back and eta another connection
        }

        while (!end) // Continue sending buffer until 'end' flag is set
        {
            if (sizeof(Buffer) != write(connfd, Buffer, sizeof(Buffer)))
            {
                qDebug() << "Connection lost ... reconnecting..";
                break;
            }

            // Delay, to not flood the client
            std::this_thread::sleep_for(std::chrono::milliseconds(Setting::INTERVAL / 2));
        }
        close(connfd);    // Close the client connection
        close(socket_fd); // Close the main server socket when we're done
    }
}
