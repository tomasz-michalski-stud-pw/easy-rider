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

/**
 * Defines maximal number of cars that can be present on the board at the same time.
 */
const int CARS_COUNT = 15;

/**
 * Defines how likely it is that the car will be created after spawner attempts to do so. Setting to "1" will result in
 * almost all cars spawned in the same spawner (as it will always succeed).
 */
const float CAR_SPAWN_CHANCE = 0.2;

#endif //EASY_RIDER_CONSTS_H
