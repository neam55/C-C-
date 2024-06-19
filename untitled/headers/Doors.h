#ifndef DOORS_H
#define DOORS_H
#include<QObject>
#include<QTimer>
#include"defines.h"

class Doors : public QObject {
    Q_OBJECT
    enum doors_state { OPENNING, OPENED, CLOSING, CLOSED };

public:
    explicit Doors(QObject *parent = nullptr);

signals:
    void closed_doors();
    void opened_doors();

public slots:
    void start_openning();
    void start_closing();

private slots:
    void open();
    void close();

private:
    doors_state current_state;
    QTimer doors_open_timer;
    QTimer doors_close_timer;
    QTimer doors_stay_open_timer;
};


#endif // DOORS_H
