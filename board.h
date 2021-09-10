#ifndef EASY_RIDER_BOARD_H
#define EASY_RIDER_BOARD_H

#include <map>
#include <string>
#include <vector>


class Board {
public:
    enum Tile {
        UNKNOWN,
        EMPTY,
        ROAD,
    };

    Board(std::string str);

    int getHeight();

    int getWidth();

    Tile getTile(int x, int y);

private:
    std::vector <Tile> tiles;
    int width = 0;
    int height = 0;
};


std::ostream &operator<<(std::ostream &out, const Board::Tile tile);


#endif //EASY_RIDER_BOARD_H
