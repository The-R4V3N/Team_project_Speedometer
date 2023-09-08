#include <QDebug>
#include "window.h"
#include "setting.h"
#include "comservice.h"

/**
 * @brief Constructor for the Window class.
 *
 * @param com Pointer to the COMService object.
 */
Window::Window(COMService *com) : communication{com}
{
    setFixedHeight(Setting::Server::Window::Height);
    setFixedWidth(Setting::Server::Window::Width);
    setWindowFlag(Qt::WindowStaysOnTopHint);

    speedSlider.setOrientation(Qt::Horizontal);
    speedSlider.setRange(Setting::Signal::Speed::MIN, Setting::Signal::Speed::MAX);

    layout.addWidget(&speedLabel, 0, 0);
    layout.addWidget(&speedSlider, 0, 1);
    layout.addWidget(&speedValueLabel, 0, 2);

    temperatureSlider.setOrientation(Qt::Horizontal);
    temperatureSlider.setRange(Setting::Signal::Temperature::MIN, Setting::Signal::Temperature::MAX);

    layout.addWidget(&temperatureLabel, 1, 0);
    layout.addWidget(&temperatureSlider, 1, 1);
    layout.addWidget(&temperatureValueLabel, 1, 2);

    batterySlider.setOrientation(Qt::Horizontal);
    batterySlider.setRange(Setting::Signal::BatteryLevel::MIN, Setting::Signal::BatteryLevel::MAX);

    layout.addWidget(&batteryLabel, 2, 0);
    layout.addWidget(&batterySlider, 2, 1);
    layout.addWidget(&batteryValueLabel, 2, 2);

    layout.addWidget(&lightLabel, 3, 0);

    lightLayout.addWidget(&leftLightCheckBox);
    lightLayout.addWidget(&rightLightCheckBox);
    lightLayout.addWidget(&warningLightCheckBox);

    layout.addLayout(&lightLayout, 3, 1, 1, 2);

    setLayout(&layout);

    connect(&speedSlider, &QSlider::valueChanged, [=](int value)
            {
        speedValueLabel.setText(QString::number(value) + " km/h");
        communication->setSpeed(value); });

    connect(&temperatureSlider, &QSlider::valueChanged, [=](int value)
            {
        temperatureValueLabel.setText(QString::number(value) + "°C");
        communication->setTemperature(value); });

    connect(&batterySlider, &QSlider::valueChanged, [=](int value)
            {
        batteryValueLabel.setText(QString::number(value) + "%");
        communication->setBatteryLevel(value); });

    connect(&leftLightCheckBox, &QCheckBox::toggled, [=](bool checked)
            {
        if (checked) {
            communication->SetLightLeft(true);
            rightLightCheckBox.setEnabled(false);
        } else {
            rightLightCheckBox.setEnabled(true);
            communication->SetLightLeft(false);
        } });

    connect(&rightLightCheckBox, &QCheckBox::toggled, [=](bool checked)
            {
        if (checked) {
            leftLightCheckBox.setEnabled(false);
            communication->SetLightRight(true);
        }
        else
        {
            leftLightCheckBox.setEnabled(true);
            communication->SetLightRight(false);
        } });

    connect(&warningLightCheckBox, &QCheckBox::toggled, [=](bool checked)
            {
        if (checked) {
            // remove if not to untoggle right/left button when warning is pressed.
            communication->SetLightRight(true);
            communication->SetLightLeft(true);

            leftLightCheckBox.setChecked(false);
            rightLightCheckBox.setChecked(false);
            //
        }
        else
        {
            communication->SetLightRight(false);
            communication->SetLightLeft(false);
        } });
}
