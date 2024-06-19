#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Elevator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void on_button_cabin_clicked(int num);

private slots:
    void on_button_floor_clicked(int num);

private:
    Ui::MainWindow *ui;
    Elevator lift;
};
#endif // MAINWINDOW_H
