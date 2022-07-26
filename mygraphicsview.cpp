#include "mygraphicsview.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent)
               : QGraphicsView(parent)
               , IS_Translate(false)
{
    pScene = new QGraphicsScene(this);
    pixmapItem = new QGraphicsPixmapItem();

    pScene->addItem(pixmapItem);
    this->setScene(pScene);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QGraphicsView::customContextMenuRequested,[=](const QPoint &)
        {
            pMenu->exec(QCursor::pos());
        });

    pMenu = new QMenu(this);
    pChangeImg = new QAction("Select Image", this);
    pClear = new QAction("Clear Content", this);
    pCoordType = new QAction("Display Relative Coordinates", this);
    pTextColor = new QAction("Select Text Color", this);
    pMenu->addAction(pChangeImg);
    pMenu->addAction(pTextColor);
    pMenu->addAction(pCoordType);
    pMenu->addAction(pClear);


    pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, &QTimer::timeout, [=](){
        IS_Translate = true;
    });

    connect(pChangeImg, &QAction::triggered, this, [=](){

        mFileName = QFileDialog::getOpenFileName(this,
                                                        "Select Image",
                                                         "./",
                                                        "Images(*.jpg *.png *.jpeg *.bmp)");

        showImage(mFileName);
    });

    connect(pCoordType, &QAction::triggered, this, [=](){

        if(pCoordType->text() == "Display Relative Coordinates")
        {

            pCoordType->setText("Display Absolute Coordinates");
        }
        else
        {
            pCoordType->setText("Display Relative Coordinates");
        }
        this->update();
    });

    connect(pClear, &QAction::triggered, this, [=](){

    });

    connect(pTextColor, &QAction::triggered, this, [=](){

        QColor color = QColorDialog::getColor(Qt::white, this);

    });
}

MyGraphicsView::~MyGraphicsView()
{
    pTimer->deleteLater();
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? zoomOut() : zoomIn();
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(IS_Translate)
    {
        QPointF posDelta = event->pos() - mLastPos;

        int w = viewport()->rect().width();
        int h = viewport()->rect().height();
        QPoint newCenter(w / 2. - posDelta.x()+0.5,  h / 2. - posDelta.y()+0.5);
        centerOn(mapToScene(newCenter));
    }
    mLastPos = event->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        pTimer->start();
        mLastPos = event->pos();
    }
//    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(pTimer->isActive()) pTimer->stop();
    if(IS_Translate) IS_Translate = false;
    else {
        QPoint p = event->pos();

    }

//    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::zoomIn()
{
    scale(0.95,0.95);
}

void MyGraphicsView::zoomOut()
{
    scale(1.05,1.05);
}

void MyGraphicsView::showImage(const QString &filename)
{
    QImage image(filename);
    pixmapItem->setPixmap(QPixmap::fromImage(image));
}
