#ifndef EASY_RIDER_BOARD_H
#define EASY_RIDER_BOARD_H

#include <QPoint>

#include <map>
#include <string>
#include <vector>


class Board {
public:
    enum Tile {
        UNKNOWN,
        EMPTY,
        ROAD_UP,
        ROAD_RIGHT,
        ROAD_DOWN,
        ROAD_LEFT,
        SPAWNER,
    };

    Board(std::string str);

    int getHeight();

    int getWidth();

    Tile getTile(int x, int y);

    Tile getTile(QPoint point);

    void increaseCarsCount();

    void decreaseCarsCount();

    int getCarsCount();

private:
    std::vector <Tile> tiles;
    int width = 0;
    int height = 0;
    int carsCount = 0;
};


std::ostream &operator<<(std::ostream &out, const Board::Tile tile);


#endif //EASY_RIDER_BOARD_H
