#include "dialog.h"
#include "ui_dialog.h"
#include <cstdlib>
#include <QGraphicsEllipseItem>

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
    User *prove = new User(100);
    User *verify = new User(*prove);

    mapUser(prove);

}

double Dialog::toPolar(double start, double end){
    return (start)/(end) *(2 * 3.141492);
}

void Dialog::mapUser(User* u){
    int nodeNum = u->getSize();
    Map* toVis;
    if( u->getUserType() == VERIFY ){
        toVis = u->getNoColor();
    } else {
        toVis = u->commitToRecolor();
    }

    QGraphicsEllipseItem* newNode;
    for ( int i = 0; i < nodeNum; i++){
        newNode = scene->addEllipse(cos(toPolar(i,nodeNum))*nodeNum, sin(toPolar(i, nodeNum))* nodeNum, 10, 10, blackPen, colorScheme[toVis->getNodeColor(i)] );
        newNode->setFlag(QGraphicsItem::ItemIsMovable);
        newNode->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    }
    return;
}

void Dialog::connectNodes(User u){
    int nodeNum = u.getSize();
    while (true){
        for(int i = 0; i < nodeNum; i++){
            // Create a Line but only if the node already exists
            //TODO: Create a way to connect nodes without over drawing and update when moved
            return;
        }
    }
}

void Dialog::redrawLine(){


}


Dialog::~Dialog()
{
    delete ui;
}
