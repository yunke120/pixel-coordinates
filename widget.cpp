#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pMenu = new QMenu(this);
    pChangeImg = new QAction("Select Image", this);
    pClear = new QAction("Clear Content", this);
    pMenu->addAction(pChangeImg);
    pMenu->addAction(pClear);

    connect(pChangeImg, &QAction::triggered, this, [=](){

        mFileName = QFileDialog::getOpenFileName(this,
                                                        "Select Image",
                                                         "./",
                                                        "Images(*.jpg *.png *.jpeg *.bmp)");

        displayImage(mFileName);
    });

    connect(pClear, &QAction::triggered, this, [=](){
        ui->label->gPointList.clear();
        ui->label->update();
    });


    ui->label->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->label->setTextColor(QColor(255,0,0));

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
//        qDebug() << double(event->pos().x()) / ui->label->width();
//        qDebug() << double(event->pos().y()) / ui->label->height();
    }
}

