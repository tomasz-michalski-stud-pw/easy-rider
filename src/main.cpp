#include <QApplication>
#include <QColor>
#include <QPushButton>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QtWidgets>
#include <QGraphicsItem>

#include <iostream>

#include "board.h"
#include "consts.h"
#include "graphics_board.h"


/**
 * Defines string used to construct simulation board.
 */
const std::string board_str = R"(
......s................
......v^.....^.........
......v^.....^.........
......v^.....^.........
......v^.....^.........
.<<<<<<^<<<<<^<<<<<<<<s
s>>>>>v>>>>>>>>>>>>>>>.
......v^.....^.........
......v^.....^.........
......v^>>>>>^>>v>>>>>.
.<<<<<<^........v^.....
s>>>>>v>........v^.....
......v^........v^.....
......v^........v^.....
......v^........v^.....
.......s.........s.....
)";


/**
 * Main entrypoint for the application.
 */
int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Board board(board_str);

    QGraphicsScene scene;
    scene.setSceneRect(
            2 * TILE_SIZE + TILE_OFFSET, 2 * TILE_SIZE + TILE_OFFSET,
            (board.getWidth() - 4) * TILE_SIZE, (board.getHeight() - 4) * TILE_SIZE);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.addItem(new GraphicsBoard(board));

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Easy Rider"));
    view.setBackgroundBrush(QColor(0, 136, 43));
    view.scale(0.5, 0.5);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(SLEEP);

    return app.exec();
}
