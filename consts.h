#ifndef EASY_RIDER_CONSTS_H
#define EASY_RIDER_CONSTS_H


/**
 * Defines width and height of the painted tile.
 */
const int TILE_SIZE = 100;

/**
 * Defines how much the painted tile is moved compared to the coordinates used by logic.
 */
const int TILE_OFFSET = (-TILE_SIZE / 2);

/**
 * Defines how many milliseconds should pass between simulation ticks.
 */
const int SLEEP = 1000 / 5;

#endif //EASY_RIDER_CONSTS_H
