#ifndef TCPSERVICE_H
#define TCPSERVICE_H
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
    std::atomic<bool> end{false}; /**< Atomic flag to indicate when the service should stop.*/

    /**
     * @brief Defines a thread that runs the "run" function upon creation of a TCPService object.
     */
    std::thread thrd{&TCPService::run, this};

    /**
     * @brief Declaration of the overriden "run" function which is expected to provide the main functionality.
     */
    void run(void) override;

public:
    /**
     * @brief Constructor declaration.
     */
    TCPService() = default;

    /**
     *@brief Destructor declaration.
     * It ensures that when a TCPService object is destroyed,
     * The socket is shutdown and closed, and the associated thread is joined.
     */
    ~TCPService()
    {
        end = true;
        shutdown(socket_fd, SHUT_RDWR);
        close(socket_fd);
        thrd.join();
    }
};
#endif
