#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "graph.h"
#include "user.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    QGraphicsEllipseItem* MaptoArray(){
        Map m(10);
        QGraphicsEllipseItem arr[m.getSize()]= new QGraphicsEllipseItem[m.getSize()];
        return arr;
    }
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene* scene;
};

#endif // DIALOG_H
