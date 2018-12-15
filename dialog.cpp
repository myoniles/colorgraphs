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
    prove = new User(150);
    verify = new User(prove, VERIFY);
    status = ui->status;

    // init status
    status->setText("Status: Idle");

    // create the maps!
    mapUser(prove, -200 * 2);
    mapUser(verify, 200 * 2);

    // House keeping for the buttons
    connect( ui->pushButton_2, SIGNAL (released()), this, SLOT (testUser()) );
    connect ( ui->pushButton, SIGNAL (released()), this, SLOT (quickTest()));
    connect(ui->pushButton_3, SIGNAL (released()), this, SLOT(testSpoof()));
}


// simple mapping to polar
double Dialog::toPolar(double start, double end){
    return (start)/(end) *(2 * 3.141492);
}

void Dialog::mapUser(User* u, int offset){
    int nodeNum = u->getSize();

    Map* toVis;
    if( u->getUserType() == VERIFY ){
        toVis = u->getNoColor();
    } else {
        toVis = u->commitToRecolor();
    }

    QGraphicsEllipseItem* newNode;
    // Create a new node mapped to a polar coordinate based on the size of the graph
    for ( int i = 0; i < nodeNum; i++){
        MyNode* newNode = new MyNode(QRectF(cos(toPolar(i,nodeNum))*nodeNum + offset, sin(toPolar(i, nodeNum))* nodeNum, 10, 10), toVis, i, this);

        // Handle the node's color
        if(toVis->getNodeColor(i) == -1){
            newNode->setBrush(grayBrush);
        } else {
        newNode->setBrush(colorScheme[toVis->getNodeColor(i)]);
        }
        // draw to the scene
        scene->addItem(newNode);
    }
    return;
}

bool Dialog::testUser(){
    // Get rid of any line that was already there from a previous test
    if(lastTestLine != NULL){
        delete lastTestLine;
    }
    // If there is a mishap in the comparisons of graphs, exit
    if ( prove->getSize() != verify->getSize()){
        return false;
    }

    // Get a recoloring, get a random node, then a random node connected to said node
    Map* recol = prove->commitToRecolor();
    int checkNode1 =  rand() % recol->size();
    int checkNode2 = recol[0][checkNode1].getConnections()[ rand() % recol[0][checkNode1].getConnections().size()];

    // Then make a call comparing those two nodes
    bool passed = verify->requestRound(prove, checkNode1, checkNode2);

    if (!passed){
        stringstream ss;
        ss << "Status: TEST FAILED! Same color on Node #" << checkNode1 << " and Node #" << checkNode2;
        status->setText(ss.str().c_str());
    } else {
        status->setText("Status: Test Passed");
    }

    lastTestLine = connectNodes(checkNode1, checkNode2, -200);
    delete recol;
    return passed;
}

void Dialog::testSpoof(){

    // Draw the Graph
    User* snoop = new User(prove, USERTYPE::SNOOP);
    // Honestly He could do a better job at guessing
    snoop->guess();
    Map* toVis = snoop->commitToRecolor();
    int nodeNum = toVis->size();
    // For node in the graph
    for ( int i = 0; i < nodeNum; i++){
        // map to polar
        MyNode* newNode = new MyNode(QRectF(cos(toPolar(i,nodeNum))*nodeNum , sin(toPolar(i, nodeNum))* nodeNum, 10, 10), toVis, i, this);
        if(toVis->getNodeColor(i) == -1){
            newNode->setBrush(grayBrush);
        } else {
        newNode->setBrush(colorScheme[toVis->getNodeColor(i)]);
        }
        scene->addItem(newNode);
    }

    for ( int i = 0; i < 100; i++){
        int checkNode1 =  rand() % toVis->size();
        int checkNode2 = toVis[0][checkNode1].getConnections()[ rand() % toVis[0][checkNode1].getConnections().size()];
        bool passed = verify->requestRound(snoop, checkNode1, checkNode2);


        if (!passed){
            stringstream ss;
            ss << "Status: TEST FAILED! Same color on Node #" << checkNode1 << " and Node #" << checkNode2;
            status->setText(ss.str().c_str());

            if(lastTestLine != NULL){
                delete lastTestLine;
            }

            lastTestLine = connectNodes(checkNode1,checkNode2,0);

            return;
        }
    }
    status->setText("Status: Test Passed.");
    return;
}

// will only compare 100 nodes
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


QGraphicsLineItem* Dialog::connectNodes(int node1, int node2, int offset){
    Map* m = prove->getNoColor();
    int nodeNum = m->getSize();
    int x1 = cos(toPolar(node1,nodeNum))*nodeNum + offset*2;
    int x2 = cos(toPolar(node2,nodeNum))*nodeNum + offset*2;
    int y1 = sin(toPolar(node1, nodeNum))* nodeNum;
    int y2 = sin(toPolar(node2, nodeNum))* nodeNum;
    return scene->addLine(x1, y1, x2, y2);

}

QGraphicsLineItem* Dialog::connectNodes(QPointF p1, int node2){
    Map* m = prove->getNoColor();
    int nodeNum = m->getSize();
    int offset;
    if(p1.x() >= 200){
        offset = 400;
    } else if (p1.x() <= -200){
        offset = -400;
    } else {
        offset = 0;
    }

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
