#ifndef WINDOW_H
#define WINDOW_H

#include <QTimer>
#include "canvas.h"
#include <QDialog>
#include <QGridLayout>
#include "comservice.h"

/**
 * @class Window
 * @brief Represents a dialog window with a canvas for drawing.
 */
class Window : public QDialog
{
    QTimer timer;                       /**< Timer used to refresh the canvas periodically. */
    Canvas canvas;                      /**< Canvas used for drawing. */
    QGridLayout layout;                 /**< Layout used to organize the widgets in the window. */
    COMService *communication{nullptr}; /**< Pointer to the COMService object used for communication with the vehicle. */

public:
    /**
     * @brief Constructs a new Window object.
     */
    Window(COMService *com);

private:
    /**
     * @brief Refreshes the canvas by redrawing its contents.
     */
    void refresh();
};

#endif // WINDOW_H
