/**
 * @file uartservice.h
 * @brief Header file for the UARTService class, which inherits from COMService and QThread.
 *
 * This class provides a UART service for communication between devices. It overrides the run() function
 * from QThread to start the service in a separate thread. The service can be stopped by setting the end flag
 * to true and waiting for the thread to finish.
 *
 * @see COMService
 * @see QThread
 */
#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#include <QThread>
#include "comservice.h"

class UARTService : public COMService, public QThread
{
private:
    std::atomic<bool> end{false}; /**<Atomic flag to indicate when the service should stop.*/

    void run() override; /**<Override the run() function from QThread to provide the main functionality.*/

public:
    /**>Constructor declaration.*/
    UARTService()
    {
        start();
    }
    /**<Destructor declaration.
        It ensures that when a UARTService object is destroyed, the associated thread is joined.
    */
    virtual ~UARTService()
    {
        end = true;
        wait();
    }
};

#endif // UARTSERVICE_H
