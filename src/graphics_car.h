#ifndef EASY_RIDER_GRAPHICS_CAR_H
#define EASY_RIDER_GRAPHICS_CAR_H

#include <QGraphicsItem>

#include "board.h"


class GraphicsCar : public QGraphicsItem {
public:
    /**
     * Defines in which directions car can be rotated.
     */
    enum Direction {
        UNKNOWN,
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    /**
     * Contains all valid values for directions.
     */
    const Direction allDirections[4] = {UP, RIGHT, DOWN, LEFT};

    /**
     * Creates GraphicsCar object.
     *
     * @param board
     * @param boardPos
     */
    GraphicsCar(Board &board, QPoint boardPos);

    /**
     * Used by Qt. Defines an area in which painting will take place.
     * @return
     */
    QRectF boundingRect() const override;

    /**
     * Used by Qt. Defines how the object should be painted.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    Board &board;
    QPoint currentBoardPos;
    Direction currentDirection = UNKNOWN;
    bool justChangedDirection = false;
    QColor color;
};

#endif //EASY_RIDER_GRAPHICS_CAR_H
