#include"Doors.h"
#include <QDebug>

Doors::Doors(QObject *parent) : QObject(parent), current_state(CLOSED) {
    doors_stay_open_timer.setInterval(WAIT_TIME);
    doors_stay_open_timer.setSingleShot(true);

    doors_open_timer.setSingleShot(true);
    doors_close_timer.setSingleShot(true);

    QObject::connect(&doors_open_timer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&doors_close_timer, SIGNAL(timeout()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(opened_doors()), &doors_stay_open_timer,
                     SLOT(start()));
    QObject::connect(&doors_stay_open_timer, SIGNAL(timeout()), this,
                     SLOT(start_closing()));
}

void Doors::start_openning() {
    if (current_state != CLOSED && current_state != CLOSING)
        return;

    qDebug() << "Двери открываются.";
    if (current_state == CLOSED) {
        current_state = OPENNING;
        doors_open_timer.start(DOORS_TIME);
    } else {
        current_state = OPENNING;
        int t = doors_close_timer.remainingTime();
        doors_close_timer.stop();
        doors_open_timer.start(DOORS_TIME - t);
    }
}

void Doors::start_closing() {
    if (current_state != OPENED && current_state != CLOSED)
        return;

    if (current_state == CLOSED) {
        emit closed_doors();
    } else {
        current_state = CLOSING;
        qDebug() << "Двери закрываются.";
        doors_close_timer.start(DOORS_TIME);
    }
}

void Doors::open() {
    if (current_state != OPENNING)
        return;

    current_state = OPENED;
    qDebug() << "Двери открыты!";
    emit opened_doors();
}

void Doors::close() {
    if (current_state != CLOSING)
        return;

    current_state = CLOSED;
    qDebug() << "Двери закрыты.";
    emit closed_doors();
}
