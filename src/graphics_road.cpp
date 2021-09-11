#include "graphics_road.h"

#include <QColor>
#include <QPainter>

#include "consts.h"


qreal tile_to_rotation(Board::Tile tile) {
    switch (tile) {
        case Board::Tile::ROAD_UP:
            return 0;
        case Board::Tile::ROAD_RIGHT:
            return 90;
        case Board::Tile::ROAD_DOWN:
            return 180;
        case Board::Tile::ROAD_LEFT:
            return 270;
        default:
            return 0;
    }
}

GraphicsRoad::GraphicsRoad(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
    setPos(boardPos * TILE_SIZE);
    setRotation(tile_to_rotation(board.getTile(boardPos)));
}

QRectF GraphicsRoad::boundingRect() const {
    return QRectF(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}

void GraphicsRoad::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->translate(TILE_OFFSET, TILE_OFFSET);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(200, 200, 200));
    painter->drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    painter->setBrush(QColor(185, 185, 185));
    painter->drawPolygon(QPolygonF()
                                 << QPoint(TILE_SIZE * 0.50, TILE_SIZE * 0.25)
                                 << QPoint(TILE_SIZE * 0.33, TILE_SIZE * 0.75)
                                 << QPoint(TILE_SIZE * 0.66, TILE_SIZE * 0.75)
    );
}
