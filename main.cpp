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
#include "spawner_tile.h"


// TODO: read from file?
const std::string board_str = R"(
......s...............
......v^.....^........
......v^.....^........
.<<<<<<^<<<<<^<<<<<<<s
s>>>>>v>>>>>>>>>>>>>>.
......v^.....^........
......v^.....^........
......v^>>>>>^>>v>>>>.
.<<<<<<^........v^....
s>>>>>v^........v^....
......v^........v^....
.......s.........s....
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
            auto boardPos = QPoint(x, y);
            Board::Tile tile = board.getTile(x, y);
            if (tile == Board::Tile::ROAD_UP
                || tile == Board::Tile::ROAD_RIGHT
                || tile == Board::Tile::ROAD_DOWN
                || tile == Board::Tile::ROAD_LEFT) {
                RoadTile *roadTile = new RoadTile(board, boardPos);
                roadTile->setParentItem(&background);
            }
            if (tile == Board::Tile::SPAWNER) {
                SpawnerTile *spawnerTile = new SpawnerTile(board, boardPos);
                spawnerTile->setParentItem(&background);
            }
        }
    }

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
