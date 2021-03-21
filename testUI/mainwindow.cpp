#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QFile>


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


void MainWindow::readData()
{
     if (rec == true)
     {
          ui->customPlot->graph(0)->setData(dataX, dataY, true);
          ui->customPlot->xAxis->rescale(true);
          ui->customPlot->yAxis->rescale(true);
          ui->customPlot->replot();
     }

     val = serialPort->readAll();
     value = val.toDouble();

     speed_ms = perim * value / 25;
     speed_kmh = speed_ms * 3.6;
     int speed_rpm = (5 * 60 * value / 2500) / 0.01;

     ui->lcdSpeed->display(speed_kmh);
     ui->lcdCount->display(speed_rpm);

//     if (rec == true && speed_kmh > 40 && value < 2000)
         if (rec == true && value > 100)

     {
          dataX.append(++inc);
          dataY.append(value);
          ui->lcdCount->display(inc);

          qDebug() << value;
          previousValue = value;
     }
}

void MainWindow::on_startButton_clicked()
{
     QPen pen(Qt::red);
     pen.setWidth(2);

     ui->customPlot->setBackground(QBrush(Qt::black));
     //ui->customPlot->
     ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
     ui->customPlot->xAxis->setTickLabelColor(QColor(Qt::white));
     ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
     ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white));

     ui->customPlot->yAxis->setBasePen(QPen(Qt::red));
     ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
     ui->customPlot->yAxis->setTickPen(QPen(Qt::red));
     ui->customPlot->yAxis->setSubTickPen(QPen(Qt::red));

     perim = M_PI * 0.226;
     qDebug() << perim;

     rec = false;
     //    ui->labelPerim->setText(QString::(perim));

     serialPort = new QSerialPort(this);
//     serialPort->setPortName("/dev/ttyACM0");
     serialPort->setPortName("COM3");
     serialPort->setBaudRate(2000000);
     serialPort->setDataBits(QSerialPort::Data8);
     serialPort->setParity(QSerialPort::NoParity);
     serialPort->setStopBits(QSerialPort::OneStop);
     serialPort->setFlowControl(QSerialPort::NoFlowControl);
     serialPort->open(QSerialPort::QIODevice::ReadOnly);

     serialPort->waitForReadyRead();
     connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);

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
     inc = 0;
}

void MainWindow::on_plotButton_clicked()
{
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

void MainWindow::on_saveButton_clicked()
{
    QFile file("C:\\Users\\ama\\Documents\\qt-projects\\QMotorTest\\rec.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for (int i = 0; i < dataY.size(); i++)
    {
        out << dataY[i] << "\n";
    }
}
