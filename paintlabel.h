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

    enum COORD_TYPE{
        REALTIVE,
        ABSOLUTE
    };

    void showImage(QImage);
    void showText(QPainter *painter, QList<QPoint> pointL);
    void setTextColor(QColor color);
    void setCoordType(COORD_TYPE type);

    QList<QPoint> gPointList;
protected:
    void paintEvent(QPaintEvent *);

private:
    QImage mImage;
    QColor mTextColor;
    COORD_TYPE mCoordType;
};




#endif // PAINTLABEL_H
