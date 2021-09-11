#ifndef EASY_RIDER_SPAWNER_TILE_H
#define EASY_RIDER_SPAWNER_TILE_H

#include <QGraphicsItem>

#include "board.h"


class SpawnerTile : public QGraphicsItem {
public:
    SpawnerTile(Board &board, QPoint boardPos);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    Board &board;
    QPoint boardPos;
};

#endif //EASY_RIDER_SPAWNER_TILE_H
