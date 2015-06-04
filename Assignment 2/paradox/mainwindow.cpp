#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    former = 0;
    count = 0;
    ans = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Create(int x)
{
    int k=0;
    int x_co,y_co = 30;
    if(x <=30)
    {
        x_co = 45;
        for(int i=0;i<x;i++)
        {
            grid[k] = new QPushButton(ui->centralWidget);
            grid[k]->setGeometry(x_co,y_co,30,30);
            grid[k]->setVisible(true);
            k++;
            x_co+= 30;
        }
    }
    else
    {
        for(int i=0;i<((x/30));i++)
        {
            x_co = 45;
            for(int j=0;j<30;j++)
            {
                grid[k] = new QPushButton(ui->centralWidget);
                grid[k]->setGeometry(x_co,y_co,30,30);
                grid[k]->setVisible(true);
                k++;
                x_co+= 30;
            }
            y_co += 30;
        }
        x_co = 45;
        for(int j=0;j<(x%30);j++)
        {
            grid[k] = new QPushButton(ui->centralWidget);
            grid[k]->setGeometry(x_co,y_co,30,30);
            grid[k]->setVisible(true);
            k++;
            x_co+= 30;
        }
    }
}

void MainWindow::Clear()
{
    for(int i=0;i<former;i++)
    {
        grid[i]->setEnabled(true);
    }
}


void MainWindow::on_pushButton_clicked()
{
    int x = ui->lineEdit->text().toInt();
    for(int i=0;i<former;i++)
    {
        grid[i]->close();
    }
    Create(x);
    former = x;
    ans = 0;
    count = 0;
    probability = 364;
    probability /= 365;
    int power = (former*(former-1))/2;
    probability = (float)pow(probability,power);
    probability = 1 - probability;
    ui->label->setText("Expected probability = "+QString::number(probability));
    ui->label_2->setText("");
    ui->label_3->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    Clear();
    flag = false;
    count++;
    srand(time(NULL));
    for(int i=0;i<former;i++)
    {
        int x = (rand()%365 +1);
        numbers[i] = x;
        grid[i]->setText(QString::number(x));
    }
    for(int i=0;i<former;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(numbers[i]==numbers[j])
            {
                flag = true;
                grid[i]->setEnabled(false);
                grid[i]->setText(QString::number(numbers[i]));
                grid[j]->setEnabled(false);
                grid[j]->setText(QString::number(numbers[j]));
            }
        }
    }
    if(flag)
    {
        ans++;
    }
    ui->label_2->setText("Actual probability = "+QString::number((float)ans/count));
    ui->label_3->setText("No. of trials = "+QString::number(count));
}
