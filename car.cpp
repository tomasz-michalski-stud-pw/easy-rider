#include "car.h"

#include <QPainter>


QRectF Car::boundingRect() const {
    return QRectF(-50, -50, 100, 100);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    qreal height = 90;
    qreal width = 50;

    painter->setBrush(Qt::red);
    painter->drawRoundedRect(-width / 2, -height / 2, width, height, 10, 10);

    painter->setBrush(Qt::yellow);
    painter->drawRoundedRect((-width / 2) - (12 / 2) + 12, -height / 2 + 5, 12, 6, 2, 2);
    painter->drawRoundedRect((width / 2) - (12 / 2) - 12, -height / 2 + 5, 12, 6, 2, 2);

    painter->drawPolygon(QPolygonF()
                                 << QPoint(-width / 2 + 6, -20)
                                 << QPoint(width / 2 - 6, -20)
                                 << QPoint(width / 2 - 10, -5)
                                 << QPoint(-width / 2 + 10, -5)
    );
    painter->drawPolygon(QPolygonF()
                                 << QPoint(width / 2 - 10, 20)
                                 << QPoint(-width / 2 + 10, 20)
                                 << QPoint(-width / 2 + 6, 35)
                                 << QPoint(width / 2 - 6, 35)
    );
}


void Car::advance(int step) {
    if (!step)
        return;
}
