#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QMouseEvent>

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

//    virtual void wheelEvent(QWheelEvent *event);


private:
    Ui::Widget *ui;






};

#endif // WIDGET_H
