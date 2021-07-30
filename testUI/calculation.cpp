#include "calculation.h"


calculation::calculation(QObject *parent) : QObject(parent)
{
     perimeter_m = 0.71;
     rollerTops = 2500;
     sampleTime = 0.01;

}


void calculation::readData(QByteArray frame)
{

     frameSplited = frame.split(';');
     valueStr1 = frameSplited[0];
     valueStr2 = frameSplited[1];

     value1 = valueStr1.toDouble();
     value2 = valueStr2.toDouble();

     speed_kmh = perimeter_m * value1 / 25 * 3.6;
     speedRoller_rads = 2 * PI * (value1 / rollerTops) / sampleTime;
     speedEngine_rpm = (speedRoller_rads * 30) / PI;

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
}
