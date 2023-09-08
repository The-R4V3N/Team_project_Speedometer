/**
 * @file main.cpp
 * @brief This file contains the main function that initializes the client window and starts the application.
 *
 * The main function initializes the QApplication and creates a Window object. The Window object is then shown and the
 * application is started by calling app.exec().
 */
#include <QApplication>
#include "window.h"
#ifdef UARTCOM
#include "uartservice.h"
#else
#include "tcpservice.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); /**<Create a QApplication object*/

#ifdef UARTCOM /**<Check if UART communication is enabled*/
    UARTService service;
#else /**<If UART communication is not enabled*/
    TCPService service;
#endif

    Window clientWindow{&service}; /**<Create a Window object*/

    clientWindow.show(); /**<Show the Window object*/

    return app.exec(); /**<Start the application*/
}
