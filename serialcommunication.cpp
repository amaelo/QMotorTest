#include "serialcommunication.h"

serialcommunication::serialcommunication(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort(this);

    serialPort->setPortName("COM3");
    serialPort->setBaudRate(9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

}


void serialcommunication::Start()
{
    serialPort->waitForReadyRead();

//    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);

}
