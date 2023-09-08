#include "comservice.h"
#include <climits>

/**
 * @brief Extracts a value from the buffer starting at a given position and with a given length.
 *
 * @param start The starting position of the value in the buffer.
 * @param length The length of the value to extract.
 * @param value The extracted value.
 */
void COMService::extract(uint32_t start, uint32_t length, uint32_t &value)
{
    value = 0;
    int pos = start % CHAR_BIT;
    int index = start / CHAR_BIT;

    std::lock_guard<std::mutex> lock(mtx);

    for (int i = 0; i < length; ++i)
    {
        if (((Buffer[index] >> pos) & 1) != 0)
        {
            value |= (1 << i);
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
 * @brief Extracts a value from the buffer starting at a given position and with a given length.
 *
 * @param start The starting position of the value in the buffer.
 * @param length The length of the value to extract.
 * @param value The extracted value.
 */
void COMService::extract(uint32_t start, uint32_t length, int32_t &value)
{
    extract(start, length, reinterpret_cast<uint32_t &>(value));

    if ((value & (1 << (length - 1))) != 0)
    {
        value |= ~((1 << length) - 1);
    }
}

/**
 * @brief Returns the speed value from the COMService object.
 *
 * @return uint32_t The speed value.
 */
uint32_t COMService::getSpeed(void)
{
    uint32_t value;
    extract(Setting::Signal::Speed::START, Setting::Signal::Speed::LENGTH, value);
    return value;
}

/**
 * @brief Returns the temperature value from the COMService object.
 *
 * @return uint32_t The temperature value.
 */
int32_t COMService::getTemperature(void)
{
    int32_t value;
    extract(Setting::Signal::Temperature::START, Setting::Signal::Temperature::LENGTH, value);
    return value;
}

/**
 * @brief Returns the battery level value from the COMService object.
 *
 * @return uint32_t The battery level value.
 */
uint32_t COMService::getBatteryLevel(void)
{
    uint32_t value;
    extract(Setting::Signal::BatteryLevel::START, Setting::Signal::BatteryLevel::LENGTH, value);
    return value;
}

/**
 * @brief Returns the state of the left light from the COMService object.
 *
 * @return bool The state of the left light.
 */
bool COMService::getLightLeft(void)
{
    uint32_t value;
    extract(Setting::Signal::Light::Left::START, Setting::Signal::Light::Left::LENGTH, value);
    return value;
}

/**
 * @brief Returns the state of the right light from the COMService object.
 *
 * @return bool The state of the right light.
 */

bool COMService::getLightRight(void)
{
    uint32_t value;
    extract(Setting::Signal::Light::Right::START, Setting::Signal::Light::Right::LENGTH, value);
    return value;
}