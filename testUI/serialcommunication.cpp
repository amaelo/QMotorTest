#include "serialcommunication.h"

serialcommunication::serialcommunication(QObject *parent, QString portName, int baudRate) : QObject(parent)
{
     if (!this->initializeSerialPort(portName, baudRate))
     {
          QString message = "ERROR : impossible to initialize seria port " + portName + " with baudrate = " + baudRate;

          qDebug() << message;
          QMessageBox::information(nullptr, "Error", message);
     }
}


void serialcommunication::StartCommunication()
{
     serialPort->waitForReadyRead();

     connect(serialPort, &QSerialPort::readyRead, this, &serialcommunication::flushData);
}


QString serialcommunication::GetSerialPortAdress()
{
     return "serialPort->toto";
}


bool serialcommunication::initializeSerialPort(QString portName, int baudRate)
{
     serialPort = new QSerialPort(this);
     serialPort->setPortName(portName);
     serialPort->setBaudRate(baudRate);
     serialPort->setDataBits(QSerialPort::Data8);
     serialPort->setParity(QSerialPort::NoParity);
     serialPort->setStopBits(QSerialPort::OneStop);
     serialPort->setFlowControl(QSerialPort::NoFlowControl);
     serialPort->open(QSerialPort::QIODevice::ReadOnly);

     return true;
}


void serialcommunication::flushData()
{
     disconnect(serialPort, &QSerialPort::readyRead, this, &serialcommunication::flushData);

     serialPort->waitForReadyRead();

     for (int i = 0; i < 50; i++)
     {
          serialPort->waitForReadyRead();
          qDebug() << serialPort->readLine();
     }

     connect(serialPort, &QSerialPort::readyRead, this, &serialcommunication::readData);
}


void serialcommunication::readData()
{
     frameRS232 = serialPort->readLine();

     if (frameRS232.startsWith('_') && frameRS232.endsWith('_') && frameRS232 != "_")
     {
          frameRS232.remove(0,1);
          frameRS232.remove(frameRS232.size() - 1, 1);

          listFramesRS232 = frameRS232.split('_');

          if(listFramesRS232[0] != nullptr)
          {
               for (int i = 0; i < listFramesRS232.length(); ++i)
               {
                    if (listFramesRS232[i] != "") { emit newFrameRS232(listFramesRS232[i]); }
               }
          }
          else
          {
               if (frameRS232 != "") { emit newFrameRS232(frameRS232); }
//          qDebug() << frameRS232;
          }

     }
     else
     {
          qDebug() << "ERROR : " << frameRS232;
     }
}
