#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QList>
#include <vector>

#include "bacteria.h"

class widget : public QGraphicsView
{
    Q_OBJECT

public:
    widget(QWidget *parent = 0);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;


private:
    int timerId;
    int timerAnimation;
    QList<bacteria *> allBacterias;

    bacteria * bact1;
    std::vector< std::vector<int> > bacteriaGrid;

    int sceneX;
    int sceneY;
    int sceneHeigth;
    int sceneWidth;
    qreal bacHorizonSize;
    qreal bacVertSize;
    int nHorizon;
    int nVert;

    void findSlotToReplicate(int & x, int & y);
    QPointF findGridPosition(int iBac);
    double randcpp(double fMin, double fMax);
    int randcpp(int fMin, int fMax);

};

#endif // WIDGET_H
