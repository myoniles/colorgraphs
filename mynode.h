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
    bool isP1;
    Dialog* d;

public:
    MyNode(){
    }



    MyNode( const QRectF &rect, Dialog* dia) : QGraphicsEllipseItem(rect){
        //setFlag(QGraphicsItem::ItemIsMovable);
        //setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
        setAcceptHoverEvents(true);
;
        d = dia;
    }


    void hoverEnterEvent(QGraphicsSceneHoverEvent* event){

        QGraphicsScene* scene = this->scene();
        lines = new vector<QGraphicsLineItem*>;


        for ( int i = 0; i <)
        lines->push_back(d->connectNodes(event->pos(), 3));


        return update();
    }


    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
        for ( int i = 0; i< lines->size(); i++){
            delete lines->at(i);
        }
        return update();
    }
};

#endif // MYNODE_H
