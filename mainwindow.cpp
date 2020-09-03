#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QProcess>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
     : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
}

MainWindow::~MainWindow()
{
     delete ui;

     // Add new fucntion

}


void MainWindow::on_toolButton_clicked()
{
     QProcess cmd;


     Q_INIT_RESOURCE(ressources); // ressources.qrc
     QFile file(":/python/pyt_4.py");

     QDir pyDir;
     pyDir.mkdir(QApplication::applicationDirPath() + "/python");

     QString path = QApplication::applicationDirPath() + "/python/" + "txt.py";
     QStringList arg(path);
     file.copy(path);

     cmd.setArguments(arg);
     cmd.start("/usr/bin/python", arg);
//     cmd.start("ls");
     cmd.waitForFinished();
     QString outp = cmd.readAllStandardOutput();
     QStringList outList = outp.split('\n');

     QMessageBox::information(nullptr, "titl", outp);
}
