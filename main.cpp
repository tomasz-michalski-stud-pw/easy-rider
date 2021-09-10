#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QtWidgets>
#include <QGraphicsItem>


class Mouse : public QGraphicsItem {
public:
    Mouse();

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
};


static constexpr int MouseCount = 7;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < MouseCount; ++i) {
        Mouse *mouse = new Mouse;
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200,
                      ::cos((i * 6.28) / MouseCount) * 200);
        scene.addItem(mouse);
    }

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Easy Rider"));
    view.resize(1200, 900);
    view.scale(10, 10);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 150);

    return app.exec();
}

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle) {
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Mouse::Mouse() : color(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256)) {
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}

QRectF Mouse::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Mouse::shape() const {
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
}

void Mouse::advance(int step) {
    if (!step)
        return;

    // Don't move too far away
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
    }

    // Try not to crash with any other mice
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                                     << mapToScene(0, 0)
                                                                     << mapToScene(-30, -50)
                                                                     << mapToScene(30, -50));

    for (const QGraphicsItem *item : dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
        }
    }

    // Add some random movement
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }

    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
