#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include <QDebug>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "comservice.h"
#include <sys/socket.h>
#include <thread>

/**
 * @brief The TCPService class is a COMService that communicates with the vehicle via TCP.
 */
class TCPService : public COMService /**<Declares a new class named "TCPService" that inherits from "COMService".*/
{
private:
    int socket_fd;                /**<File descriptor for the TCP socket.*/
    std::atomic<bool> end{false}; /**<Atomic flag to indicate when the service should stop.*/

    /**<Defines a thread that runs the "run" function upon creation of a TCPService object.*/
    std::thread thrd{&TCPService::run, this};

    /**<Declaration of the overriden "run" function which is expected to provide the main functionality.*/
    void run(void) override;

public:
    /**<Default constructor declaration.*/
    TCPService() = default;

    /**<Destructor declaration.
        It ensures that when a TCPService object is destroyed,
        the socket is shutdown and closed, and the associated thread is joined.
    */
    ~TCPService()
    {
        end = true;                     /**<Set the "end" flag to true to indicate the service should stop.*/
        shutdown(socket_fd, SHUT_RDWR); /**<Shutdown both reading and writing on the socket.*/
        close(socket_fd);               /**<Close the socket.*/
        thrd.join();                    /**<Wait for the associated thread to finish.*/
    }
};

#endif // TCPSERVICE_H
