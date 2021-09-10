#include "background.h"

#include <QPainter>


QRectF Background::boundingRect() const {
    const int size = 10000; // TODO: make it more reasonable
    return QRectF(-size, -size, 2 * size, 2 * size);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->translate(-50, -50);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(100, 100, 100, 500);
    painter->drawRect(100, 500, 500, 100);
}
