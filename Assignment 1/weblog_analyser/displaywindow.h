#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include<iostream>
#include "log_entry.h"
#include <stdlib.h>
#include <QFile>
#include <QDir>
#include<string.h>
#include<QTextStream>
using namespace std;
namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT
    log_entry log[10000];
    int count;
    string filename;
    QList <log_entry> list;

public:
    explicit DisplayWindow(QWidget *parent = 0);
    ~DisplayWindow();

    void display();

private:
    Ui::DisplayWindow *ui;
private slots:
void getname(string);
void on_pushButton_clicked();

public:
void parse_file();
};

#endif // DISPLAYWINDOW_H
