#ifndef EASY_RIDER_ROAD_TILE_H
#define EASY_RIDER_ROAD_TILE_H

#include <QGraphicsItem>

#include "board.h"


class RoadTile : public QGraphicsItem {
public:
    RoadTile(Board &board, QPoint boardPos);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    Board &board;
    QPoint boardPos;
};

#endif //EASY_RIDER_ROAD_TILE_H
