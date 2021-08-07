#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QProcess>
#include <QFileDialog>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent)
     : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     ui->centralwidget->layout()->setMargin(0);
     ui->widget->layout()->setMargin(0);
     ui->stackedWidget->layout()->setMargin(0);

     simu = new simulator(0, 100000);
     myThread = new QThread(this);
     myThread->setPriority(QThread::IdlePriority);
     simu->moveToThread(myThread);
     connect(myThread, &QThread::finished, simu, &QObject::deleteLater);
     connect(this, &MainWindow::startSimulator, simu, &simulator::doLoop);
//     connect(simu, &simulator::resultReady, this, &MainWindow::getResult);

     timer = new QTimer(this);
     timer->setTimerType(Qt::VeryCoarseTimer);
     connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_tic);

     ui->customPlot->addGraph();
     ui->customPlot->addGraph();

     rec = false;
     inc = 0;
     lambdaPrevious = 0;

     QAction *connectPort = new QAction(this);
     QPushButton *connectPortButton = new QPushButton(this);
     connectPortButton->setText("Connect");
     connectPortButton->setCheckable(true);
     connectPortButton->addAction(connectPort);
     connect(connectPortButton, &QPushButton::clicked, this, &MainWindow::connectPortAction);
//     connect(connectPort, &QAction::triggered, this, &MainWindow::on_connectPortAction);

     QComboBox *serialAdressBox = new QComboBox(this);
     serialAdressBox->setEditable(true);
     serialAdressBox->setMinimumWidth(150);

     QLabel *portLabel = new QLabel(this);
     portLabel->setText("Serial Port : ");


     ui->toolBar->addWidget(portLabel);
     ui->toolBar->addWidget(serialAdressBox);
     ui->toolBar->addWidget(connectPortButton);

     ui->customPlot->setBackground(QBrush(Qt::black));
     ui->customPlot->axisRect()->setupFullAxesBox();

     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

     ui->customPlot->xAxis2->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis2->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis2->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis2->setSubTickPen(QPen(Qt::white));

     ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
     ui->customPlot->yAxis->setTickPen(QPen(Qt::red, 3));
     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red, 2));
     ui->customPlot->yAxis->setTickLabels(true);
     ui->customPlot->yAxis->setTickLabelFont(QFont("FreeSans", 12, QFont::Bold));

     ui->customPlot->yAxis2->setBasePen(QPen(Qt::white));
     ui->customPlot->yAxis2->setTickLabelColor(QColor(Qt::green));
     ui->customPlot->yAxis2->setTickPen(QPen(Qt::green));
     ui->customPlot->yAxis2->setSubTickPen(QPen(Qt::green));
     ui->customPlot->yAxis2->setTickLabels(true);
     ui->customPlot->yAxis2->setTickLabelFont(QFont("FreeSans", 12, QFont::Bold));
     ui->customPlot->yAxis2->setRange(0, 1);
}


MainWindow::~MainWindow()
{
     myThread->quit();
     myThread->wait();

     delete ui;
     qInfo() << "Mainwindow deleted";

     inc = 0;
}


//void MainWindow::on_pushButton_clicked()
//{
//     simu->StopLoop();


//     myForm = new myWidget(ui->verticalFrameN1);
//     myForm->show();

//     QVariant toto;
//     toto = "salut";

//     qDebug() << toto;
//     //    QMessageBox::information(this, "title", toto.toString());

//     //    QObject *objframe = new QObject();

//     QFrame *frame = new QFrame(this);
//     //    QPushButton *button = new QPushButton(this);
//     QList<QWidget *> list;
//     list.append(frame);
//     //    list.append(button);
//     QObject *obj = new QObject(nullptr); // TODO : deledte obj

//     for(int i = 0; i < list.size(); ++i)
//     {
//          obj = list[i];
//          qDebug() << "widget N°" << i << list.at(i);
//     }
//     //qobject_cast<QFrame *>(objframe);
//     //ui->verticalLayout->addWidget(frame);
//     delete obj;
//     qDebug() << "\ntype de toto" << toto.type() << "\n";

//}


//void MainWindow::on_pushButton_2_clicked()
//{
//     myThread->start();
//     emit startSimulator();
//     timer->start(100);
//}


//void MainWindow::getResult(const int &result)
//{
//     ui->lcdNumber->display(result);
//}

void MainWindow::on_pushButton_3_clicked()
{

     QVector<double> dataX;
     QVector<double> dataY;

     dataX << 0 << 10 << 15 << 38 << 100 << 102 << 139;
     dataY << 2 << 23 << -12 << -6 << 65 << -230 << -22;

     QPen pen(Qt::red);
     pen.setWidth(10);

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

//void MainWindow::on_pushButton_4_clicked()
//{
//     double x = ui->lineX->text().toDouble();
//     double y = ui->lineY->text().toDouble();

//     ui->customPlot->graph(0)->addData(x, y);
//     ui->customPlot->xAxis->rescale(false);
//     ui->customPlot->yAxis->rescale(false);
//     ui->customPlot->replot();

//}

//************************************************************************************
//void MainWindow::on_pushButton_5_clicked()
//{
//     QPrinter printer;
//     printer.setOutputFileName("letter");
//     printer.setOutputFormat(QPrinter::PdfFormat);
//     ui->textEdit->print(&printer);
//}

//void MainWindow::on_pushButton_6_clicked()
//{
//     QPixmap pixmap(ui->customPlot->size());
//     ui->customPlot->render(&pixmap);
//     bool rep = pixmap.save(":/new/prefix1/img");

//     qDebug() << "image saved :" << rep;

//}
//***************************************************************************************


void MainWindow::on_getData(int nbTops, int speed, double lambda, int speeEngine)
{
     if (rec == true)
     {
          if (dataX.size() > 2500)
          {
               dataX.pop_front();
               dataY.pop_front();
               dataY2.pop_front();
          }

          ui->customPlot->graph(0)->setData(dataX, dataY, true);
          ui->customPlot->graph(1)->setData(dataX, dataY2, true);
//          ui->customPlot->xAxis->rescale(true);
//          ui->customPlot->yAxis->rescale(true);
////          ui->customPlot->yAxis2->rescale(true);
//          ui->customPlot->replot();
          speed_kmh = speed;
          speedEngine_rpm = speeEngine;

          dataX.append(++inc);
          dataY.append(nbTops);
          dataY2.append(lambda);

//          previousValue = value;
     }
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

//          valSplitted = frame.split(';');
//          val1 = valSplitted[0];
//          val2 = valSplitted[1];

//          value = val1.toDouble();
//          value2 = val2.toDouble();
//          if (value2 > 1024) { qDebug() << value2; }

//          speed_ms = perim * value / 25;
//          speed_kmh = speed_ms * 3.6;
//          ui->lcdSpeed->display(speed_kmh);
void MainWindow::on_timer_tic()
{
     ui->lcdSpeed->display(speed_kmh);
     ui->lcdCount->display(speedEngine_rpm);

     ui->customPlot->xAxis->rescale(true);
     ui->customPlot->yAxis->rescale(true);
     ui->customPlot->replot();
}


//     }
//     else
//     {
//          qDebug() << "Error : °" << inc << " Value : " << val;
//     }


void MainWindow::connectPortAction()
{
     ui->customPlot->graph(0)->setPen(QPen(Qt::red, 2));
     ui->customPlot->graph(1)->setPen(QPen(Qt::green));

     dataCalculation = new calculation(this);
     calculationThread = new QThread(this);
     dataCalculation->moveToThread(calculationThread);
     calculationThread->start();

     connect(dataCalculation, &calculation::dataReady, this, &MainWindow::on_getData);

//     QPen pen2(Qt::green)
//     pen2.setWidth(2);

//     ui->customPlot->axisRect()->setupFullAxesBox();
//     ui->customPlot->setBackground(QBrush(Qt::black));

//     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
//     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
//     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
//     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

//     ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
//     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
//     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
//     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));
//     ui->customPlot->yAxis->setTickLabels(true);
////     ui->customPlot->yAxis->setTicker()

//     ui->customPlot->yAxis2->setBasePen(QPen(Qt::white));
//     ui->customPlot->yAxis2->setTickLabelColor(QColor(Qt::green));
//     ui->customPlot->yAxis2->setTickPen(QPen(Qt::green));
//     ui->customPlot->yAxis2->setSubTickPen(QPen(Qt::green));
//     ui->customPlot->yAxis2->setTickLabels(true);
//     ui->customPlot->yAxis2->setRange(0, 1);

     ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis2);

     perim = M_PI * 0.226;
     qDebug() << perim;

     rec = false;
     //    ui->labelPerim->setText(QString::(perim));


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
     timer->start(100);
}

void MainWindow::on_stopButton_clicked()
{
     rec = false;
     timer->stop();
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
     QString recPath = "";

#ifdef Q_OS_LINUX
     QString pythonPath = "/home/kama/anaconda3/bin/python";
     args << "/home/kama/applications/_myAppli/QMotorTest/testUI/getValues.py";
     recPath = "/home/kama/applications/_myAppli/QMotorTest/recorders";
#else
     QString pythonPath = "C:/ProgramData/Anaconda3/python.exe";
     args << "C:/Users/ama/Documents/qt-projects/QMotorTest/testUI/getValues.py";
#endif

     QFileDialog dial(this,"Save recorder", recPath,"");
     dial.setFileMode(QFileDialog::AnyFile);
     QString fPath = dial.getSaveFileName();

     QFile file(fPath);
     if (file.open(QIODevice::WriteOnly))
     {
         QTextStream stream(&file);
         for (int i = 0; i < dataY.length(); ++i)
         {
              stream << dataY[i] << "," << dataY2[i] << endl;
         }
     }
     file.close();

     args << fPath;

     QProcess proc;
     proc.start(pythonPath, args);
     proc.waitForStarted();
     proc.waitForFinished();
     QString result = proc.readAll();

     QStringList strX = result.split("_")[0].split(";");
     QStringList strY1 = result.split("_")[1].split(";");
     QStringList strY2 = result.split("_")[2].split(";");

     dataX.clear();
     dataY.clear();
     dataY2.clear();

     for(int i = 0; i < strX.length(); i++)
     {
          dataX.append(strX[i].toDouble());
          dataY.append(strY1[i].toDouble());
          lambdaPrevious = strY2[i].toDouble();
          if (strY2[i].toDouble() > 0)
          {
              dataY2.append(strY2[i].toDouble());
              lambdaPrevious = strY2[i].toDouble();
          }
          else { dataY2.append(lambdaPrevious); }
     }

     QPen pen(Qt::red);
     pen.setWidth(2);

     QPen pen2(Qt::green);
     pen.setWidth(2);

//     ui->customPlot->axisRect()->setupFullAxesBox();

//     ui->customPlot->setBackground(QBrush(Qt::black));
//     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
//     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
//     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
//     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

////     ui->customPlot->xAxis2->setBasePen(QPen(Qt::white));
////     ui->customPlot->xAxis2->setTickLabelColor(QColor(Qt::white));
////     ui->customPlot->xAxis2->setTickPen(QPen(Qt::white));
////     ui->customPlot->xAxis2->setSubTickPen(QPen(Qt::white));

//     ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
//     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
//     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
//     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));

//     ui->customPlot->yAxis2->setBasePen(QPen(Qt::white));
//     ui->customPlot->yAxis2->setTickLabelColor(QColor(Qt::green));
//     ui->customPlot->yAxis2->setTickPen(QPen(Qt::green));
//     ui->customPlot->yAxis2->setSubTickPen(QPen(Qt::green));
//     ui->customPlot->yAxis2->setTickLabels(true);
//     ui->customPlot->yAxis2->setRange(0, 5);

     QCPCurve *newCurve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
     QCPCurve *newCurve2 = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis2);

     const int pointsCount = dataX.length();

     QVector<QCPCurveData> dataCurve(pointsCount);
     QVector<QCPCurveData> dataCurve2(pointsCount);

     for (int i = 0; i < pointsCount; i++)
     {
          dataCurve[i] = QCPCurveData(i, dataX[i], dataY[i]);
          dataCurve2[i] = QCPCurveData(i, dataX[i], dataY2[i]);
     }

     QVector<double> xo;
     QVector<double> yo;
     xo.append(10000);
     yo.append(0);
     //ui->customPlot->graph(0)->setValueAxis(ui->customPlot->yAxis);
     ui->customPlot->graph(0)->setData(xo, yo, true);
     ui->customPlot->graph(1)->setData(xo, yo, true);

     newCurve->data()->set(dataCurve);
     newCurve->setPen(pen);
     newCurve2->data()->set(dataCurve2);
     newCurve2->setPen(pen2);

     ui->customPlot->graph(1)->setValueAxis(ui->customPlot->yAxis2);

//ui->customPlot->addPlottable(this->newCurve);
//     ui->customPlot->cur
     ui->customPlot->graph(1)->setData(dataX, dataY2, true);
     ui->customPlot->graph(1)->setPen(pen2);

     ui->customPlot->xAxis->setRange(dataX[0] - 100, ui->customPlot->xAxis->range().maxRange + 500);
     ui->customPlot->xAxis->rescale(true);
     ui->customPlot->yAxis->rescale(true);
     ui->customPlot->yAxis2->setRange(0, 1);

     ui->customPlot->replot();
}
