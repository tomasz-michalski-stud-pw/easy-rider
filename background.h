#ifndef EASY_RIDER_BACKGROUND_H
#define EASY_RIDER_BACKGROUND_H

#include <QGraphicsItem>

#include "board.h"


/**
 * Graphic object responsible for displaying background based on the given Board.
 */
class Background : public QGraphicsItem {
public:
    /**
     * Creates Background object.
     *
     * @param board The Board which should be used as the source of data.
     */
    Background(Board &board);

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

#endif //EASY_RIDER_BACKGROUND_H
