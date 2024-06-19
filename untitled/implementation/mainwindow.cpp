#include<QDebug>
#include "mainwindow.h"
#include "design.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qDebug() << "Лифт начал работу!\n";

    for (int i = 0; i < ui->cabin_buttons.size(); ++i) {
        connect(ui->cabin_buttons[i], &QPushButton::pressed, this,
                [=, this]() {on_button_cabin_clicked(i + 1); });
    }

    for (int i = 0; i < ui->cabin_buttons.size(); ++i) {
        connect(ui->floor_buttons[i], &QPushButton::pressed, this,
                [=, this]() {on_button_floor_clicked(i + 1); });
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_cabin_clicked(int num) {
    qDebug() << "В лифте нажата кнопка" << num << "этажа.";
    lift.click_cabin(num);

}

void MainWindow::on_button_floor_clicked(int num) {
    qDebug() << "Лифт вызван на " << num << " этаж.";
    lift.click_floor(num);
}
