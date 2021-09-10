#ifndef EASY_RIDER_ROAD_TILE_H
#define EASY_RIDER_ROAD_TILE_H

#include <QGraphicsItem>


class RoadTile : public QGraphicsItem {
public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};


#endif //EASY_RIDER_ROAD_TILE_H
