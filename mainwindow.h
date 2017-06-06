#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>


namespace Ui {
class MainWindow;
}
//terminal
class SettingsDialog;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    void addPoint(double x, double y);
//    void clearData();
    void plot();

private slots:
    void on_btn_start_clicked();
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
     void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    // terminal
    QLabel *status;
    SettingsDialog *settings;
    QSerialPort *serial;

    int i;
    QVector<double> potencia,frequencia;
};


#endif // MAINWINDOW_H
