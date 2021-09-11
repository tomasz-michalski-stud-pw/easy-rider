#include "graphics_spawner.h"

#include <QGraphicsScene>
#include <QRandomGenerator>

#include "consts.h"
#include "graphics_car.h"


GraphicsSpawner::GraphicsSpawner(Board &board, QPoint boardPos) : board(board), boardPos(boardPos) {
}

void GraphicsSpawner::advance(int step) {
    if (!step)
        return;

    if (board.getCarsCount() < CARS_COUNT && QRandomGenerator::global()->generateDouble() < CAR_SPAWN_CHANCE) {
        board.increaseCarsCount();
        scene()->addItem(new GraphicsCar(board, boardPos));
    }
}

QRectF GraphicsSpawner::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void GraphicsSpawner::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
}
