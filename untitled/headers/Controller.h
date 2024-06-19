#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include "defines.h"

class Controller : public QObject {
    Q_OBJECT
    enum panel_state { FREE, BUSY };

public:
    explicit Controller(QObject *parent = nullptr);
    void set_new_target_floor(int floor);
    void set_new_target_cabin(int floor);

signals:
    void set_target(int floor, direction dir);
    void target_changed(int floor);

public slots:
    void achieved_floor(int floor);
    void passed_floor(int floor);

private:
    int cur_floor;
    int cur_target = -1;

    QVector<bool> is_target;
    panel_state current_state;
    direction cur_direction;
    bool next_target(int &floor);
    void find_new_target();
};


#endif // CONTROLLER_H
