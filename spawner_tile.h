#ifndef EASY_RIDER_SPAWNER_TILE_H
#define EASY_RIDER_SPAWNER_TILE_H

#include <QGraphicsItem>

#include "board.h"


/**
 * Graphic object responsible for creating new Car objects at its position, when needed.
 */
class SpawnerTile : public QGraphicsItem {
public:
    /**
     * Creates SpawnerTile object.
     *
     * @param board The Board which should be used as the source of data.
     * @param boardPos Position of the tile on the board.
     */
    SpawnerTile(Board &board, QPoint boardPos);

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
    QPoint boardPos;
};

#endif //EASY_RIDER_SPAWNER_TILE_H
