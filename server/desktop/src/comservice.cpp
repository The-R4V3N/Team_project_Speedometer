/**
 * @file comservice.cpp
 * @brief Implementation of the COMService class.
 */

#include "comservice.h"
#include "setting.h"
#include <climits>

/**
 * @brief Inserts a value into the buffer starting at the specified position.
 *
 * @param start The starting bit position in the buffer.
 * @param length The number of bits to insert.
 * @param value The value to insert.
 */
void COMService::insert(const uint32_t start, const uint32_t length, uint32_t value)
{
    int pos = start % CHAR_BIT;
    int index = start / CHAR_BIT;
    std::scoped_lock<std::mutex> locker{mtx};
    for (size_t i = 0; i < length; i++)
    {
        uint8_t bit = (uint8_t)((value >> i) & 1);

        if (bit == 0)
        {
            Buffer[index] &= ~(1 << pos);
        }
        else
        {
            Buffer[index] |= (1 << pos);
        }

        pos++;
        if (pos == CHAR_BIT)
        {
            pos = 0;
            index++;
        }
    }
}

/**
 * @brief Sets the speed value in the buffer.
 *
 * @param value The speed value to set.
 */
void COMService::setSpeed(uint32_t value)
{
    insert(Setting::Signal::Speed::START, Setting::Signal::Speed::LENGTH, value);
}

/**
 * @brief Sets the temperature value in the buffer.
 *
 * @param value The temperature value to set.
 */
void COMService::setTemperature(uint32_t value)
{
    insert(Setting::Signal::Temperature::START, Setting::Signal::Temperature::LENGTH, value);
}

/**
 * @brief Sets the battery level value in the buffer.
 *
 * @param value The battery level value to set.
 */
void COMService::setBatteryLevel(uint32_t value)
{
    insert(Setting::Signal::BatteryLevel::START, Setting::Signal::BatteryLevel::LENGTH, value);
}

/**
 * @brief Sets the left light value in the buffer.
 *
 * @param data The left light value to set.
 */
void COMService::SetLightLeft(bool data)
{
    uint32_t value = data ? 1U : 0;
    insert(Setting::Signal::Light::Left::START, Setting::Signal::Light::Left::LENGTH, value);
}

/**
 * @brief Sets the right light value in the buffer.
 *
 * @param data The right light value to set.
 */
void COMService::SetLightRight(bool data)
{
    uint32_t value = data ? 1U : 0;
    insert(Setting::Signal::Light::Right::START, Setting::Signal::Light::Right::LENGTH, value);
}