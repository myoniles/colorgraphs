#include "dialog.h"
#include "mynode.h"
#include "ui_dialog.h"
#include <cstdlib>
#include <QGraphicsEllipseItem>
#include <QPushButton>
#include <unistd.h>
#include <sstream>

//Define some colors for the graph. Gray will define unknown colors
QBrush colorScheme[3] = {QBrush(Qt::red), QBrush(Qt::blue), QBrush(Qt::green)};
QBrush grayBrush(Qt::gray);
QPen blackPen(Qt::black);


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);

    // Set the scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Create test users
    prove = new User(5);
    verify = new User(prove, VERIFY);
    status = ui->status;

    status->setText("Status: Idle");

    mapUser(prove, -50 * 2);
    mapUser(verify, 50 * 2);

    connect( ui->pushButton_2, SIGNAL (released()), this, SLOT (testUser()) );
    connect ( ui->pushButton, SIGNAL (released()), this, SLOT (quickTest()));
}

double Dialog::toPolar(double start, double end){
    return (start)/(end) *(2 * 3.141492);
}

void Dialog::mapUser(User* u, int offset){
    int nodeNum = u->getSize();
    MyNode *nodeList[nodeNum] = {NULL};
    Map* toVis;
    if( u->getUserType() == VERIFY ){
        toVis = u->getNoColor();
    } else {
        toVis = u->commitToRecolor();
    }

    QGraphicsEllipseItem* newNode;
    for ( int i = 0; i < nodeNum; i++){
        MyNode* newNode = new MyNode(QRectF(cos(toPolar(i,nodeNum))*nodeNum + offset, sin(toPolar(i, nodeNum))* nodeNum, 10, 10), this);

        if(toVis->getNodeColor(i) == -1){
            newNode->setBrush(grayBrush);
        } else {
        newNode->setBrush(colorScheme[toVis->getNodeColor(i)]);
        }
        scene->addItem(newNode);

        // Traverse through all previous Nodes, set itself as the Node 1
        // This unfortunately makes the function O(n^2)

        /*vector<Node> connections = toVis->getNodes();
        for( int j = 0; i < connections.size(); j++){
            if(j >= i){
                break;
            } else {
                QGraphicsLineItem* line = scene->addLine(nodeList[j]->pos().x(), nodeList[j]->pos().y(),cos(toPolar(i,nodeNum))*nodeNum, sin(toPolar(i, nodeNum))* nodeNum, blackPen);
                newNode->drawLine(line, true);
                nodeList[j]->drawLine(line, false);
            }

        } */
        nodeList[i] = newNode;
    }
    return;
}

bool Dialog::testUser(){
    if ( prove->getSize() != verify->getSize()){
        return false;
    }

    Map* recol = prove->commitToRecolor();
    int checkNode1 =  rand() % recol->size();
    int checkNode2 = recol[0][checkNode1].getConnections()[ rand() % recol[0][checkNode1].getConnections().size()];

    bool passed = verify->requestRound(prove, checkNode1, checkNode2);

    if (!passed){
        stringstream ss;
        ss << "Status: TEST FAILED! Same color on Node #" << checkNode1 << " and Node #" << checkNode2;
        status->setText(ss.str().c_str());
    } else {
        status->setText("Status: Test Passed");
    }

    delete recol;
    return passed;
}

void Dialog::quickTest(){

    if ( prove->getSize() != verify->getSize()){
        return;
    }

    Map* recol = prove->commitToRecolor();

    for ( int i = 0; i < 100; i++){
        int checkNode1 =  rand() % recol->size();
        int checkNode2 = recol[0][checkNode1].getConnections()[ rand() % recol[0][checkNode1].getConnections().size()];
        bool passed = verify->requestRound(prove, checkNode1, checkNode2);


        if (!passed){
            stringstream ss;
            ss << "Status: TEST FAILED! Same color on Node #" << checkNode1 << " and Node #" << checkNode2;
            status->setText(ss.str().c_str());
            return;
        }
    }
    status->setText("Status: Test Passed.");
    delete recol;

}


QGraphicsLineItem* Dialog::connectNodes(int node1, int node2){
    Map* m = prove->getNoColor();
    int nodeNum = m->getSize();
    int offset = 0;
    int x1 = cos(toPolar(node1,nodeNum))*nodeNum + offset;
    int x2 = cos(toPolar(node2,nodeNum))*nodeNum + offset;
    int y1 = sin(toPolar(node1, nodeNum))* nodeNum;
    int y2 = sin(toPolar(node2, nodeNum))* nodeNum;
    return scene->addLine(x1, y1, x2, y2);

}

QGraphicsLineItem* Dialog::connectNodes(QPointF p1, int node2){
    Map* m = prove->getNoColor();
    int nodeNum = m->getSize();
    int offset = 50;
    int x1 = p1.x();
    int x2 = cos(toPolar(node2,nodeNum))*nodeNum + offset;
    int y1 = p1.y();
    int y2 = sin(toPolar(node2, nodeNum))* nodeNum;
    return scene->addLine(x1, y1, x2, y2);
}


Dialog::~Dialog()
{
    delete prove;
    delete verify;
    delete ui;
}
