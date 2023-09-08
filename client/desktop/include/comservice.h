#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <mutex>
#include <atomic>
#include <cstdint>
#include "setting.h"
#include <QObject>

/**
 * @brief The COMService class is a base class for services that communicate with the vehicle.
 */
class COMService : public QObject
{
    /**
     * @brief Extracts a value from the buffer.
     * @param start The starting index of the value in the buffer.
     * @param length The length of the value in bits.
     * @param value The extracted value.
     */
    void extract(uint32_t start, uint32_t length, uint32_t &value);

    /**
     * @brief Extracts a value from the buffer.
     * @param start The starting index of the value in the buffer.
     * @param length The length of the value in bits.
     * @param value The extracted value.
     */
    void extract(uint32_t start, uint32_t length, int32_t &value);

protected:
    std::mutex mtx;                              /**< Mutex to protect the buffer. */
    std::atomic<bool> status{false};             /**< Atomic boolean to indicate the status of the service. */
    uint8_t Buffer[Setting::Signal::BUFSIZE]{0}; /**< Buffer to store the data received from the vehicle. */

    /**
     * @brief The run method is a pure virtual method that must be implemented by the derived classes.
     */
    virtual void run(void) = 0;

public:
    /**
     * @brief Returns the status of the service.
     * @return The status of the service.
     */
    bool getStatus(void) { return status; }

    /**
     * @brief Returns the speed of the vehicle.
     * @return The speed of the vehicle.
     */
    uint32_t getSpeed(void);

    /**
     * @brief Returns the temperature of the vehicle.
     * @return The temperature of the vehicle.
     */
    int32_t getTemperature(void);

    /**
     * @brief Returns the battery level of the vehicle.
     * @return The battery level of the vehicle.
     */
    uint32_t getBatteryLevel(void);

    /**
     * @brief Returns the status of the left light of the vehicle.
     * @return The status of the left light of the vehicle.
     */
    bool getLightLeft(void);

    /**
     * @brief Returns the status of the right light of the vehicle.
     * @return The status of the right light of the vehicle.
     */
    bool getLightRight(void);

    /**
     * @brief The destructor of the COMService class.
     */
    virtual ~COMService() = default;
};

#endif