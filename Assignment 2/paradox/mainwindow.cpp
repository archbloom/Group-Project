#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

   ui->setupUi(this);
   setWindowTitle("Birthday Paradox");
   count = 0;
   // Creating UI of 25 buttons
   x_co = 300, y_co = 50,k=0;
   for(int i=0;i<5;i++)
   {
       x_co = 300;
       for(int j=0;j<5;j++)
       {
           if(k<23)
           {
            Arr[k] = new QPushButton(this);
            Arr[k]->setGeometry(x_co,y_co,50,50);
            x_co +=50;
            k++;
           }
       }
       y_co +=50;
   }
   ans = 0;

   //Calculate probability of same birthdate for group of 25 people
   probability = 364;
   probability /= 365;
   probability = (float)pow(probability,253); //300 is ((n)*(n-1)/2) for n=25, this is taken as nC2 because these are the no. of distinct pairs of birthdays for n people
   probability = 1 - probability; //we take complement of the above value because it indicates at least one pair sharing the same birthday

   // Creating Labels to display results

   label1 = new QLabel(this);
   label1->setGeometry(600,125,200,40);

   label2 = new QLabel(this);
   label2->setGeometry(600,175,200,40);

   label3 = new QLabel(this);
   label3->setGeometry(600,200,200,40);
   label3->setText("No. of trials = "+QString::number(count));

   label1->setText("Expected probability = "+QString::number(probability));

   click = new QPushButton(this);
   click->setGeometry(375,350,100,50);
   click->setText("Generate!");
   connect(click,SIGNAL(clicked()),this,SLOT(generate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Clear()
{
    for(int i=0;i<23;i++)
    {
        Arr[i]->setEnabled(true);
    }
}

void MainWindow::generate()
{
    Clear();
    flag = false;
    count++;
    srand(time(NULL));
    for(int i=0;i<23;i++)
    {
        int x = (rand()%365 +1);
        numbers[i] = x;
        Arr[i]->setText(QString::number(x));
    }
    for(int i=0;i<23;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(numbers[i]==numbers[j])
            {
                flag = true;
                Arr[i]->setEnabled(false);
                Arr[i]->setText(QString::number(numbers[i]));
                Arr[j]->setEnabled(false);
                Arr[j]->setText(QString::number(numbers[j]));
            }
        }
    }
    if(flag)
    {
        ans++;
    }
    label2->setText("Actual probability = "+QString::number((float)ans/count));
    label3->setText("No. of trials = "+QString::number(count));
}
