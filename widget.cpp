#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Pixel Coordinates");
}

Widget::~Widget()
{

    delete ui;
}



