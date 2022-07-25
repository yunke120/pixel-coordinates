#ifndef PAINTLABEL_H
#define PAINTLABEL_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class PaintLabel : public QLabel
{
public:
    PaintLabel(QWidget *parent = nullptr);

    void showImage(QImage);
    void showText(QPainter *painter, QList<QPoint> pointL);
    void setTextColor(QColor color);

    QList<QPoint> gPointList;
protected:
    void paintEvent(QPaintEvent *);

private:
    QImage mImage;
    QColor mTextColor;
};




#endif // PAINTLABEL_H
