#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtGlobal>
#include <QLabel>
#include <math.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QPushButton *Arr[23], *click;
    int x_co,y_co,k,count,ans, numbers[25],high1,high2;
    float probability;
    bool flag;
    void Clear();
    QLabel *label1,*label2,*label3;
private slots:
     void generate();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
