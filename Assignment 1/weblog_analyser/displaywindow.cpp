#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Displaywindow");

}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}
void DisplayWindow::getname(string f)
{
filename = f;
std::cout<<"file name = "<<filename<<endl;
parse_file();
}
void DisplayWindow::parse_file()
{

    QString homePath = QDir::homePath();
   // std::cout<<homePath.toStdString();
//    ui->lineEdit->setText(homePath);
    QString path = ("python "+homePath+"/parser.py "+QString::fromStdString(filename));
    std::cout<<path.toStdString();
    system(path.toStdString().c_str());

    display();

}
void DisplayWindow::display()
{
    QString homePath = QDir::homePath();
    QFile file(homePath+"/test.txt");
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    QList< QStringList > lists;
    QString line;
    do {
        line = in.readLine();
        lists << line.split(",");
    } while (!line.isNull());
    file.close();
    std::cout<<"\n list size"<<lists.size()<<endl;
    std::cout<<"\n list size"<<lists[0].size()<<endl;
    // Set the table size (assuming the rows are all the same length).
    ui->tableWidget->setRowCount( lists.size() );
    ui->tableWidget->setAlternatingRowColors(true);


    for(int i=0;i<lists.size();i++)
    {
        if(lists[i].size()==9)
        {
       ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(lists[i][0]));
       ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(lists[i][1]));
       ui->tableWidget->setItem(i-1,2,new QTableWidgetItem(lists[i][2]));
       ui->tableWidget->setItem(i-1,3,new QTableWidgetItem(lists[i][3]));
       ui->tableWidget->setItem(i-1,4,new QTableWidgetItem(lists[i][4]));
       ui->tableWidget->setItem(i-1,5,new QTableWidgetItem(lists[i][5]));
       ui->tableWidget->setItem(i-1,6,new QTableWidgetItem(lists[i][6]));
       ui->tableWidget->setItem(i-1,7,new QTableWidgetItem(lists[i][7]));
       ui->tableWidget->setItem(i-1,8,new QTableWidgetItem(lists[i][8]));

        }
        else
        {
            ui->tableWidget->setRowHidden(i-1,true);
        }
    }
}

void DisplayWindow::on_pushButton_clicked()
{
    QString homePath = QDir::homePath();
    QString path = ("Rscript "+homePath+"/rdisp.r ");
    system(path.toStdString().c_str());
}
