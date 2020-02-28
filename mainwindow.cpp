#include "mainwindow.h"
#include "ui_mainwindow.h"

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
     delete ui;

     // New window
     QMainWindow new window;

     Qint entier = 79;
<<<<<<< HEAD

     QDebug << "OK"
=======
>>>>>>> modif_entier
}

