#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->setBackground(QBrush(QColor(48,47,47)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::addPoint(double x, double y)
//{

//}

//void MainWindow::clearData()
//{

//}

void MainWindow::plot()
{

   //////////////
   //potencia.append(2);
    potencia = {2,3,4,3,5,6,10,12,4,5,1}; // no eixo y
    //frequencia.append(3);
    frequencia = {88,89.7,91.5,93.9,94.6,96.9,99.3,100.7,101.5,104.1,108}; // no eixo x
    ui->plot->graph(0)->setData(frequencia,potencia);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("frequência");
    ui->plot->yAxis->setLabel("potência");
    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(88, 108);
    ui->plot->yAxis->setRange(0, 16);
    ui->plot->replot();
   // ui->plot->replot(); // salva o que existe
   // ui->plot->update(); // adiciona o que não existe
}

void MainWindow::on_btn_start_clicked()
{
    plot();
}
