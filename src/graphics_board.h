#ifndef EASY_RIDER_GRAPHICS_BOARD_H
#define EASY_RIDER_GRAPHICS_BOARD_H

#include <QGraphicsItem>

#include "board.h"


/**
 * Graphic object responsible for displaying background based on the given Board.
 */
class GraphicsBoard : public QGraphicsItem {
public:
    /**
     * Creates GraphicsBoard object.
     *
     * @param board The Board which should be used as the source of data.
     */
    GraphicsBoard(Board &board);

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

private:
    Board &board;
};

#endif //EASY_RIDER_GRAPHICS_BOARD_H
