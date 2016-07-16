#include "widget.h"

#include <QGraphicsItem>
#include <QTextStream>
#include <QDebug>
#include <QTimerEvent>

#include <math.h>

#include "bacteria.h"

widget::widget(QWidget *parent)
    :QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneX = -250;
    sceneY = -250;
    sceneHeigth = 490;
    sceneWidth = 490;

    scene->setSceneRect(sceneX, sceneY, sceneHeigth, sceneWidth);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setWindowTitle(tr("Bacterial Growth"));

    bacteria * bact0 = new bacteria();
    QRectF bactSize = bact0->boundingRect();
    bacHorizonSize = bactSize.width();
    bacVertSize = bactSize.height();
    nHorizon = floor((double)sceneWidth/(double)bacHorizonSize);
    nVert = floor((double)sceneHeigth/(double)bacVertSize);
    bacteriaGrid.resize(nVert);
    for(int i = 0; i < nVert; i++)
    {
        bacteriaGrid[i].resize(nHorizon);
        for(int j = 0; j < nHorizon; j++)
        {
            bacteriaGrid[i][j] = -1;
        }
    }

    // first bacteria
    bacteria * bact1 = new bacteria();
    scene->addItem(bact1);
    allBacterias << bact1;
    bacteriaGrid[12][12] = 0;
    allBacterias[0]->setPos(12.5 * bacHorizonSize + sceneX, 12.5 * bacVertSize + sceneY);

    // as bacterias sao indistinguiveis.
    timerId = startTimer(1000 / 0.5);
    timerAnimation = startTimer(1000 / 5);
}


void widget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::blue);
    painter->setOpacity(0.7);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void widget::timerEvent(QTimerEvent *event)
{
    //qDebug() << "Timer ID:" << event->timerId();

    if (event->timerId() == timerId)
    {
        if(allBacterias.size() < nHorizon * nVert)
        {
            int iSlot, jSlot;
            findSlotToReplicate(iSlot, jSlot);
            int iBac = allBacterias.size();
            bacteriaGrid[iSlot][jSlot] = iBac;
            bacteria * bactn = new bacteria();
            this->scene()->addItem(bactn);
            allBacterias << bactn;
            allBacterias[iBac]->setPos((iSlot + 0.5) * bacHorizonSize + sceneX, (jSlot + 0.5) * bacVertSize + sceneY);
        }
    }


    if (event->timerId() == timerAnimation)
    {
        timerAnimation = startTimer(1000 / 5);
        //dance bacterias
        for(int i=0; i < allBacterias.size(); i++)
        {
            qreal maxStep = 6;
            QPointF bacIPos = findGridPosition(i);
            qreal xOriginalPos = ((bacIPos.x() + 0.5) * bacHorizonSize) + sceneX;
            qreal yOriginalPos = ((bacIPos.y() + 0.5) * bacVertSize) + sceneY;
            qreal xActualPos = allBacterias[i]->pos().x();
            qreal yActualPos = allBacterias[i]->pos().y();
            qreal dx = randcpp(-2.0,2.0);
            qreal dy = randcpp(-2.0,2.0);
            // > 0 tenho q andar pra frente
            if((xOriginalPos - xActualPos) > bacHorizonSize / maxStep )
            {
                if(dx < 0)
                    dx = -dx;
            }
            else if((xOriginalPos - xActualPos) < -bacHorizonSize / maxStep )
            {
                if(dx > 0)
                    dx = -dx;
            }
            if((yOriginalPos - yActualPos) > bacVertSize / maxStep )
            {
                if(dy < 0)
                    dy = -dy;
            }
            else if((yOriginalPos - yActualPos) < -bacVertSize / maxStep )
            {
                if(dy > 0)
                    dy = -dy;
            }
            if(allBacterias[i]->getDeadAlive())
                allBacterias[i]->moveBy(dx,dy);
        }
    }
}

// so pode entrar aqui se o numero de bacterias for menor do que nHorizon x nVert
// senao e loop infinito
void widget::findSlotToReplicate(int & x, int & y)
{
    int posx, posy;
    int zero = 0;
    while(true)
    {
        posx = randcpp(zero,nHorizon-1);
        posy = randcpp(zero,nVert-1);
        if(bacteriaGrid[posx][posy] != -1)
            continue;

        bool checkXp = (posx + 1) < nHorizon;
        bool checkXm = (posx - 1) >= 0;
        bool checkYp = (posy + 1) < nVert;
        bool checkYm = (posy - 1) >= 0;

        if(checkXp)
        {
            if(bacteriaGrid[posx+1][posy] != -1)
                break;
        }
        if(checkXm)
        {
            if(bacteriaGrid[posx-1][posy] != -1)
                break;
        }
        if(checkYp)
        {
            if(bacteriaGrid[posx][posy+1] != -1)
                break;
        }
        if(checkYm)
        {
            if(bacteriaGrid[posx][posy-1] != -1)
                break;
        }
    }
    x = posx;
    y = posy;
}

QPointF widget::findGridPosition(int iBac)
{
    for(int i=0; i<nHorizon; i++)
    {
        for(int j=0; j<nVert; j++)
        {
            if(bacteriaGrid[i][j] == iBac)
            {
                return QPointF(i,j);
            }
        }
    }
    return QPointF(0,0);
}

double widget::randcpp(double fMin, double fMax)
{
    double f = ((double)rand() / (double)(RAND_MAX));
    return fMin + f * (fMax - fMin);
}

int widget::randcpp(int fMin, int fMax)
{
    return fMin + (rand() % (int)(fMax - fMin + 1));
}


//QString str;
//QTextStream(&str) << "posx:  " << bacteriaGrid[i][j] << "  posy:  " << allBacterias[0]->pos().y() << "  " << endl;
//scene->addText(str);
