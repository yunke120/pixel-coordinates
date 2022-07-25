#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    IS_RELATIVE(true)
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

    connect(pChangeImg, &QAction::triggered, this, [=](){

        mFileName = QFileDialog::getOpenFileName(this,
                                                        "Select Image",
                                                         "./",
                                                        "Images(*.jpg *.png *.jpeg *.bmp)");

        displayImage(mFileName);
    });

    connect(pCoordType, &QAction::triggered, this, [=](){

        if(pCoordType->text() == "Display Relative Coordinates")
        {
            ui->label->setCoordType(ui->label->REALTIVE);
            pCoordType->setText("Display Absolute Coordinates");
        }
        else
        {
            ui->label->setCoordType(ui->label->ABSOLUTE);
            pCoordType->setText("Display Relative Coordinates");
        }
        ui->label->update();
    });

    connect(pClear, &QAction::triggered, this, [=](){
        ui->label->gPointList.clear();
        ui->label->update();
    });

    connect(pTextColor, &QAction::triggered, this, [=](){

        QColor color = QColorDialog::getColor(Qt::white, this);
        ui->label->setTextColor(color);
        ui->label->update();
    });


    ui->label->setContextMenuPolicy(Qt::CustomContextMenu);


    connect(ui->label,&QLabel::customContextMenuRequested,[=](const QPoint &pos)
    {
        Q_UNUSED(pos);
        pMenu->exec(QCursor::pos());
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::displayImage(const QString &fileName)
{
    if(fileName.isNull()) return ;
    QImage image(fileName);
    if(image.isNull()) return;
    ui->label->showImage(image);
}


void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        ui->label->gPointList.append(event->pos());
        ui->label->update();
    }
}

