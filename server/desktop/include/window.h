#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>
#include <QSlider>
#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "comservice.h"

/**
 * @brief The Window class represents the main window of the application.
 *
 * This class inherits from QDialog and contains various UI elements such as sliders, labels, and checkboxes.
 * It also has a COMService object for communication with the server.
 */
class Window : public QDialog
{
    COMService *communication{nullptr};

public:
    /**
     * @brief Default constructor for the Window class.
     */
    Window();

    /**
     * @brief Constructor for the Window class that takes a COMService object as a parameter.
     *
     * @param com A pointer to a COMService object for communication with the server.
     */
    Window(COMService *com);

    /**
     * @brief The layout of the window.
     */
    QGridLayout layout{this};

private:
    QSlider speedSlider;              /**<The slider for the speed signal*/
    QLabel speedLabel{"Speed:"};      /**<The label for the speed signal*/
    QLabel speedValueLabel{"0 km/h"}; /**<The label for the speed value*/

    QLabel lightLabel{"Light signals: "}; /**<The label for the light signals*/

    QSlider temperatureSlider;               /**<The slider for the temperature signal*/
    QLabel temperatureLabel{"Temperature:"}; /**<The label for the temperature signal*/
    QLabel temperatureValueLabel{"0 °C"};    /**<The label for the temperature value*/
    QLabel batteryLabel{"Battery:"};         /**<The label for the battery signal*/

    QSlider batterySlider;                       /**<The slider for the battery signal*/
    QLabel batteryValueLabel{"0%"};              /**<The label for the battery value*/
    QCheckBox leftLightCheckBox{"Left Light"};   /**<The checkbox for the left light signal*/
    QCheckBox rightLightCheckBox{"Right Light"}; /**<The checkbox for the right light signal*/
    QCheckBox warningLightCheckBox{"Warning"};   /**<The checkbox for the warning light signal*/

    QHBoxLayout lightLayout; /**<The layout for the light signals*/
};

#endif // WINDOW_H
