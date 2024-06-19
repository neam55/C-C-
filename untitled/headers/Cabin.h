#ifndef CABIN_H
#define CABIN_H
#include<QObject>
#include"Doors.h"
#include"Controller.h"
#include"Lights.h"
#include"defines.h"

class Cabin : public QObject {
    Q_OBJECT
    enum cabin_state { MOVE, WAIT, STOP };

public:
    explicit Cabin(QObject *parent = nullptr);

signals:
    void cabin_called();
    void cabin_crossing_floor(int floor, direction d);
    void cabin_reached_target(int floor);
    void cabin_stopped(int floor);
    void turn_on_the_lights();
    void turn_off_the_lights();

public slots:
    void cabin_move();
    void cabin_stopping();
    void cabin_call(int floor, direction dir);
    void light_switch_off();
    void light_switch_on();

private:
    int current_floor;
    int target;
    bool new_target;
    cabin_state current_state;
    direction current_direction;
    Doors doors;
    Lights lighting;
    QTimer crossing_floor_timer;
};


#endif // CABIN_H
