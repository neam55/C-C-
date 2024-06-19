#include"Controller.h"
#include <iostream>
#include "Lights.h"
#include <QDebug>
#include<ostream>

Controller::Controller(QObject *parent)
    : QObject(parent), cur_floor(1), cur_target(-1),
    is_target(FLOORS, false), current_state(FREE), cur_direction(STAY) {}

void Controller::set_new_target_cabin(int floor) {
    current_state = BUSY;
    is_target[floor - 1] = true;

    if (cur_target == -1) {
        cur_target = floor;
    }

    if (((cur_direction == UP) && (floor < cur_target) && (floor > cur_floor)) ||
        ((cur_direction == DOWN) && (floor > cur_target)) && (floor < cur_floor)) {
        emit set_target(floor, cur_direction);
    }
    else
    {
        next_target(floor);
        cur_direction = (cur_floor > cur_target) ? DOWN : UP;
        emit set_target(floor, cur_direction);
    }
}

void Controller::set_new_target_floor(int floor) {
    current_state = BUSY;
    is_target[floor - 1] = true;

    if (cur_target == -1) {
        cur_target = floor;
    }

    if (((cur_direction == UP) && (floor > cur_target)) || ((cur_direction == DOWN) && (floor < cur_target)))
    {
        cur_target = floor;
    }
    next_target(floor);
    cur_direction = (cur_floor > cur_target) ? DOWN : UP;
    emit set_target(floor, cur_direction);
}


void Controller::achieved_floor(int floor) {
    if (current_state != BUSY)
        return;

    cur_floor = floor;
    is_target[floor - 1] = false;

    if (cur_floor == cur_target) {
        cur_target = -1;
        find_new_target();
    }

    if (next_target(floor)) {
        cur_direction = (cur_floor > cur_target) ? DOWN : UP;

        emit set_target(floor, cur_direction);
    } else {
        current_state = FREE;
    }
}

void Controller::passed_floor(int floor) {
    cur_floor = floor;
    qDebug() << "Лифт проехал" << floor << "этаж.";
}

void Controller::find_new_target() {
    int state = false;

    if (cur_direction == UP) {
        for (int i = FLOORS; i >= 1 && !state; i--) {
            if (is_target[i - 1]) {
                state = true;
                cur_target = i;
            }
        }
        return;
    }

    for (int i = 1; i <= FLOORS && !state; i++) {
        if (is_target[i - 1]) {
            state = true;
            cur_target = i;
        }
    }
}

bool Controller::next_target(int &floor) {
    bool state = false;
    if (cur_target > cur_floor) {
        for (int i = cur_floor; i <= FLOORS && !state; i += 1) {
            if (is_target[i - 1]) {
                floor = i;
                state = true;
            }
        }
    } else {
        for (int i = cur_floor; i >= 1 && !state; i -= 1) {
            if (is_target[i - 1]) {
                floor = i;
                state = true;
            }
        }
    }
    return state;
}

