#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
//#include "console.h"
#include <QPrinter>
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->setBackground(QBrush(QColor(48,47,47)));
    plot();

    serial = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;
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


//! [4]
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
     //   console->setEnabled(true);
    //    console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
   // console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
   // console->putData(data);
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settings, &MainWindow::show);
    //connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
