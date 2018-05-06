#include "dialog.h"
#include "ui_dialog.h"
#include "graph.h"
#include "user.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Set the scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    //Define some colors for the graph. Gray will define unknown colors
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);

    // TEST
    scene->addEllipse(50,50, 100, 100, blackPen, redBrush);

    // Make an array to hold nodes
    //QGraphicsItem* map1 = new QgraphicsItem[10];
}

Dialog::~Dialog()
{
    delete ui;
}
