#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QtWidgets>
#include <QGraphicsItem>

#include <iostream>

#include "background.h"
#include "board.h"
#include "car.h"


// TODO: read from file?
const std::string board_str = R"(
.....R..............
.....R......R.......
RRRRRRRRRRRRRRRRRRRR
.....R......R.......
.....R......R.......
.....R......R.......
.....RRRRRRRRRRRRRRR
.....R..........R...
RRRRRR..........R...
.....R..........R...
)";


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Board board(board_str);

    std::cout << "Board: \n";
    for (int i = 0; i < board.getHeight(); i++) {
        for (int j = 0; j < board.getWidth(); j++) {
            std::cout << board.getTile(j, i);
        }
        std::cout << "\n";
    }

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
