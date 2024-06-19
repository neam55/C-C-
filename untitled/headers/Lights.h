#ifndef LIGHTS_H
#define LIGHTS_H
#include<QObject>
#include<QDebug>
#include<QTimer>
#include"defines.h"

class Lights : public QObject
{
    Q_OBJECT
    enum light_state {LIGHTS_ON, LIGHTS_OFF};

public:
    Lights();
    ~Lights() = default;

public slots:
    void lights_on();
    void ligths_off();

private:
    light_state lighting;
};


#endif // LIGHTS_H
