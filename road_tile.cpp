#include "road_tile.h"

#include <QPainter>


RoadTile::RoadTile(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
    setPos(boardPos * 100);
}

QRectF RoadTile::boundingRect() const {
    return QRectF(-50, -50, 100, 100);
}

void RoadTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::lightGray);
    painter->drawRect(-50, -50, 100, 100);
}
