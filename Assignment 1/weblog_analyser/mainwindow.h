#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "displaywindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
DisplayWindow *dw;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_button1_clicked();
signals:
    void filename(string);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
