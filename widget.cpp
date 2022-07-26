#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Pixel Coordinates");

    pMenu = new QMenu(this);
    pChangeImg = new QAction("Select Image", this);
    pClear = new QAction("Clear Content", this);
    pCoordType = new QAction("Display Relative Coordinates", this);
    pTextColor = new QAction("Select Text Color", this);
    pMenu->addAction(pChangeImg);
    pMenu->addAction(pTextColor);
    pMenu->addAction(pCoordType);
    pMenu->addAction(pClear);



    mScene = new QGraphicsScene(this);
    mScene->setBackgroundBrush(Qt::white);

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    QImage image("./fish.jpg");
    pixmapItem->setPixmap(QPixmap::fromImage(image.scaled(this->size())));

    mScene->addItem(pixmapItem);
    ui->graphicsView->setScene(mScene);



}

Widget::~Widget()
{
    delete ui;
}



