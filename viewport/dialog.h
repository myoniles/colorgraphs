#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
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
    QGraphicsLineItem* connectNodes(int node1, int node2);
    ~Dialog();

public slots:
    void genGraphButtonPress();
    void fromFileButtonPress();
    void saveButtonPress();

private:
    Ui::Dialog *ui;
    QGraphicsScene* scene;
    Map* m;
    double toPolar(double start, double end);
    QPointF getNodePos(int n);
    void updateMap();

};

#endif // DIALOG_H
