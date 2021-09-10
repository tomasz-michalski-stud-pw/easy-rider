#ifndef EASY_RIDER_CAR_H
#define EASY_RIDER_CAR_H

#include <QGraphicsItem>


class Car : public QGraphicsItem {
public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

};

#endif //EASY_RIDER_CAR_H
