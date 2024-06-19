#include"Cabin.h"

#include<QDebug>
#include<QString>
Cabin::Cabin(QObject *parent)
    : QObject(parent), current_floor(1), target(-1), new_target(false),
    current_state(STOP), current_direction(STAY) {
    crossing_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_called()), &doors, SLOT(start_closing()));
    QObject::connect(this, SIGNAL(cabin_reached_target(int)), this,
                     SLOT(cabin_stopping()));
    QObject::connect(this, SIGNAL(cabin_stopped(int)), &doors,
                     SLOT(start_openning()));
    QObject::connect(&doors, SIGNAL(closed_doors()), this, SLOT(cabin_move()));
    QObject::connect(&crossing_floor_timer, SIGNAL(timeout()), this,
                     SLOT(cabin_move()));
    QObject::connect(&doors, SIGNAL(closed_doors()), this, SLOT(light_switch_off()));
    QObject::connect(this, SIGNAL(cabin_stopped(int)), this, SLOT(light_switch_on()));
    QObject::connect(this, SIGNAL(turn_off_the_lights()), &lighting, SLOT(ligths_off()));
    QObject::connect(this, SIGNAL(turn_on_the_lights()), &lighting, SLOT(lights_on()));
}

void Cabin::cabin_move() {
    if (new_target && current_state == WAIT) {
        current_state = MOVE;

        if (current_floor == target) {
            emit cabin_reached_target(current_floor);
        } else {
            crossing_floor_timer.start(CROSSING_FLOOR);
        }

        return;
    }

    if (current_state == MOVE) {
        current_state = MOVE;

        current_floor += current_direction;

        if (current_floor == target) {
            emit cabin_reached_target(current_floor);
        } else {
            emit cabin_crossing_floor(current_floor, current_direction);
            crossing_floor_timer.start(CROSSING_FLOOR);
        }
    }
}

void Cabin::cabin_stopping() {
    if (current_state != MOVE)
        return;

    current_state = STOP;
    qDebug() << "Остановка на" << current_floor << "этаже.";
    emit cabin_stopped(current_floor);

}

void Cabin::cabin_call(int floor, direction dir) {
    if (current_state == STOP)
    {
        new_target = true;
        current_state = WAIT;
        target = floor;
        current_direction = dir;
        emit cabin_called();
    }
}


void Cabin::light_switch_off()
{
    if ((current_floor == target) && (current_state == STOP))
        emit turn_off_the_lights();

}

void Cabin::light_switch_on()
{
        emit turn_on_the_lights();
}
