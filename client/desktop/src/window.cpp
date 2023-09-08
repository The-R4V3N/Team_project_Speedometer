#include "window.h"
#include "setting.h"

/**
 * @brief Constructor for the Window class.
 *
 * This constructor sets the window flags to always stay on top, sets the window title to "Client",
 * adds the canvas to the layout, sets the layout margins to 0, sets the canvas size policy to fixed,
 * sets the canvas width and height from the shared header file, connects the timer's timeout signal
 * to the refresh slot, and starts the timer with an interval of 1000 ms (1 second).
 *
 * @param None.
 * @return None.
 *
 * @note This constructor is called when a Window object is created.
 *
 */
Window::Window(COMService *com) : communication{com}
{
    setWindowFlags(Qt::WindowStaysOnTopHint); /**<Set the window to be always on top*/
    setWindowTitle("Client");                 /**<Set the window title*/
    layout.addWidget(&canvas, 0, 0, 1, 3);    /**<Add the canvas to the layout*/
    layout.setContentsMargins(0, 0, 0, 0);    /**<Set the layout margins*/

    setLayout(&layout);

    canvas.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); /**<Set the canvas size policy*/
    canvas.setFixedWidth(Setting::Client::Windows::Width);        /**<Set the canvas width from the shared setting.h file*/
    canvas.setFixedHeight(Setting::Client::Windows::Height);      /**<Set the canvas height from the shared setting.h file*/

    /**<Connect the timer's timeout signal to the refresh slot*/
    connect(&timer, &QTimer::timeout, this, &Window::refresh);

    /**<Set the timer interval (in milliseconds) the interval is defined in the shared setting.h file*/
    timer.start(Setting::INTERVAL); /**<Start the timer*/
}

/**
 * @brief Refreshes the window by updating the canvas with the latest data received from the communication module.
 *
 * This function updates the battery level, temperature, speed, light, and status of the canvas by calling the corresponding functions of the communication module.
 * It then triggers the repaint of the canvas by calling the update() function.
 */
void Window::refresh()
{
    if (communication->getStatus()) /**<Check if the communication module is connected */
    {
        canvas.setBatteryLevel(communication->getBatteryLevel());                       /**<Set the Battery Level*/
        canvas.setTemperature(communication->getTemperature());                         /**<Set the Temperature*/
        canvas.setSpeed(communication->getSpeed());                                     /**<Set the Speed*/
        canvas.setLight(communication->getLightLeft(), communication->getLightRight()); /**<Set the Light*/
        canvas.setStatus(true);                                                         /**<Set the Status*/
    }
    else /**<If the communication module is not connected*/
    {
        canvas.setStatus(false);   /**<Set the status*/
        canvas.setBatteryLevel(0); /**<Set the Battery Level*/
        canvas.setTemperature(0);  /**<Set the Temperature*/
        canvas.setSpeed(0);        /**<Set the Speed*/
        canvas.setLight(0, 0);     /**<Set the Light*/
    }

    canvas.update(); /**<Trigger the repaint of the canvas*/
}
