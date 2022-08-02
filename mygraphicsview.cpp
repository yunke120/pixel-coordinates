#include "mygraphicsview.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent)
               : QGraphicsView(parent)
               , IS_Translate(false)
               , IS_Translate2(false)
               , mTextColor(QColor(255,0,0))
               , mCoordType(ABSOLUTE)
{
    this->setWindowTitle("PixelCoord V2.1");
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // scaled变换时以鼠标为中心变换

}

MyGraphicsView::~MyGraphicsView()
{
    delete pixmapItem;
    pixmapItem = nullptr;
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? scale(1.05,1.05) : scale(0.95,0.95);
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
        QPointF p1 = mapToScene(event->pos());
        QPoint p3(int(p1.x()), int(p1.y()));
        QPointF p2 = pixmapItem->mapToScene(p3);
        double w = p2.x();
        double h = p2.y();

        if( w < 0 || w >  imgSize.width() || h < 0 || h > imgSize.height() ) return;

        QString text;
        if(mCoordType == ABSOLUTE)
            text = QString("(%1,%2)").arg(w, 3, 'f',2,QChar('0')).arg(h, 3, 'f',2,QChar('0'));
        else
            text = QString("(%1,%2)").arg(w/imgSize.width(), 3, 'f',2,QChar('0')).arg(h/imgSize.height(), 3, 'f',2,QChar('0'));

        QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem(text);
        item->setPen(mTextColor);
        item->setPos(p1);
        mSimpleTextItemList.append(item);
        pScene->addItem(item);
    }
    else if (event->button() == Qt::RightButton) {
        pTimer->start();
        IS_Translate2 = false;
        mLastPos = event->pos();
    }

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *)
{
    if(pTimer->isActive()) pTimer->stop();
    if(IS_Translate)
    {
        IS_Translate2 = true;
        IS_Translate = false;
        this->setDragMode(QGraphicsView::NoDrag); //设置鼠标显示为手型
    }


}

void MyGraphicsView::showEvent(QShowEvent *)
{
    QImage image(":/show.png");
    if(image.isNull()) return;
    QImage img = image.scaled(800,600,Qt::KeepAspectRatio);
    imgSize = img.size();
    this->resize(imgSize);

    pScene = new QGraphicsScene(this);
    pScene->setSceneRect(-viewport()->width()/2,-viewport()->height()/2,viewport()->width()*2, viewport()->height()*2);
    pScene->setBackgroundBrush(Qt::gray);
    this->setScene(pScene);

    pixmapItem = new QGraphicsPixmapItem();
    pixmapItem->setPixmap(QPixmap::fromImage(img));
    pixmapItem->setPos(0,0);
    pScene->addItem(pixmapItem);

    menuInit();

    pTimer = new QTimer(this);
    pTimer->setInterval(150);
    connect(pTimer, &QTimer::timeout, [=](){
        IS_Translate = true;
        this->setDragMode(QGraphicsView::ScrollHandDrag); //设置鼠标显示为手型
    });

}

void MyGraphicsView::slotChangeImgTriggered()
{
    mFileName = QFileDialog::getOpenFileName(this,
                                                    "Select Image",
                                                     "./",
                                                    "Images(*.jpg *.png *.jpeg *.bmp)");

    showImage(mFileName);
}

void MyGraphicsView::slotCoordTypeTriggered()
{
    if(pCoordType->text() == "Display Relative Coordinates")
    {
        mCoordType = REALTIVE;
        pCoordType->setText("Display Absolute Coordinates");
    }
    else
    {
        mCoordType = ABSOLUTE;
        pCoordType->setText("Display Relative Coordinates");
    }
    this->update();
}

void MyGraphicsView::slotTextColorTriggered()
{
    mTextColor = QColorDialog::getColor(Qt::white, this);
}

void MyGraphicsView::slotClearTriggered()
{
    if(mSimpleTextItemList.isEmpty()) return;
    for (int i = 0; i < mSimpleTextItemList.size(); i++) {
        pScene->removeItem(mSimpleTextItemList.value(i));
    }
    mSimpleTextItemList.clear();
}

void MyGraphicsView::menuInit()
{
    pMenu = new QMenu(this);
    pChangeImg = new QAction("Select Image", this);
    pClear = new QAction("Clear Content", this);
    pCoordType = new QAction("Display Relative Coordinates", this);
    pTextColor = new QAction("Select Text Color", this);
    pMenu->addAction(pChangeImg);
    pMenu->addAction(pTextColor);
    pMenu->addAction(pCoordType);
    pMenu->addAction(pClear);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QGraphicsView::customContextMenuRequested,[=](const QPoint &)
        {
        if(!IS_Translate2)
            pMenu->exec(QCursor::pos());
    });

    connect(pChangeImg, &QAction::triggered, this, &MyGraphicsView::slotChangeImgTriggered);
    connect(pCoordType, &QAction::triggered, this, &MyGraphicsView::slotCoordTypeTriggered);
    connect(pClear, &QAction::triggered, this, &MyGraphicsView::slotClearTriggered);
    connect(pTextColor, &QAction::triggered, this, &MyGraphicsView::slotTextColorTriggered);
}

void MyGraphicsView::showImage(const QString &filename)
{
    QImage image(filename);
    if(image.isNull()) return;
    slotClearTriggered();
//    QImage img = image.scaled(800,600,Qt::KeepAspectRatio); /* 图片压缩之后太模糊，弃用 */
//    imgSize = img.size();
//    this->resize(imgSize);
    imgSize = image.size();
    pScene->setSceneRect(-image.width()/2,-image.height()/2,image.width()*2, image.height()*2);
    pixmapItem->setPos(0,0);
//    pixmapItem->setPos((viewport()->width()-image.width())/2, (viewport()->height()-image.height())/2);
    pixmapItem->setPixmap(QPixmap::fromImage(image));
}
