#include "background.h"

#include <QPainter>

#include "car.h"
#include "road_tile.h"
#include "spawner_tile.h"


QRectF Background::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
}

Background::Background(Board &board) : board(board) {
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            auto boardPos = QPoint(x, y);
            Board::Tile tile = board.getTile(x, y);
            if (tile == Board::Tile::ROAD_UP
                || tile == Board::Tile::ROAD_RIGHT
                || tile == Board::Tile::ROAD_DOWN
                || tile == Board::Tile::ROAD_LEFT) {
                RoadTile *roadTile = new RoadTile(board, boardPos);
                roadTile->setParentItem(this);
            }
            if (tile == Board::Tile::SPAWNER) {
                SpawnerTile *spawnerTile = new SpawnerTile(board, boardPos);
                spawnerTile->setParentItem(this);
            }
        }
    }
}
