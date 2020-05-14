#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

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
     QMessageBox::information(nullptr, "titl", "test OK");
}
