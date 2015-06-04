#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Mainwindow");
    dw = new DisplayWindow(this);
    this->setGeometry(400,300,381,191);
    connect(this,SIGNAL(filename(string)),dw,SLOT(getname(string)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_button1_clicked()
{
dw->show();
emit filename(ui->lineEdit->text().toStdString());
}

