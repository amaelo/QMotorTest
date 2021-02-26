#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QSerialPort>

#include "mywidget.h"
#include "simulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void getResult(const int &result);
    void readData();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_startButton_clicked();


    void on_recButton_clicked();

    void on_stopButton_clicked();

    void on_razButton_clicked();

    void on_plotButton_clicked();

signals :
    void startSimulator();

private:
    Ui::MainWindow *ui;
    myWidget *myForm;
    simulator *simu;
    QThread *myThread;
    QTimer *timer;

    QSerialPort *serialPort;

    QString val;
    float perim;
    float speed;
    float speed_ms;
    int speed_kmh;
    int inc;
    long value;
    long previousValue;
    bool rec;

    QVector<double> dataX;
    QVector<double> dataY;
};
#endif // MAINWINDOW_H
