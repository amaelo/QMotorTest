#include "calculation.h"


calculation::calculation(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_LINUX
     RS232com = new serialcommunication(this, "/dev/ttyACM0", 2000000);
#else
     RS232com = new serialcommunication(this, "COM3", 2000000);
#endif

     RS232thread = new QThread(this);
     RS232com->moveToThread(RS232thread);
//     RS232thread->setPriority(QThread::TimeCriticalPriority);
     RS232thread->start();
     RS232com->StartCommunication();

     connect(RS232com, &serialcommunication::newFrameRS232, this, &calculation::readData);

     perimeter_m = 0.71;
     rollerTops = 2500;
     sampleTime = 0.01;

}


void calculation::readData(QByteArray frame)
{
//     qDebug() << frame;
     frameSplited = frame.split(';');
     valueStr1 = frameSplited[0];
     valueStr2 = frameSplited[1];

     value1 = valueStr1.toDouble();
     value2 = valueStr2.toDouble();

     speed_kmh = 3.6 * perimeter_m * (value1 / 2500) / sampleTime;
     speedRoller_rads = 2 * PI * (value1 / rollerTops) / sampleTime;
     speedEngine_rpm = 5 * (speedRoller_rads * 30) / PI;

     emit dataReady(value1, speed_kmh, 1.1 * value2 / 1024, speedEngine_rpm);

//     array_Speed_kmh.append(speed_kmh);
//     array_SpeedEngine_rpm.append()
//     array_lambda_volts.append(1.1 * value2 / 1024);
}
//     if (rec == true)
//     {
//          dataX.append(++inc);
//          dataY.append(value);
//          dataY2.append(1.1 * value2 / VOLTAGE_RESOLUTION);

//          //               ui->lcdCount->display(inc);

//          //               qDebug() << value << "\n";
//          previousValue = value;

//}

//               speed_rps = [(v / TOPS) / SAMPLE for v in values]
//               speed_rpm = [v * 60 for v in speed_rps]
//               speed_rads = [v * 2 * PI for v in speed_rps]

