#ifndef EASY_RIDER_BACKGROUND_H
#define EASY_RIDER_BACKGROUND_H

#include <QGraphicsItem>


class Background : public QGraphicsItem {
public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif //EASY_RIDER_BACKGROUND_H
