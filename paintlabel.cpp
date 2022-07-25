#include "paintlabel.h"

PaintLabel::PaintLabel(QWidget *parent)
           : QLabel (parent)
           , mTextColor(QColor(0,255,0))
{

}

void PaintLabel::showImage(QImage image)
{
    mImage = image;
    update();
}

void PaintLabel::showText(QPainter *painter, QList<QPoint> pointL)
{
    painter->save();
    painter->setPen(mTextColor);
    for (int i = 0; i < pointL.size(); i++) {
        QPoint p = pointL.value(i);
        double w = double(p.x()) / width();
        double h = double(p.y()) / height();
        QString text = QString("(%1,%2)").arg(w, 4, 'g').arg(h, 4, 'g');
        painter->drawText(p, text);
    }
    painter->restore();
}

void PaintLabel::setTextColor(QColor color)
{
    mTextColor = color;
}

void PaintLabel::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,this->width(), this->height());
    if(mImage.isNull()) return;
    QImage img = mImage.scaled(this->size(), Qt::KeepAspectRatio);
    int x = this->width() - img.width();
    int y = this->height() - img.height();
    x = x >> 2;
    y = y >> 2;
    painter.drawImage(QPoint(x, y), img);
    showText(&painter, gPointList);
    painter.end();
}
