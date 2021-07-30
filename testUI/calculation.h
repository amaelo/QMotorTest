#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>


class calculation : public QObject
{
     Q_OBJECT

public:
     explicit calculation(QObject *parent = nullptr);

private:


private slots:
     void readData(QByteArray frame);

signals:

private:
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
     unsigned int speed_kmh;
     unsigned int speedEngine_rpm;

     QVector<unsigned int> array_Speed_kmh;
     QVector<unsigned int> array_SpeedEngine_rpm;

};

#endif // CALCULATION_H
