#include"Lights.h"
Lights::Lights() : lighting(LIGHTS_OFF){}

void Lights::lights_on()
{
    if (lighting == LIGHTS_OFF)
    {
        lighting = LIGHTS_ON;
        qDebug() << "Свет включён.";
    }
}

void Lights::ligths_off()
{
        lighting = LIGHTS_OFF;
        qDebug() << "Свет выключен.";
}
