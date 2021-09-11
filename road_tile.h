#ifndef EASY_RIDER_ROAD_TILE_H
#define EASY_RIDER_ROAD_TILE_H

#include <QGraphicsItem>

#include "board.h"


/**
 * Graphic object responsible for displaying single tile representing part of a road.
 */
class RoadTile : public QGraphicsItem {
public:
    /**
     * Creates RoadTile object.
     *
     * @param board The Board which should be used as the source of data.
     * @param boardPos Position of the tile on the board.
     */
    RoadTile(Board &board, QPoint boardPos);

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
    Board &board;
    QPoint boardPos;
};

#endif //EASY_RIDER_ROAD_TILE_H
