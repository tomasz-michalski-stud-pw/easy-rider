#include "graphics_road.h"

#include <QPainter>

#include "consts.h"


GraphicsRoad::GraphicsRoad(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
    setPos(boardPos * TILE_SIZE);
}

QRectF GraphicsRoad::boundingRect() const {
    return QRectF(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}

void GraphicsRoad::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}
