#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
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

    enum COORD_TYPE{
            REALTIVE,
            ABSOLUTE
    };

    void showImage(const QString &filename);
protected:

    virtual void wheelEvent(QWheelEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event) ;
    virtual void mouseReleaseEvent(QMouseEvent *event) ;

private slots:
    void slotChangeImgTriggered();
    void slotCoordTypeTriggered();
    void slotTextColorTriggered();
    void slotClearTriggered();

private:

    void menuInit();

    QMenu *pMenu;
    QAction *pChangeImg;
    QAction *pCoordType;
    QAction *pTextColor;
    QAction *pClear;
    QString mFileName;
    bool IS_RELATIVE;

    bool IS_Translate;
    bool IS_Translate2;
    bool IS_Menu;

    QTimer *pTimer;
    QGraphicsScene *pScene;
    QGraphicsPixmapItem *pixmapItem;
    QList<QGraphicsSimpleTextItem *> mSimpleTextItemList;
    QColor mTextColor;

    QPoint mLastPos;
    QSize imgSize;

    COORD_TYPE mCoordType;


};

#endif // MYGRAPHICSVIEW_H
