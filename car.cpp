#include "car.h"

#include <QPainter>
#include <QRandomGenerator>

#include <set>


QRectF Car::boundingRect() const {
    return QRectF(-50, -50, 100, 100);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    qreal height = 90;
    qreal width = 50;

    painter->setBrush(Qt::red);
    painter->drawRoundedRect(-width / 2, -height / 2, width, height, 10, 10);

    painter->setBrush(Qt::yellow);
    painter->drawRoundedRect((-width / 2) - (12 / 2) + 12, -height / 2 + 5, 12, 6, 2, 2);
    painter->drawRoundedRect((width / 2) - (12 / 2) - 12, -height / 2 + 5, 12, 6, 2, 2);

    painter->drawPolygon(QPolygonF()
                                 << QPoint(-width / 2 + 6, -20)
                                 << QPoint(width / 2 - 6, -20)
                                 << QPoint(width / 2 - 10, -5)
                                 << QPoint(-width / 2 + 10, -5)
    );
    painter->drawPolygon(QPolygonF()
                                 << QPoint(width / 2 - 10, 20)
                                 << QPoint(-width / 2 + 10, 20)
                                 << QPoint(-width / 2 + 6, 35)
                                 << QPoint(width / 2 - 6, 35)
    );
}


Car::Direction direction_from_road_tile(Board::Tile tile) {
    switch (tile) {
        case Board::Tile::ROAD_UP:
            return Car::Direction::UP;
        case Board::Tile::ROAD_RIGHT:
            return Car::Direction::RIGHT;
        case Board::Tile::ROAD_DOWN:
            return Car::Direction::DOWN;
        case Board::Tile::ROAD_LEFT:
            return Car::Direction::LEFT;
        default:
            return Car::Direction::UNKNOWN;
    }
}


bool is_direction_opposite(Car::Direction a, Car::Direction b) {
    switch (a) {
        case Car::Direction::UP:
            return b == Car::Direction::DOWN;
        case Car::Direction::RIGHT:
            return b == Car::Direction::LEFT;
        case Car::Direction::DOWN:
            return b == Car::Direction::UP;
        case Car::Direction::LEFT:
            return b == Car::Direction::RIGHT;
        default:
            return false;
    }
}


QPoint direction_to_point(Car::Direction direction) {
    switch (direction) {
        case Car::Direction::UP:
            return QPoint(0, -1);
        case Car::Direction::RIGHT:
            return QPoint(1, 0);
        case Car::Direction::DOWN:
            return QPoint(0, 1);
        case Car::Direction::LEFT:
            return QPoint(-1, 0);
        default:
            return QPoint(0, 0);
    }
}


qreal direction_to_rotation(Car::Direction direction) {
    switch (direction) {
        case Car::Direction::UP:
            return 0;
        case Car::Direction::RIGHT:
            return 90;
        case Car::Direction::DOWN:
            return 180;
        case Car::Direction::LEFT:
            return 270;
        default:
            printf("WARNING: unknown direction\n");
            return QRandomGenerator::global()->bounded(12)*30;
    }
}


void Car::advance(int step) {
    if (!step)
        return;

    std::set <Direction> new_directions;

    // "pulling" to the new road tile nearby which will allow to travel further
    for (auto possible_direction : allDirections) {
        auto possible_tile = board.getTile(boardPos + direction_to_point(possible_direction));
        Car::Direction possible_tile_direction = direction_from_road_tile(possible_tile);
        if (possible_direction == possible_tile_direction
            && !is_direction_opposite(currentDirection, possible_direction)
            && possible_tile_direction != Car::Direction::UNKNOWN) {
            new_directions.insert(possible_direction);
        }
    }

    // "pushing" from the current road
    {
        Car::Direction tile_direction = direction_from_road_tile(board.getTile(boardPos));
        new_directions.insert(tile_direction);
    }

    if (new_directions.size() > 0) {
        // select random direction
        auto it = std::begin(new_directions);
        std::advance(it, QRandomGenerator::global()->bounded(new_directions.size()));
        currentDirection = *it;
    } else {
        currentDirection = UNKNOWN;
    }

    setRotation(direction_to_rotation(currentDirection));
    boardPos = boardPos + direction_to_point(currentDirection);
    setPos(boardPos * 100);
}


Car::Car(Board board) : board(board) {
    // TODO: make it random
    boardPos.setX(6);
    boardPos.setY(8);
    currentDirection = Direction::UP;
}
