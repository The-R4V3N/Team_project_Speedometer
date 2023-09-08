#include "canvas.h"
#include "setting.h"
#include <QFileInfo>
#include <QPaintEvent>
#include <QFontDatabase>
#include <QMediaDevices>
#include <QAudioDevice>

/**
 * @brief Constructor for the Canvas class
 *
 * Initializes paths and fonts, adds the application font, and initializes the brush and pen.
 *
 */
Canvas::Canvas()
{
    /**
     * @brief Initialize paths and fonts
     *
     */
    QFileInfo file{__FILE__};                                                     /**<Get the path of the current file*/
    QString resPath = file.absolutePath() + "/../res/";                           /**<Get the path of the resources folder*/
    QFontDatabase::addApplicationFont(resPath + "font.ttf");                      /**<Add the application font*/
    turnSignalSound.setAudioDevice(QMediaDevices::defaultAudioOutput());          /**<Set the audio device*/
    turnSignalSound.setSource(QUrl::fromLocalFile(resPath + "turn-signals.wav")); /**<Set the audio source*/
    turnSignalSound.setLoopCount(QSoundEffect::Infinite);                         /**<Set the loop count*/
    turnSignalSound.setVolume(1);                                                 /**<Set the volume*/

    /**
     * @brief Initialize brush and pen
     *
     */
    brush = QBrush(QColor(0xa6, 0x2e, 0x39));
}

/**
 * @brief This function is called whenever the canvas needs to be repainted.
 *
 * @param event The paint event that triggered the repaint.
 */
void Canvas::paintEvent(QPaintEvent *event)
{
    painter.begin(this);                                      /**<Start painting*/
    painter.setRenderHint(QPainter::Antialiasing);            /**<Set the render hint*/
    painter.fillRect(event->rect(), QBrush(QColor(6, 6, 6))); /**<Fill the rectangle with the specified brush*/

    /**
     * @brief Call the diffrent Drawing functions.
     *
     * @return * Call
     */
    drawBatteryLevel();      /**<Call the drawBatteryLevel function*/
    drawTmpLevel();          /**<Call the drawTmpLevel function*/
    drawArrows();            /**<Call the drawArrows function*/
    drawSpeed();             /**<Call the drawSpeed function*/
    drawSpeedometerNeedle(); /**<Call the drawSpeedometerNeedle function*/

    painter.end(); /**<End painting*/
}

/**
 * @brief Draws the battery level on the canvas.
 *
 * This function calculates the height of the battery rectangle based on the battery level,
 * chooses the battery symbol color based on the battery level, and draws the battery icon
 * with the selected color. It also draws the battery level rectangle, battery level, and
 * battery text on the canvas.
 *
 * @param None.
 * @return None.
 *
 * @note This function assumes that the painter object has already been initialized.
 * @warning This function does not check if the battery level is within the valid range.
 *
 * @see Canvas, QPainter
 */

void Canvas::drawBatteryLevel()
{
    /**< Calculate the height of the battery rectangle based on the battery level. */
    int batteryHeight = static_cast<int>(batteryLevel * 0.4); /**<0.4 pixels per percentage point.*/

    /**<Choose the battery symbol color based on battery level*/
    QColor symbolColor;
    if (batteryLevel < 25)
    {
        symbolColor = QColor(255, 0, 0); /**>Red for battery level < 25%.*/
    }
    else if (batteryLevel >= 25 && batteryLevel <= 49)
    {
        symbolColor = QColor(255, 255, 0); /**<Yellow for battery level between [25,49]%.*/
    }
    else
    {
        symbolColor = QColor(0, 255, 0); /**<Green for battery level > 49%.*/
    }

    /**<Draw battery icon with the selected color.*/
    iconFont = QFont("Material Icons", 50, QFont::Normal);                       /**<Font*/
    painter.setPen(symbolColor);                                                 /**<Use the selected color*/
    painter.setFont(iconFont);                                                   /**<Font*/
    painter.drawText(QRect(680, 280, 100, 100), Qt::AlignCenter, QChar(0xebdc)); /**<Battery icon.*/

    // Draw battery level rectangle
    painter.setPen(Qt::NoPen);                                                    /**<No outline*/
    painter.setBrush(symbolColor);                                                /**<Use the selected color*/
    painter.drawRect(QRect(716, 153 + (200 - batteryHeight), 28, batteryHeight)); /**<Rectangle dimensions*/

    // Draw Battery level
    painter.setPen(QColor(255, 255, 255));                                     /**<White text*/
    painter.setFont(QFont("Arial", 11));                                       /**<Font*/
    QString batteryText = QString::number(batteryLevel) + " %";                /**<Battery level text*/
    painter.drawText(QRect(680, 330, 100, 100), Qt::AlignCenter, batteryText); /**<Draw the text*/
}

/**
 * @brief Draws the temperature level and icon on the canvas.
 *
 * This function draws the temperature level and icon on the canvas. The temperature level is displayed in Celsius and the color of the icon changes based on the temperature range. White is used for temperatures below or equal to 5°C, blue is used for temperatures between 6°C and 39°C, and red is used for temperatures above 39°C.
 *
 * @return void
 *
 * @see Canvas
 */
void Canvas::drawTmpLevel(void)
{
    painter.setPen(QColor(255, 255, 255));                                         /**<White Text*/
    painter.setFont(QFont("Arial", 11));                                           /**<Font and Font size*/
    QString temperatureText = QString::number(temperature) + " °C";                /**<Temperature text*/
    painter.drawText(QRect(680, 425, 100, 100), Qt::AlignCenter, temperatureText); /**<Draw the text*/

    /**
     * @brief Choose the temperature icon color based on the temperature level.
     *
     */
    QColor iconColor;
    if (temperature <= 5)
    {
        iconColor = QColor(255, 255, 255); /**<White for temperatures below or equal to 5°C.*/
    }
    else if (temperature <= 39)
    {
        iconColor = QColor(77, 130, 255); /**<Blue for temperatures between 6°C and 39°C.*/
    }
    else
    {
        iconColor = QColor(255, 0, 0); /**<Red for temperatures above 39°C.*/
    }

    /**
     * @brief Draw the temperature icon with the selected color.
     *
     */
    iconFont = QFont{"Material Icons", 50, QFont::Normal};                       /**<Font*/
    painter.setPen(QColor(iconColor));                                           /**<Use the selected color*/
    painter.setFont(iconFont);                                                   /**<Font*/
    painter.drawText(QRect(680, 380, 100, 100), Qt::AlignCenter, QChar(0xf076)); /**<Temperature icon.*/
}

/**
 * @brief Draws arrows on the canvas based on the state of the left and right turn signals.
 *
 * @details The function draws arrows on the canvas using the QPainter object. The arrows are Material Icons and are drawn in green color. The left arrow is drawn on the left side of the canvas and the right arrow is drawn on the right side of the canvas. The arrows blink on and off based on the state of the turn signals. If either the left or right turn signal is on, the arrows will blink and a turn signal sound will play. If both turn signals are off, the arrows will not blink and the turn signal sound will stop.
 *
 * @param void
 * @return void
 *
 * @note This function is called by the Canvas class.
 * @warning The Material Icons font must be installed on the system for the arrows to be drawn correctly.
 */
void Canvas::drawArrows(void)
{
    constexpr int MAX_COUNT{14}; /**<Adjust the maximum count as needed. Higher values will result in slower blinking.*/
    static int blink{0};         /**<Initialize the blink counter.*/
    if (leftLight || rightLight) /**<Check if either the left or right turn signal is on*/
    {
        blink = (blink + 1) % MAX_COUNT; /**<Increment the blink counter*/

        if (!turnSignalSound.isPlaying()) /**<Check if the turn signal sound is not playing*/
        {
            turnSignalSound.play(); /**<Play the turn signal sound*/
        }
    }
    else
    {
        blink = 0;              /**<Reset the blink counter*/
        turnSignalSound.stop(); /**<Stop the turn signal sound*/
    }
    if (blink <= MAX_COUNT / 2) /**<Check if the blink counter is less than or equal to half of the maximum count*/
    {
        painter.setFont(QFont{"Material Icons", 46, QFont::Normal}); /**<Set the font and font size*/
        if (leftLight)
        {
            painter.setPen(QColor(0, 255, 0));                                      /**<Set the pen color to green*/
            painter.drawText(QRect(10, 5, 40, 40), Qt::AlignCenter, QChar(0xe5c4)); /**<Left Arrow Icon*/
        }
        if (rightLight)
        {
            painter.setPen(QColor(0, 255, 0));                                       /**<Set the pen color to green*/
            painter.drawText(QRect(620, 5, 40, 40), Qt::AlignCenter, QChar(0xe5c8)); /**<Right Arrow Icon*/
        }
    }
}

/**
 * @brief Draws a speedometer on the canvas.
 *
 * This function draws a speedometer on the canvas using the provided parameters.
 * It calculates the center X and Y coordinates of the canvas, as well as the radius of the circle to fit within the canvas.
 * It then sets up the pen for drawing the arc outline and draws the arc outline.
 * Main markings are drawn at evenly spaced intervals, with the number of sub-markings and their thickness and radius being adjustable.
 * Sub-markings and sub-sub-markings are also drawn between main markings.
 *
 * @return void
 */
void Canvas::drawSpeed(void)
{
    int centerX = width() / 2 * 0.9;  /**<Calculate the center X-coordinate of the canvas*/
    int centerY = height() / 2 * 1.2; /**<Calculate the center Y-coordinate of the canvas*/

    /**<Calculate the radius of the circle to fit within the canvas*/
    int radius = qMin(width(), height()) * 0.55; /**<Adjust the scale factor for the needle as needed*/

    int startAngle = -40 * 16; /**<Start angle in degrees * 16 (Qt uses 16-bit fixed point angles)*/
    int endAngle = 220 * 16;   /**<End angle in degrees * 16*/

    int startA = -37 * 16; /**<Start angle for the markings*/
    int endA = 217 * 16;   /**<End angle for the markings*/

    /**<Set up the pen for drawing the arc outline*/
    QPen pen(Qt::white);        /**<Color of the arc outline */
    int arcThickness = 8;       /**<Thickness of the arc outline in pixels*/
    pen.setWidth(arcThickness); /**<Adjust the pen width as needed*/
    painter.setPen(pen);

    /**<Draw the arc outline*/
    painter.drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, startAngle, endAngle - startAngle);

    /**<Draw main markings at evenly spaced intervals*/
    int numMainMarkings = 13;
    int numSubMarkings = 1;          /**<Adjust the number of sub-markings*/
    int markingThickness = 7;        /**<Adjust the thickness of the markings*/
    int markingRadius = radius - 25; /**<Adjust the radius where markings are drawn*/
    int markingLength = 25;

    pen.setWidth(markingThickness); /**<Thickness of the markings outline in pixels*/
    qreal angleIncrement = static_cast<qreal>(endA - startA) / (numMainMarkings - 1);

    for (int i = 0; i < numMainMarkings; ++i)
    {
        qreal angle = startA + i * angleIncrement;            /**<Calculate the angle for the current marking*/
        qreal angleRadians = qDegreesToRadians(angle / 16.0); /**<Convert the angle to radians*/

        qreal startX = centerX + (radius - 10) * qCos(angleRadians);          /**<Calculate the start X-coordinate of the marking*/
        qreal startY = centerY - (radius - 10) * qSin(angleRadians);          /**<Calculate the start Y-coordinate of the marking*/
        qreal endX = centerX + (radius - markingLength) * qCos(angleRadians); /**<Calculate the end X-coordinate of the marking*/
        qreal endY = centerY - (radius - markingLength) * qSin(angleRadians); /**<Calculate the end Y-coordinate of the marking*/

        painter.setPen(QPen(Qt::white, markingThickness));              /**<Set the pen for drawing the markings*/
        painter.drawLine(QPointF(startX, startY), QPointF(endX, endY)); /**<Draw the marking*/

        // Draw sub-markings
        if (i != numMainMarkings - 1)
        {
            qreal subMarkingAngleIncrement = (endAngle - startAngle) / (numMainMarkings - 1) / (numSubMarkings + 1); /**<Angle increment between sub-markings*/
            qreal subMarkingAngle = angle + subMarkingAngleIncrement;                                                /**<Angle for the first sub-marking*/

            for (int j = 0; j < numSubMarkings; ++j)
            {
                qreal subMarkingStartX = centerX + markingRadius * qCos(qDegreesToRadians(subMarkingAngle / 16.0));              /**<Calculate the start X-coordinate of the sub-marking*/
                qreal subMarkingStartY = centerY - markingRadius * qSin(qDegreesToRadians(subMarkingAngle / 16.0));              /**<Calculate the start Y-coordinate of the sub-marking*/
                qreal subMarkingEndX = subMarkingStartX + markingLength * 0.5 * qCos(qDegreesToRadians(subMarkingAngle / 16.0)); /**<Calculate the end X-coordinate of the sub-marking*/
                qreal subMarkingEndY = subMarkingStartY - markingLength * 0.5 * qSin(qDegreesToRadians(subMarkingAngle / 16.0)); /**<Calculate the end Y-coordinate of the sub-marking*/

                painter.setPen(QPen(Qt::white, 3));                                                                     /**<Set the pen for drawing the sub-markings*/
                painter.drawLine(QPointF(subMarkingStartX, subMarkingStartY), QPointF(subMarkingEndX, subMarkingEndY)); /**<Draw the sub-marking*/

                subMarkingAngle += subMarkingAngleIncrement; /**<Calculate the angle for the next sub-marking*/

                /**<Draw sub-sub-markings between main and sub markings*/
                qreal subSubMarkingAngleIncrement = subMarkingAngleIncrement / (numSubMarkings + 1); /**<Angle increment between sub-sub-markings*/
                qreal subSubMarkingAngle = subMarkingAngle - subSubMarkingAngleIncrement;            /**<Angle for the first sub-sub-marking*/
                qreal subSubMarkingAngle2 = angle + subSubMarkingAngleIncrement;                     /**<Angle for the second sub-sub-marking*/

                for (int k = 0; k < numSubMarkings; ++k)
                {
                    qreal subSubMarkingStartX = centerX + markingRadius * qCos(qDegreesToRadians(subSubMarkingAngle / 16.0));                  /**<Calculate the start X-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingStartY = centerY - markingRadius * qSin(qDegreesToRadians(subSubMarkingAngle / 16.0));                  /**<Calculate the start Y-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingEndX = subSubMarkingStartX + markingLength * 0.25 * qCos(qDegreesToRadians(subSubMarkingAngle / 16.0)); /**<Calculate the end X-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingEndY = subSubMarkingStartY - markingLength * 0.25 * qSin(qDegreesToRadians(subSubMarkingAngle / 16.0)); /**<Calculate the end Y-coordinate of the sub-sub-marking*/

                    painter.setPen(QPen(Qt::white, 2));                                                                                 /**<Set the pen for drawing the sub-sub-markings*/
                    painter.drawLine(QPointF(subSubMarkingStartX, subSubMarkingStartY), QPointF(subSubMarkingEndX, subSubMarkingEndY)); /**<Draw the sub-sub-marking*/

                    subSubMarkingAngle -= subSubMarkingAngleIncrement; /**<Calculate the angle for the next sub-sub-marking*/

                    qreal subSubMarkingStartX2 = centerX + markingRadius * qCos(qDegreesToRadians(subSubMarkingAngle2 / 16.0));                   /**<Calculate the start X-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingStartY2 = centerY - markingRadius * qSin(qDegreesToRadians(subSubMarkingAngle2 / 16.0));                   /**<Calculate the start Y-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingEndX2 = subSubMarkingStartX2 + markingLength * 0.25 * qCos(qDegreesToRadians(subSubMarkingAngle2 / 16.0)); /**<Calculate the end X-coordinate of the sub-sub-marking*/
                    qreal subSubMarkingEndY2 = subSubMarkingStartY2 - markingLength * 0.25 * qSin(qDegreesToRadians(subSubMarkingAngle2 / 16.0)); /**<Calculate the end Y-coordinate of the sub-sub-marking*/

                    painter.setPen(QPen(Qt::white, 2));                                                                                     /**<Set the pen for drawing the sub-sub-markings*/
                    painter.drawLine(QPointF(subSubMarkingStartX2, subSubMarkingStartY2), QPointF(subSubMarkingEndX2, subSubMarkingEndY2)); /**<Draw the sub-sub-marking*/

                    subSubMarkingAngle2 += subSubMarkingAngleIncrement; /**<Calculate the angle for the next sub-sub-marking*/

                    /**<Draw sub-sub-markings*/
                    qreal subSubMarkingAngleIncrement = subMarkingAngleIncrement / (numSubMarkings + 1); /**<Angle increment between sub-sub-markings*/
                    qreal subSubMarkingAngle = subMarkingAngle + subSubMarkingAngleIncrement;            /**<Angle for the first sub-sub-marking*/
                    qreal subSubMarkingAngle2 = subMarkingAngle - subSubMarkingAngleIncrement;           /**<Angle for the second sub-sub-marking*/
                }
            }
        }
    }

    /**<Draw the integer labels for the speedometer*/
    int labelRadius = radius - 60; /**<Adjust the radius where labels are drawn*/
    int labelPadding = 10;         /**<Adjust the padding between the labels and the markings*/

    for (int speed = 0; speed <= 240; speed += 20)
    {
        qreal angle = startA + (endA - startA) * (1.0 - (speed / 240.0)); /**<Invert the angle calculation*/
        qreal angleRadians = qDegreesToRadians(angle / 16.0);             /**<Convert the angle to radians*/

        QString label = QString::number(speed);             /**<Convert the speed to a string*/
        QFont labelFont("Arial", 14, QFont::Bold);          /**<Set the font and font size*/
        QFontMetrics labelMetrics(labelFont);               /**<Get the font metrics for the label*/
        QRect labelRect = labelMetrics.boundingRect(label); /**<Get the bounding rectangle for the label*/
        int labelWidth = labelRect.width();                 /**<Get the width of the label*/
        int labelHeight = labelRect.height();               /**<Get the height of the label*/

        qreal labelX = centerX + (labelRadius + labelPadding) * qCos(angleRadians) - labelWidth / 2.0;  /**<Calculate the X-coordinate of the label*/
        qreal labelY = centerY - (labelRadius + labelPadding) * qSin(angleRadians) + labelHeight / 4.0; /**<Calculate the Y-coordinate of the label*/

        painter.setFont(labelFont);              /**<Set the font for drawing the label*/
        painter.setPen(QPen(Qt::white));         /**<Set the pen for drawing the label*/
        painter.drawText(labelX, labelY, label); /**<Draw the label*/
    }

    /**<Calculate position for the speed text*/
    int textX = width() / 2 - 80; /**<Adjust the Text X position as needed*/
    int textY = height() - 20;    /**<Adjust the Text Y position as needed*/

    /**<Calculate position for the speed logo*/
    int logoX = textX;       /**<Adjust the X position for the logo*/
    int logoY = textY - 100; /**<Adjust the Y position for the logo*/

    /**<Draw the speedometer speed logo*/
    iconFont.setPixelSize(50); /**<Adjust the font size as needed*/
    painter.setFont(iconFont); /**<Set the font for drawing the logo*/

    int iconWidth = 70;  /**<Adjust the width of the icon as needed*/
    int iconHeight = 70; /**<Adjust the height of the icon as needed*/

    QString speedValueText; /**<Initialize the speed value text*/
    if (status)
    {
        int speedValueX = logoX - 5;                                                                  /**<Adjust X position*/
        int speedValueY = logoY + iconHeight + 10;                                                    /**<Adjust Y position*/
        painter.drawText(QRect(logoX, logoY, iconWidth, iconHeight), Qt::AlignCenter, QChar(0xe9e4)); /**<Speedometer icon*/
        speedValueText = QString::number(speed) + " km/h";                                            /**<Speed value text*/
        painter.setPen(Qt::white);                                                                    /**<Set the pen for drawing the speed value text*/
        QFont boldLabelFont("Arial", 20, QFont::Normal);                                              /**<Create a bold version of the label font*/
        painter.setFont(boldLabelFont);                                                               /**<Set the font for drawing the speed value text*/
        painter.drawText(speedValueX - 10, speedValueY + 10, speedValueText);                         /**<Draw the speed value text*/
    }
    else
    {
        int speedValueX = logoX - 5;                                                                  /**<Adjust X position*/
        int speedValueY = logoY + iconHeight + 10;                                                    /**<Adjust Y position*/
        QPen redPen(Qt::red);                                                                         /**<Set the pen color to red for the drawing of the speed value text*/
        painter.setPen(redPen);                                                                       /**<Set the pen for drawing the speed value text*/
        painter.drawText(QRect(logoX, logoY, iconWidth, iconHeight), Qt::AlignCenter, QChar(0xe628)); /**<Speedometer icon*/
        speedValueText = "No Signal";                                                                 /**<Speed value text if No Connection to the Server*/
        QFont boldLabelFont("Arial", 20, QFont::Normal);                                              /**<Create a bold version of the label font*/
        painter.setFont(boldLabelFont);                                                               /**<Set the font for drawing the speed value text*/
        painter.drawText(speedValueX - 17, speedValueY + 10, speedValueText);                         /**<Draw the speed value text*/
    }
}

/**
 * @brief Draws a speedometer needle on the canvas.
 *
 * This function draws a speedometer needle on the canvas using QPainter. It calculates the center coordinates of the canvas,
 * the radius of the circle to fit within the canvas, and the angle at which the needle should point. It then draws the center
 * circle and the needle on the canvas.
 *
 * @param void
 * @return void
 *
 * @note This function assumes that the canvas has already been initialized and that the speed variable has been set.
 * @note The scale factor for the needle can be adjusted as needed.
 * @note The width of the needle can be adjusted as needed.
 * @note The start and end angles for the markings can be adjusted as needed.
 * @note The radius of the center circle can be adjusted as needed.
 */
void Canvas::drawSpeedometerNeedle(void)
{
    int centerX = width() / 2 * 0.9;  /**<Calculate the center X-coordinate of the canvas*/
    int centerY = height() / 2 * 1.2; /**<Calculate the center Y-coordinate of the canvas*/

    /**<Calculate the radius of the circle to fit within the canvas*/
    int radius = qMin(width(), height()) * 0.55; /**<Adjust the scale factor for the needle as needed*/

    int startA = -37 * 16; /**<Start angle for the markings*/
    int endA = 217 * 16;   /**<End angle for the markings*/

    int circleRadius = 15; /**<Adjust the radius of the center circle as needed*/

    /**<Draw the center circle*/
    QPen circlePen;                                                                                          /**<Pen for drawing the center circle*/
    circlePen.setColor(Qt::white);                                                                           /**<Color of the center circle*/
    circlePen.setWidth(4);                                                                                   /**<Width of the center circle outline*/
    circlePen.setStyle(Qt::SolidLine);                                                                       /**<Style of the center circle outline*/
    painter.setPen(circlePen);                                                                               /**<Set the pen for drawing the center circle*/
    painter.setBrush(QBrush(Qt::red));                                                                       /**<Set the brush for drawing the center circle*/
    painter.drawEllipse(centerX - circleRadius, centerY - circleRadius, circleRadius * 2, circleRadius * 2); /**<Draw the center circle*/

    /**<Define the coordinates for the needle vertices*/
    qreal needleLength = radius - 45;               /**<Adjust the length of the needle as needed*/
    qreal needleWidth = 12;                         /**<Adjust the width of the needle as needed*/
    QVector<QPointF> needleVertices;                /**<Vector of needle vertices*/
    needleVertices << QPointF(0, needleLength);     /**<Top vertex of the needle*/
    needleVertices << QPointF(-needleWidth / 2, 0); /**<Bottom left vertex of the needle*/
    needleVertices << QPointF(needleWidth / 2, 0);  /**<Bottom right vertex of the needle*/

    /**<Calculate the needle angle -2.48 is the offset for the needle*/
    qreal needleValue = -static_cast<qreal>(speed);                                       /**<The value at which the needle should point (0 in this case)*/
    qreal zeroAngle = startA;                                                             /**<The angle at which the needle should point to the value 0*/
    qreal needleAngle = zeroAngle + (endA - zeroAngle) * (-2.48 - (needleValue / 240.0)); /**<Calculate the angle at which the needle should point*/

    painter.translate(centerX, centerY); /**<Translate the painter to the center of the canvas*/
    painter.rotate(needleAngle / 16.0);  /**<Rotate the painter to the needle angle*/

    painter.setPen(Qt::NoPen);                 /**<No outline*/
    painter.setBrush(QBrush(Qt::red));         /**<Red needle*/
    painter.drawConvexPolygon(needleVertices); /**<Draw the needle*/
}