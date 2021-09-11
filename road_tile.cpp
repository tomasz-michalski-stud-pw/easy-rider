#include "road_tile.h"

#include <QPainter>

#include "consts.h"


RoadTile::RoadTile(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
    setPos(boardPos * TILE_SIZE);
}

QRectF RoadTile::boundingRect() const {
    return QRectF(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}

void RoadTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}
