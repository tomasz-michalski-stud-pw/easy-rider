#ifndef EASY_RIDER_CAR_H
#define EASY_RIDER_CAR_H

#include <QGraphicsItem>

#include "board.h"


class Car : public QGraphicsItem {
public:
    enum Direction {
        UNKNOWN,
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    const Direction allDirections[4] = {UP, RIGHT, DOWN, LEFT};

    Car(Board &board, QPoint boardPos);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    Board &board;
    QPoint boardPos;
    Direction currentDirection = UNKNOWN;
};

#endif //EASY_RIDER_CAR_H
