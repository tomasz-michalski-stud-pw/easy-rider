#include "board.h"

#include <sstream>

std::map<char, Board::Tile> tiles_map{
        {'?', Board::Tile::UNKNOWN},
        {'^', Board::Tile::ROAD_UP},
        {'>', Board::Tile::ROAD_RIGHT},
        {'<', Board::Tile::ROAD_LEFT},
        {'v', Board::Tile::ROAD_DOWN},
        {'s', Board::Tile::SPAWNER},
        {'.', Board::Tile::EMPTY},
};

Board::Board(std::string str) {
    std::stringstream error;

    int counter = 0;
    for (const char &c : str) {
        if (c == '\r') {
            continue;
        }
        if (c == '\n') {
            if (counter > 0) {
                height++;
                if (width > 0) {
                    if (counter != width) {
                        error << "Line " << height << "has invalid number of characters, found " << counter
                              << " expected " << width;
                        throw std::invalid_argument(error.str());
                    }
                } else {
                    width = counter;
                }
                counter = 0;
            }
            continue;
        }
        tiles.push_back(tiles_map[c]);
        counter++;
    }

    if (width * height != tiles.size()) {
        error << "Something went wrong! With width=" << width << " and height=" << height << " expected "
              << width * height << " tiles, found " << tiles.size();
        throw std::invalid_argument(error.str());
    }
}

int Board::getHeight() {
    return height;
}

int Board::getWidth() {
    return width;
}

Board::Tile Board::getTile(int x, int y) {
    if (x >= 0 && y >= 0 && x < width && y < height) {
        return tiles[y * width + x];
    }
    return UNKNOWN;
}

Board::Tile Board::getTile(QPoint point) {
    return getTile(point.x(), point.y());
}

void Board::increaseCarsCount() {
    carsCount++;
}

void Board::decreaseCarsCount() {
    carsCount--;
}

int Board::getCarsCount() {
    return carsCount;
}


std::ostream &operator<<(std::ostream &out, const Board::Tile tile) {
    for (auto &i : tiles_map) {
        if (i.second == tile) {
            return out << i.first;
        }
    }
    return out << "?";
}
