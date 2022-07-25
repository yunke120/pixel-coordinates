#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void displayImage(const QString &fileName);
protected:

    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;

    QMenu *pMenu;
    QAction *pChangeImg;
    QAction *pClear;
    QString mFileName;

};

#endif // WIDGET_H
