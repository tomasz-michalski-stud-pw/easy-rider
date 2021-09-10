#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QtWidgets>
#include <QGraphicsItem>
#include <sstream>

#include "background.h"
#include "car.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1500, 700);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Background background;
    background.setPos(0, 0);
    scene.addItem(&background);

    Car car;
    car.setPos(100, 100);
    scene.addItem(&car);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Easy Rider"));
    view.resize(1600, 800);
    view.scale(1, 1);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 5);

    return app.exec();
}
