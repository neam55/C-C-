#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, ui->graphicsView->width() - 1, ui->graphicsView->width() - 2, parent);
    ui->graphicsView->setScene(scene);

    connect(ui->scale_button, &QPushButton::released, this, &MainWindow::scale_button_clicked);
    connect(ui->transition_button, &QPushButton::released, this, &MainWindow::transition_button_clicked);
    connect(ui->rotate_button, &QPushButton::released, this, &MainWindow::rotate_button_clicked);
    connect(ui->read_obj_button, &QPushButton::released, this, &MainWindow::read_button_clicked);
    connect(ui->clear_scene_button, &QPushButton::released, this, &MainWindow::clear_button_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

action_coef_t MainWindow::rotate_values()
{
    return {ui->x_angle_spinbox->value(), ui->y_angle_spinbox->value(), ui->z_angle_spinbox->value()};
}

action_coef_t MainWindow::transition_values()
{
    return {ui->Dx_spinbox->value(), ui->Dy_spinbox->value(), ui->Dz_spinbox->value()};
}

action_coef_t MainWindow::scale_values()
{
        return {ui->Kx_spinbox->value(), ui->Ky_spinbox->value(), ui->Kz_spinbox->value()};
}

void MainWindow::scale_button_clicked()
{
    comand_t command;
    command.action = ACTION_SCALE;
    command.scene = {scene, ui->graphicsView->height(), ui->graphicsView->width()};
    command.scale = scale_values();
    error_t rc = command_handler(command);
    draw();
    error_handler(rc);
}

void MainWindow::rotate_button_clicked()
{
    comand_t command;
    command.action = ACTION_ROTATE;
    command.scene = {scene, ui->graphicsView->height(), ui->graphicsView->width()};
    command.rotate = rotate_values();
    error_t rc = command_handler(command);
    draw();
    error_handler(rc);
}

void MainWindow::transition_button_clicked()
{
    comand_t command;
    command.action = ACTION_TRANSITION;
    command.scene = {scene, ui->graphicsView->height(), ui->graphicsView->width()};
    command.transition = transition_values();
    error_t rc = command_handler(command);
    draw();
    error_handler(rc);
}

void MainWindow::draw()
{
    comand_t command;
    command.action = ACTION_DRAW;
    command.scene = {scene, ui->graphicsView->height(), ui->graphicsView->width()};
    error_t rc = command_handler(command);
    error_handler(rc);
}

void MainWindow::clear_button_clicked()
{
    comand_t command;
    command.action = ACTION_CLEAR_SCENE;
    command.scene = {scene, ui->graphicsView->height(), ui->graphicsView->width()};
    error_t rc = command_handler(command);
    error_handler(rc);
    command.action = ACTION_FREE_OBJ;
    if (rc == SUCCESS)
        rc = command_handler(command);
        error_handler(rc);

}

void MainWindow::read_button_clicked()
{
    comand_t command;
    command.action = ACTION_READ;
    command.scene = { scene, ui->graphicsView->height(), ui->graphicsView->width() };
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Object"), "../lab_01/test", tr("Object files (*.txt *.obj)"));
    std::string tmp = fileName.toStdString();
    command.filename = (char *)tmp.c_str();
    error_t rc = command_handler(command);
    draw();
    error_handler(rc);
}

void MainWindow::message_display(const char *message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::error_handler(const error_t &rc)
{
    if (rc != SUCCESS)
        message_display(error_prompt(rc));
}

