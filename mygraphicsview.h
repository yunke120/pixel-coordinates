#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QTimer>

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr);
    ~MyGraphicsView();

    void showImage(const QString &filename);
protected:

    virtual void wheelEvent(QWheelEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event) ;
    virtual void mouseReleaseEvent(QMouseEvent *event) ;


private:

    void zoomIn();
    void zoomOut();

    QMenu *pMenu;
    QAction *pChangeImg;
    QAction *pCoordType;
    QAction *pTextColor;
    QAction *pClear;
    QString mFileName;
    bool IS_RELATIVE;


    QTimer *pTimer;
    QGraphicsScene *pScene;
    QGraphicsPixmapItem *pixmapItem;
    bool IS_Translate;
    QPoint mLastPos;


};

#endif // MYGRAPHICSVIEW_H
