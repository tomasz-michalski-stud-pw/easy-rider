#ifndef EASY_RIDER_BOARD_H
#define EASY_RIDER_BOARD_H

#include <QPoint>

#include <map>
#include <string>
#include <vector>


/**
 * Logic object containing simulation parameters and data, most importantly about board tiles.
 */
class Board {
public:
    /**
     * Defines possible tile types.
     */
    enum Tile {
        UNKNOWN,
        EMPTY,
        ROAD_UP,
        ROAD_RIGHT,
        ROAD_DOWN,
        ROAD_LEFT,
        SPAWNER,
    };

    /**
     * Creates Board object.
     *
     * @param str The string describing tiles which should be used to initialize simulation board.
     */
    Board(std::string str);

    /**
     * Returns board height.
     *
     * @return number of tiles in every column of the board.
     */
    int getHeight();

    /**
     * Returns board width.
     *
     * @return number of tiles in every row of the board.
     */
    int getWidth();

    /**
     * Returns type of the tile present at given coordinates.
     *
     * @param x the x coordinate for tile to be returned
     * @param y the x coordinate for tile to be returned
     * @return the tile type
     */
    Tile getTile(int x, int y);


    /**
     * Returns type of the tile present at given coordinates.
     *
     * @param point coordinates for tile to be returned
     * @return the tile type
     */
    Tile getTile(QPoint point);

    /**
     * Increments cars counter.
     */
    void increaseCarsCount();

    /**
     * Decrements cars counter.
     */
    void decreaseCarsCount();

    /**
     * Returns how mane cars are present on the board
     *
     * @return value of the cars counter
     */
    int getCarsCount();

    /**
     * Marks given tile as locked, to prevent multiple entities standing on the same tile.
     *
     * @param point coordinates of the tile which should be locked
     * @return true if locking was successful, false otherwise
     */
    bool lockTile(QPoint point);

    /**
     * Marks given tile as unlocked, to allow other entity standing on it.
     *
     * @param point coordinates of the tile which should be unlocked
     */
    void unlockTile(QPoint point);

private:
    std::vector <Tile> tiles;
    int width = 0;
    int height = 0;
    int carsCount = 0;
    std::vector <QPoint> tilesLocks;
};


std::ostream &operator<<(std::ostream &out, const Board::Tile tile);


#endif //EASY_RIDER_BOARD_H
