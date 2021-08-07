#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>
#include <QThread>

#include "serialcommunication.h"


class calculation : public QObject
{
     Q_OBJECT

public:
     explicit calculation(QObject *parent = nullptr);

private:


private slots:
     void readData(QByteArray frame);

signals:
     void dataReady(unsigned int nbTops, unsigned int data1, double data2, int data3);

private:
     QThread *RS232thread;
     serialcommunication *RS232com;

     const short VOLTAGE_RESOLUTION = 1024;
     const double PI = 3.14159265;

     QList<QByteArray> frameSplited;
     QString valueStr1;
     QString valueStr2;
     double value1;
     double value2;
     double sampleTime;

     short rollerTops;
     double gearRatio;
     double perimeter_m;

     double speedRoller_rads;
     double lambda_volts;
     unsigned int speed_kmh;
     unsigned int speedEngine_rpm;

     QVector<unsigned int> array_Speed_kmh;
     QVector<unsigned int> array_SpeedEngine_rpm;
     QVector<double> array_lambda_volts;

};

#endif // CALCULATION_H
