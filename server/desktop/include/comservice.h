/**
 * @file comservice.h
 * @brief Header file for the COMService class.
 *
 * This file contains the declaration of the COMService class, which is responsible for handling communication with external devices.
 * The class provides methods for setting various parameters such as speed, temperature, battery level, and lights.
 * It also contains a protected buffer for storing signals and a mutex for thread safety.
 */
#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <cstdint>
#include <mutex>
#include <atomic>
#include "setting.h"

class COMService
{
    void insert(uint32_t start, uint32_t length, uint32_t value);

protected:
    std::mutex mtx;
    std::atomic<bool> status{false};
    uint8_t Buffer[Setting::Signal::BUFSIZE]{0};

    virtual void run(void) = 0;

public:
    bool getStatus(void) { return status; }
    void setSpeed(uint32_t value);
    void setTemperature(uint32_t value);
    void setBatteryLevel(uint32_t value);
    void SetLightLeft(bool value);
    void SetLightRight(bool value);

    virtual ~COMService() = default;
};

#endif // COMSERVICE_H