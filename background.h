#ifndef EASY_RIDER_BACKGROUND_H
#define EASY_RIDER_BACKGROUND_H

#include <QGraphicsItem>

#include "board.h"


class Background : public QGraphicsItem {
public:
    Background(Board &board);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    Board &board;
};

#endif //EASY_RIDER_BACKGROUND_H
