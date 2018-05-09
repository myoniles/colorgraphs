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
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene* scene;
    double toPolar(double start, double end);
    void mapUser(User* u);
    void connectNodes(User u);
    void redrawLine();

};

#endif // DIALOG_H

