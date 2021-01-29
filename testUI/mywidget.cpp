#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
}

myWidget::~myWidget()
{
    delete ui;
    qDebug() << "mywidget deleted";
}
