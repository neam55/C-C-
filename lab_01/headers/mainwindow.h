#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"handler.h"
#include<cstring>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    action_coef_t rotate_values();
    action_coef_t transition_values();
    action_coef_t scale_values();
    void draw();
    void message_display(const char *message);
    void error_handler(const error_t &rc);

private slots:
    void rotate_button_clicked();
    void transition_button_clicked();
    void scale_button_clicked();
    void read_button_clicked();
    void clear_button_clicked();
};

#endif // MAINWINDOW_H
