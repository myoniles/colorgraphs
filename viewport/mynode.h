#ifndef MYNODE_H
#define MYNODE_H
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QLabel>
#include <vector>
#include "graph.h"
#include "user.h"
#include "dialog.h"


class MyNode : public QGraphicsEllipseItem{
private:
    vector<QGraphicsLineItem*>* lines;
    Dialog* d;
    Map* m;
    int nodeNum;

public:
    MyNode(){
    }



    MyNode( const QRectF &rect, Map* refMap, int n, Dialog* dia) : QGraphicsEllipseItem(rect){
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
        setAcceptHoverEvents(true);
        nodeNum = n;
        m = refMap;
        d = dia;
    }


    void hoverEnterEvent(QGraphicsSceneHoverEvent* event){

        QGraphicsScene* scene = this->scene();
        lines = new vector<QGraphicsLineItem*>;

        vector<int> connections = m->getNodes().at(nodeNum).getConnections();

        for ( int i = 0; i < connections.size(); i++){

            lines->push_back(d->connectNodes(nodeNum, connections[i]));
        }

        return update();
    }




    QVariant itemChange(GraphicsItemChange change, const QVariant &value){
        if (change == ItemPositionChange && scene()){
            for ( int i = lines->size() - 1; i >= 0; i--){
                QPoint offset(rect().width(), rect().height());
                QLineF update( value.toPointF() + offset, lines->at(i)->line().p2());
                lines->at(i)->setLine(update);
            }
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
        for ( int i = lines->size() - 1; i >= 0; i--){
            delete lines->at(i);
        }
        return update();
    }

};

#endif // MYNODE_H
