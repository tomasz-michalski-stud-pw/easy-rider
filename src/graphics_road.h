#ifndef EASY_RIDER_GRAPHICS_ROAD_H
#define EASY_RIDER_GRAPHICS_ROAD_H

#include <QGraphicsItem>

#include "board.h"


/**
 * Graphic object responsible for displaying single tile representing part of a road.
 */
class GraphicsRoad : public QGraphicsItem {
public:
    /**
     * Creates GraphicsRoad object.
     *
     * @param board The Board which should be used as the source of data.
     * @param boardPos Position of the tile on the board.
     */
    GraphicsRoad(Board &board, QPoint boardPos);

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

#endif //EASY_RIDER_GRAPHICS_ROAD_H
