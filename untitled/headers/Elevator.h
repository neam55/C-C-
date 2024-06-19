#ifndef ELEVATOR_H
#define ELEVATOR_H
#include<QObject>
#include<QTextEdit>
#include"Controller.h"
#include"Cabin.h"
#include"defines.h"
class Elevator : public QObject {
    Q_OBJECT

public:
    Elevator();
    void click_floor(int floor);
    void click_cabin(int floor);

private:
    Controller control_panel;
    Cabin cabin;
};


#endif // ELEVATOR_H
