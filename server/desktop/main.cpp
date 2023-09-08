#include <QApplication>
#include "window.h"
#ifdef UARTCOM
#include "uartservice.h"
#else
#include "tcpservice.h"
#endif

/**
 * @file main.cpp
 * @brief Entry point of the application. Initializes the QApplication and the service used by the Window.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Exit code of the application.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef UARTCOM
    UARTService service;
#else
    TCPService service;
#endif

    Window clientWindow{&service};

    clientWindow.show();

    return app.exec();
}
