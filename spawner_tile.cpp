#include "spawner_tile.h"

#include <QGraphicsScene>
#include <QRandomGenerator>

#include "car.h"


SpawnerTile::SpawnerTile(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
}

void SpawnerTile::advance(int step) {
    if (!step)
        return;

    if (board.getCarsCount() < 10 && QRandomGenerator::global()->bounded(100) < 20) {
        board.increaseCarsCount();
        scene()->addItem(new Car(board, boardPos));
    }
}

QRectF SpawnerTile::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void SpawnerTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
}
