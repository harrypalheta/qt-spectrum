#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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

private:
    Ui::MainWindow *ui;

    int i;
    QVector<double> potencia,frequencia;
};

#endif // MAINWINDOW_H
