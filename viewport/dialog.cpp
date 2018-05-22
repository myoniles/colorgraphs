#include "dialog.h"
#include "ui_dialog.h"
#include "mynode.h"

#include <vector>
#include <unistd.h>

//Define some colors for the graph. Gray will define unknown colors
QBrush colorScheme[3] = {QBrush(Qt::red), QBrush(Qt::blue), QBrush(Qt::green)};
QBrush grayBrush(Qt::gray);
QPen blackPen(Qt::black);

vector<MyNode*>* mapNodes = new vector<MyNode*>;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    connect(ui->fromFileButton, SIGNAL (released()), this, SLOT(fromFileButtonPress()));
    connect(ui->newMapButton, SIGNAL (released()), this, SLOT(genGraphButtonPress()));
    connect(ui->saveButton, SIGNAL (released()), this, SLOT(saveButtonPress()));
}

void Dialog::fromFileButtonPress(){
    return;
}

void Dialog::genGraphButtonPress(){
    m = new Map(10);
    updateMap();
    return;
}

void Dialog::saveButtonPress(){

    return;
}

QPointF Dialog::getNodePos(int n){
    return mapNodes->at(n)->pos();
}

QGraphicsLineItem* Dialog::connectNodes(int node1, int node2){
    double x1 = getNodePos(node1).x();
    double y1 = getNodePos(node1).y();
    double x2 = getNodePos(node2).x();
    double y2 = getNodePos(node2).y();
    return scene->addLine(x1,y1,x2,y2);
}

void Dialog::updateMap(){
    // delete old graph
    scene->clear();

    // We do not delete because that is already handled by the clear feature
    for ( int i = mapNodes->size() - 1; i >= 0; i--){
        mapNodes->pop_back();
    }

    // Draw New Graph
    int nodeNum = m->size();
    for ( int i = 0; i < nodeNum; i++){
        MyNode* newNode = new MyNode(QRectF(cos(toPolar(i,nodeNum))*nodeNum , sin(toPolar(i, nodeNum))* nodeNum, 10, 10), m, i, this);
        qDebug() << m->getNodeColor(i);
        newNode->setBrush(colorScheme[m->getNodeColor(i)]);
        mapNodes->push_back(newNode);
        scene->addItem(newNode);
    }
}

double Dialog::toPolar(double start, double end){
    return (start)/(end) *(2 * 3.141492);
}

Dialog::~Dialog()
{
    delete ui;
}
