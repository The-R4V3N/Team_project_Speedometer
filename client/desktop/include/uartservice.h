#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#include "comservice.h"
#include <QThread>

/**
 * @brief The UARTService class is a subclass of COMService that provides UART communication functionality.
 */
class UARTService : public COMService, public QThread
{
    std::atomic<bool> end{false}; /**< Flag to indicate when the thread should end. */

    void run(void) override; /**< Overriden run function that provides the main functionality of the thread. */

public:
    /**
     * @brief Constructor declaration.
     */
    UARTService()
    {
        start();
    };

    /**
     * @brief Destructor declaration.
     * It ensures that when a UARTService object is destroyed, the associated thread is joined.
     */
    ~UARTService()
    {
        end = true;
        wait();
    }
};
#endif // UARTSERVICE_H
