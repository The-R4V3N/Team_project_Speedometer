#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QSoundEffect>

/**
 * @brief The Canvas class is a custom QWidget that displays various vehicle information.
 */
class Canvas : public QWidget
{
    QPen drawPen;     /**< The pen used for drawing. */
    QBrush brush;     /**< The brush used for drawing. */
    QPainter painter; /**< The painter used for drawing. */
    QFont iconFont;   /**< The font used for drawing icons. */

    uint32_t batteryLevel{0};     /**< The current battery level. */
    bool status{false};           /**< The current status of the vehicle. */
    uint32_t speed{0};            /**< The current speed of the vehicle. */
    int32_t temperature{0};       /**< The current temperature of the vehicle. */
    bool leftLight{false};        /**< The current state of the left light. */
    bool rightLight{false};       /**< The current state of the right light. */
    QSoundEffect turnSignalSound; /**< The sound effect for the turn signal. */

public:
    /**
     * @brief Constructs a new Canvas object.
     * @param parent The parent widget.
     */
    Canvas();

    /**
     * @brief Sets the battery level.
     * @param level The new battery level.
     */
    void setBatteryLevel(uint32_t level) { batteryLevel = level; }

    /**
     * @brief Sets the temperature.
     * @param temp The new temperature.
     */
    void setTemperature(int32_t temp) { temperature = temp; }

    /**
     * @brief Sets the status.
     * @param sts The new status.
     */
    void setStatus(bool sts) { status = sts; }

    /**
     * @brief Sets the speed.
     * @param spd The new speed.
     */
    void setSpeed(uint32_t spd) { speed = spd; }

    /**
     * @brief Sets the state of the lights.
     * @param left The state of the left light.
     * @param right The state of the right light.
     */
    void setLight(bool left, bool right)
    {
        leftLight = left;
        rightLight = right;
    }

private:
    /**
     * @brief The paint event handler.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Draws the battery level.
     */
    void drawBatteryLevel(void);

    /**
     * @brief Draws the temperature level.
     */
    void drawTmpLevel(void);

    /**
     * @brief Draws the arrows.
     */
    void drawArrows(void);

    /**
     * @brief Draws the speed.
     */
    void drawSpeed(void);

    /**
     * @brief Draws the speedometer needle.
     */
    void drawSpeedometerNeedle(void);
};

#endif // CANVAS_H