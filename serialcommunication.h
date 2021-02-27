#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "mainwindow.h"


class serialcommunication : public QObject
{
    Q_OBJECT
public:
    explicit serialcommunication(QObject *parent = nullptr);

    void Start();

private:
    QSerialPort *serialPort;


signals:

};

#endif // SERIALCOMMUNICATION_H
