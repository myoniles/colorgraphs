#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QLabel>
#include <vector>
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
    double toPolar(double start, double end);
    QGraphicsLineItem* connectNodes(int node1, int node2, int offset);
    QGraphicsLineItem* connectNodes(QPointF p1, int node2);
    ~Dialog();

   public slots:
    bool testUser();
    void quickTest();
    void testSpoof();

private:
    Ui::Dialog *ui;
    QGraphicsScene* scene;
    User* prove;
    User* verify;
    QLabel* status;
    QGraphicsLineItem* lastTestLine;
    void mapUser(User* u, int offset);



};


#endif // DIALOG_H

