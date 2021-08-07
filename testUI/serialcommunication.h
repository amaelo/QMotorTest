#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QMessageBox>


class serialcommunication : public QObject
{
     Q_OBJECT

public:
     explicit serialcommunication(QObject *parent = nullptr, QString portName="", int baudRate=115200);
     void StartCommunication();
     QString GetSerialPortAdress();


private:
     bool initializeSerialPort(QString portName, int baudRate);


private slots:
     void readData();
     void flushData();


private:
     QByteArray frameRS232;
     QList<QByteArray> listFramesRS232;

     QSerialPort *serialPort;


signals:
     void newFrameRS232(QByteArray frame);

};

#endif // SERIALCOMMUNICATION_H
