#include "graphics_board.h"

#include <QPainter>

#include "graphics_car.h"
#include "graphics_road.h"
#include "graphics_spawner.h"


GraphicsBoard::GraphicsBoard(Board &board) : board(board) {
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            auto boardPos = QPoint(x, y);
            Board::Tile tile = board.getTile(x, y);
            if (tile == Board::Tile::ROAD_UP
                || tile == Board::Tile::ROAD_RIGHT
                || tile == Board::Tile::ROAD_DOWN
                || tile == Board::Tile::ROAD_LEFT) {
                GraphicsRoad *roadTile = new GraphicsRoad(board, boardPos);
                roadTile->setParentItem(this);
            }
            if (tile == Board::Tile::SPAWNER) {
                GraphicsSpawner *spawnerTile = new GraphicsSpawner(board, boardPos);
                spawnerTile->setParentItem(this);
            }
        }
    }
}

QRectF GraphicsBoard::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void GraphicsBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
}