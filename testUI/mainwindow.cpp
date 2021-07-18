#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QProcess>



MainWindow::MainWindow(QWidget *parent)
     : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

     simu = new simulator(0, 100000);
     myThread = new QThread(this);
     myThread->setPriority(QThread::IdlePriority);
     simu->moveToThread(myThread);
     connect(myThread, &QThread::finished, simu, &QObject::deleteLater);
     connect(this, &MainWindow::startSimulator, simu, &simulator::doLoop);
     connect(simu, &simulator::resultReady, this, &MainWindow::getResult);

     timer = new QTimer(this);
     //    connect(timer, &QTimer::timeout, this, &MainWindow::getResult);
     timer->setTimerType(Qt::PreciseTimer);

     ui->customPlot->addGraph();
     ui->customPlot->addGraph();

     rec = false;
     inc = 0;
}


MainWindow::~MainWindow()
{
     myThread->quit();
     myThread->wait();

     delete ui;
     qInfo() << "Mainwindow deleted";

     inc = 0;
}


void MainWindow::on_pushButton_clicked()
{
     simu->StopLoop();


     myForm = new myWidget(ui->verticalFrameN1);
     myForm->show();

     QVariant toto;
     toto = "salut";

     qDebug() << toto;
     //    QMessageBox::information(this, "title", toto.toString());

     //    QObject *objframe = new QObject();

     QFrame *frame = new QFrame(this);
     //    QPushButton *button = new QPushButton(this);
     QList<QWidget *> list;
     list.append(frame);
     //    list.append(button);
     QObject *obj = new QObject(nullptr); // TODO : deledte obj

     for(int i = 0; i < list.size(); ++i)
     {
          obj = list[i];
          qDebug() << "widget N°" << i << list.at(i);
     }
     //qobject_cast<QFrame *>(objframe);
     //ui->verticalLayout->addWidget(frame);
     delete obj;
     qDebug() << "\ntype de toto" << toto.type() << "\n";

}


void MainWindow::on_pushButton_2_clicked()
{
     myThread->start();
     emit startSimulator();
     timer->start(100);
}


void MainWindow::getResult(const int &result)
{
     ui->lcdNumber->display(result);
}

void MainWindow::on_pushButton_3_clicked()
{

     QVector<double> dataX;
     QVector<double> dataY;

     dataX << 0 << 10 << 15 << 38 << 100 << 102 << 139;
     dataY << 2 << 23 << -12 << -6 << 65 << -230 << -22;

     QPen pen(Qt::red);
     pen.setWidth(2);

     ui->customPlot->setBackground(QBrush(Qt::black));
     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

     ui->customPlot->yAxis->setBasePen(QPen(Qt::red));
     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));

     ui->customPlot->graph(0)->setData(dataX, dataY, true);
     ui->customPlot->graph(0)->setPen(pen);
     ui->customPlot->xAxis->rescale(false);
     ui->customPlot->yAxis->rescale(false);
     ui->customPlot->replot();
}

void MainWindow::on_pushButton_4_clicked()
{
     double x = ui->lineX->text().toDouble();
     double y = ui->lineY->text().toDouble();

     ui->customPlot->graph(0)->addData(x, y);
     ui->customPlot->xAxis->rescale(false);
     ui->customPlot->yAxis->rescale(false);
     ui->customPlot->replot();

}

void MainWindow::on_pushButton_5_clicked()
{
     QPrinter printer;
     printer.setOutputFileName("letter");
     printer.setOutputFormat(QPrinter::PdfFormat);
     ui->textEdit->print(&printer);
}

void MainWindow::on_pushButton_6_clicked()
{
     QPixmap pixmap(ui->customPlot->size());
     ui->customPlot->render(&pixmap);
     bool rep = pixmap.save(":/new/prefix1/img");

     qDebug() << "image saved :" << rep;

}


void MainWindow::readData(QByteArray frame)
{
     if (rec == true)
     {
          if (dataX.size() > 2000)
          {
               dataX.pop_front();
               dataY.pop_front();
               dataY2.pop_front();
          }

          ui->customPlot->graph(0)->setData(dataX, dataY, true);
          ui->customPlot->graph(1)->setData(dataX, dataY2, true);
          ui->customPlot->xAxis->rescale(true);
          ui->customPlot->yAxis->rescale(true);
//          ui->customPlot->yAxis2->rescale(true);
          ui->customPlot->replot();
     }

//     val = serialPort->readLine();

//     bool ok;
//     val = serialPort->readLine();
////     ui->lcdCount->display(inc++);

//     if (val.startsWith('_') && val.endsWith('_') && val != '_')
//     {
////          qDebug() << val;

//          val.remove('_');
//          qDebug() << frame;

          valSplitted = frame.split(';');
          val1 = valSplitted[0];
          val2 = valSplitted[1];

          value = val1.toDouble();
          value2 = val2.toDouble();
          if (value2 > 1024) { qDebug() << value2; }

          speed_ms = perim * value / 25;
          speed_kmh = speed_ms * 3.6;
          ui->lcdSpeed->display(speed_kmh);


          if (rec == true)
          {
               dataX.append(++inc);
               dataY.append(value);
               dataY2.append(1.1 * value2 / 1024);

//               ui->lcdCount->display(inc);

//               qDebug() << value << "\n";
               previousValue = value;
          }
//     }
//     else
//     {
//          qDebug() << "Error : °" << inc << " Value : " << val;
//     }
}

void MainWindow::on_startButton_clicked()
{
     ui->customPlot->graph(0)->setPen(QPen(Qt::red));
     ui->customPlot->graph(1)->setPen(QPen(Qt::green));

//     QPen pen2(Qt::green);
//     pen2.setWidth(2);

     ui->customPlot->axisRect()->setupFullAxesBox();
     ui->customPlot->setBackground(QBrush(Qt::black));

     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

     ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));
     ui->customPlot->yAxis->setTickLabels(true);

     ui->customPlot->yAxis2->setBasePen(QPen(Qt::white));
     ui->customPlot->yAxis2->setTickLabelColor(QColor(Qt::green));
     ui->customPlot->yAxis2->setTickPen(QPen(Qt::green));
     ui->customPlot->yAxis2->setSubTickPen(QPen(Qt::green));
     ui->customPlot->yAxis2->setTickLabels(true);
     ui->customPlot->yAxis2->setRange(0, 1);

     ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis2);

     perim = M_PI * 0.226;
     qDebug() << perim;

     rec = false;
     //    ui->labelPerim->setText(QString::(perim));
     RS232com = new serialcommunication(this, "/dev/ttyACM0", 2000000);

     RS232thread = new QThread(this);
     RS232com->moveToThread(RS232thread);
     RS232thread->start();

     RS232com->StartCommunication();

     connect(RS232com, &serialcommunication::newFrameRS232, this, &MainWindow::readData);
//     serialPort = new QSerialPort(this);
//     serialPort->setPortName("/dev/ttyACM0");
//     serialPort->setBaudRate(2000000);
//     serialPort->setDataBits(QSerialPort::Data8);
//     serialPort->setParity(QSerialPort::NoParity);
//     serialPort->setStopBits(QSerialPort::OneStop);
//     serialPort->setFlowControl(QSerialPort::NoFlowControl);
//     serialPort->open(QSerialPort::QIODevice::ReadOnly);

//     serialPort->waitForReadyRead();
//     connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);

}

void MainWindow::on_recButton_clicked()
{
     rec = true;

}

void MainWindow::on_stopButton_clicked()
{
     rec = false;
}

void MainWindow::on_razButton_clicked()
{
     dataX.clear();
     dataY.clear();
     dataY2.clear();
     inc = 0;
}

void MainWindow::on_plotButton_clicked()
{
     QStringList args;
     QString arg2 = "";
     QString arg3 = "";

#ifdef Q_OS_LINUX
     QString pythonPath = "/home/kama/anaconda3/bin/python";
     args << "/home/kama/applications/_myAppli/QMotorTest/testUI/PlotMeasurments.py";
#else

#endif

     for (int i = 0; i < dataX.length(); ++i)
     {
          arg2.append(QString::number(dataY[i]) + ";");
          arg3.append(QString::number(dataY2[i]) + ";");
     }
     args << arg2 << arg3 ;

     QProcess proc;
     proc.start(pythonPath, args);
     proc.waitForStarted();
     proc.waitForFinished();
     QString result = proc.readAll();

     QStringList strX = result.split("_")[0].split(";");
     QStringList strY = result.split("_")[1].split(";");

     dataX.clear();
     dataY.clear();

     for(int i = 0; i < strX.length(); i++)
     {
          dataX.append(strX[i].toDouble());
          dataY.append(strY[i].toDouble());
     }

     QPen pen(Qt::red);
     pen.setWidth(2);

     ui->customPlot->setBackground(QBrush(Qt::black));
     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

     ui->customPlot->yAxis->setBasePen(QPen(Qt::red));
     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));

     QCPCurve *newCurve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
     const int pointCount = dataX.length();
     QVector<QCPCurveData> dataCurve(pointCount);

     for (int i = 0; i < pointCount; i++)
     {
          dataCurve[i] = QCPCurveData(i, dataX[i], dataY[i]);
     }


     newCurve->data()->set(dataCurve);
//ui->customPlot->addPlottable(this->newCurve);
//     ui->customPlot->cur
     //ui->customPlot->graph(0)->setData(dataX, dataY, true);
     ui->customPlot->graph(0)->setPen(pen);

     ui->customPlot->xAxis->setRange(dataX[0] - 100, ui->customPlot->xAxis->range().maxRange + 500);
     ui->customPlot->yAxis->rescale(true);
     ui->customPlot->replot();
}
