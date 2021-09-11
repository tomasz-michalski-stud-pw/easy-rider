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
#include "road_tile.h"


// TODO: read from file?
const std::string board_str = R"(
.....v^.....^.......
.....v^.....^.......
<<<<<<^<<<<<^<<<<<<<
>>>>>v>>>>>>>>>>>>>>
.....v^.....^.......
.....v^.....^.......
.....v^>>>>>^>>v>>>>
<<<<<<^........v^...
>>>>>v^........v^...
.....v^........v^...
)";


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Board board(board_str);

    std::cout << "Board: \n";
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            std::cout << board.getTile(x, y);
        }
        std::cout << "\n";
    }

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 2100, 1100);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Background background;
    background.setPos(0, 0);
    scene.addItem(&background);

    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            Board::Tile tile = board.getTile(x, y);
            if (tile == Board::Tile::ROAD_UP
                || tile == Board::Tile::ROAD_RIGHT
                || tile == Board::Tile::ROAD_DOWN
                || tile == Board::Tile::ROAD_LEFT) {
                RoadTile *roadTile = new RoadTile();
                roadTile->setParentItem(&background);
                roadTile->setPos(x * 100, y * 100);
            }
        }
    }


    Car car(board);
    scene.addItem(&car);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Easy Rider"));
    view.resize(1600, 800);
    view.scale(0.5, 0.5);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 5);

    return app.exec();
}
