#include "graphics_car.h"

#include <QGraphicsItemAnimation>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimeLine>

#include <set>

#include "consts.h"


GraphicsCar::GraphicsCar(Board &board, QPoint boardPos) : board(board), currentBoardPos(boardPos) {
    hide(); // hide car until first move because it may be initially blocked at spawn point
    advance(1);
}


QRectF GraphicsCar::boundingRect() const {
    return QRectF(TILE_OFFSET, TILE_OFFSET, TILE_SIZE, TILE_SIZE);
}

void GraphicsCar::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
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


GraphicsCar::Direction direction_from_road_tile(Board::Tile tile) {
    switch (tile) {
        case Board::Tile::ROAD_UP:
            return GraphicsCar::Direction::UP;
        case Board::Tile::ROAD_RIGHT:
            return GraphicsCar::Direction::RIGHT;
        case Board::Tile::ROAD_DOWN:
            return GraphicsCar::Direction::DOWN;
        case Board::Tile::ROAD_LEFT:
            return GraphicsCar::Direction::LEFT;
        default:
            return GraphicsCar::Direction::UNKNOWN;
    }
}


bool is_direction_opposite(GraphicsCar::Direction a, GraphicsCar::Direction b) {
    switch (a) {
        case GraphicsCar::Direction::UP:
            return b == GraphicsCar::Direction::DOWN;
        case GraphicsCar::Direction::RIGHT:
            return b == GraphicsCar::Direction::LEFT;
        case GraphicsCar::Direction::DOWN:
            return b == GraphicsCar::Direction::UP;
        case GraphicsCar::Direction::LEFT:
            return b == GraphicsCar::Direction::RIGHT;
        default:
            return false;
    }
}


QPoint direction_to_point(GraphicsCar::Direction direction) {
    switch (direction) {
        case GraphicsCar::Direction::UP:
            return QPoint(0, -1);
        case GraphicsCar::Direction::RIGHT:
            return QPoint(1, 0);
        case GraphicsCar::Direction::DOWN:
            return QPoint(0, 1);
        case GraphicsCar::Direction::LEFT:
            return QPoint(-1, 0);
        default:
            return QPoint(0, 0);
    }
}


qreal direction_to_rotation(GraphicsCar::Direction direction) {
    switch (direction) {
        case GraphicsCar::Direction::UP:
            return 360;
        case GraphicsCar::Direction::RIGHT:
            return 90;
        case GraphicsCar::Direction::DOWN:
            return 180;
        case GraphicsCar::Direction::LEFT:
            return 270;
        default:
            return QRandomGenerator::global()->bounded(12) * 30;
    }
}

qreal direction_to_new_rotation(GraphicsCar::Direction oldDirection, GraphicsCar::Direction newDirection) {
    qreal new_angle = direction_to_rotation(newDirection);
    qreal difference = new_angle - direction_to_rotation(oldDirection);
    if (difference > 180) {
        new_angle -= 360;
    }
    if (difference < -180) {
        new_angle += 360;
    }
    return new_angle;
}


void GraphicsCar::advance(int step) {
    if (!step)
        return;

    auto oldBoardPos = currentBoardPos;
    auto oldDirection = currentDirection;

    if (!justChangedDirection) {
        std::set <Direction> new_directions;

        // "pulling" to the new road tile nearby which will allow to travel further
        for (auto possible_direction : allDirections) {
            auto possible_tile = board.getTile(currentBoardPos + direction_to_point(possible_direction));
            GraphicsCar::Direction possible_tile_direction = direction_from_road_tile(possible_tile);
            if (possible_direction == possible_tile_direction
                && !is_direction_opposite(currentDirection, possible_direction)
                && possible_tile_direction != GraphicsCar::Direction::UNKNOWN) {
                new_directions.insert(possible_direction);
            }
        }

        // "pushing" from the current road
        {
            GraphicsCar::Direction possible_direction = direction_from_road_tile(board.getTile(currentBoardPos));
            auto possible_tile = board.getTile(currentBoardPos + direction_to_point(possible_direction));
            GraphicsCar::Direction possible_tile_direction = direction_from_road_tile(possible_tile);
            if (possible_tile_direction != GraphicsCar::Direction::UNKNOWN) {
                new_directions.insert(possible_direction);
            }
        }

        if (new_directions.size() > 0) {
            // select random direction
            auto it = std::begin(new_directions);
            std::advance(it, QRandomGenerator::global()->bounded(new_directions.size()));
            currentDirection = *it;
        } else {
            // car is stuck, despawn it
            hide();
            board.unlockTile(currentBoardPos);
            scene()->removeItem(this);
            board.decreaseCarsCount();
        }
    }
    if (oldDirection == UNKNOWN) {
        oldDirection = currentDirection;
    }

    if (oldDirection == currentDirection) {
        justChangedDirection = false;
        auto newBoardPos = currentBoardPos + direction_to_point(currentDirection);
        if (board.lockTile(newBoardPos)) {
            show(); // freshly spawned cars are hidden
            board.unlockTile(currentBoardPos);
            currentBoardPos = newBoardPos;
        }
    } else {
        justChangedDirection = true;
    }

    QTimeLine *timer = new QTimeLine(SLEEP);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(this);
    animation->setTimeLine(timer);
    animation->setPosAt(0, oldBoardPos * TILE_SIZE);
    animation->setPosAt(1, currentBoardPos * TILE_SIZE);
    animation->setRotationAt(0, direction_to_rotation(oldDirection));
    animation->setRotationAt(1, direction_to_new_rotation(oldDirection, currentDirection));
    timer->start();
}
