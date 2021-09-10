#include "background.h"

#include <QPainter>


QRectF Background::boundingRect() const {
    const int size = 10000; // TODO: make it more reasonable
    return QRectF(-size, -size, 2 * size, 2 * size);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
}
