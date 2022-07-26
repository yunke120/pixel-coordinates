#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>
#include <QMouseEvent>

#include <QGraphicsView>
#include <QGraphicsRectItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QMenu *pMenu;
    QAction *pChangeImg;
    QAction *pCoordType;
    QAction *pTextColor;
    QAction *pClear;
    QString mFileName;
    bool IS_RELATIVE;


    QGraphicsScene *mScene;

};

#endif // WIDGET_H
