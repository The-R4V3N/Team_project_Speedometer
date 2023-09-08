#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <cstdint>
#include <mutex>
#include <atomic>
#include "setting.h"

/**
 * @brief The COMService class provides a base class for communication services.
 *
 * This class provides a base implementation for communication services. It includes
 * methods for setting various parameters such as speed, temperature, and battery level,
 * as well as methods for controlling the left and right lights. The class also includes
 * a protected buffer for storing signal data, as well as a mutex for thread safety.
 *
 * To use this class, you should subclass it and implement the run() method. This method
 * should contain the main logic for your communication service.
 */
class COMService
{
    void insert(uint32_t start, uint32_t length, uint32_t value);

protected:
    std::mutex mtx;                  /**< Mutex for thread safety */
    std::atomic<bool> status{false}; /**< Atomic boolean for status */

    uint8_t Buffer[Setting::Signal::BUFSIZE]{0}; /**< Buffer for storing signal data */

    /**
     * @brief The run() method should contain the main logic for your communication service.
     *
     * This method should contain the main logic for your communication service. It will be
     * called by the start() method, which should be implemented in your subclass.
     */
    virtual void run(void) = 0;

public:
    /**
     * @brief Get the status of the communication service.
     *
     * @return true if the communication service is running, false otherwise.
     */
    bool getStatus(void) { return status; }

    /**
     * @brief Set the speed parameter.
     *
     * @param value The new value for the speed parameter.
     */
    void setSpeed(uint32_t value);

    /**
     * @brief Set the temperature parameter.
     *
     * @param value The new value for the temperature parameter.
     */
    void setTemperature(uint32_t value);

    /**
     * @brief Set the battery level parameter.
     *
     * @param value The new value for the battery level parameter.
     */
    void setBatteryLevel(uint32_t value);

    /**
     * @brief Set the left light.
     *
     * @param value true to turn on the left light, false to turn it off.
     */
    void SetLightLeft(bool value);

    /**
     * @brief Set the right light.
     *
     * @param value true to turn on the right light, false to turn it off.
     */
    void SetLightRight(bool value);

    virtual ~COMService() = default;

private:
};

#endif