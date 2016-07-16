#include "widget.h"

#include <QGraphicsItem>
#include <QTextStream>

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

    //QString str;
    //QTextStream(&str) << "posx:  " << bacteriaGrid[i][j] << "  posy:  " << allBacterias[0]->pos().y() << "  " << endl;
    //scene->addText(str);

    // as bacterias sao indistinguiveis.
    timerId = startTimer(1000 / 50);

    // xzinho no olho ela morreu
    // fazer uma funcao para encontrar a posicao da bacteria adjacente a alguma disponivel
    // replicar e imprimir as bacterias.

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
    Q_UNUSED(event);


    //


    // dance bacterias
    allBacterias[0]->moveBy(3,3);
}

void widget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 50);
}


// so pode entrar aqui se o numero de bacterias for menor do que nHorizon x nVert
// senao e loop infinito
void widget::findSlotToReplicate(int & x, int & y)
{
    int posx, posy;
    int zero = 0;
    while(true)
    {
        posx = randcpp(zero,nHorizon);
        posy = randcpp(zero,nVert);
        if(bacteriaGrid[posx][posy] != -1)
            continue;

        bool checkXp = (posx + 1) <= nHorizon;
        bool checkXm = (posx - 1) >= 0;
        bool checkYp = (posy + 1) <= nVert;
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


double widget::randcpp(double fMin, double fMax)
{
    double f = ((double)rand() / (double)(RAND_MAX));
    return fMin + f * (fMax - fMin);
}

int widget::randcpp(int fMin, int fMax)
{
    return fMin + (rand() % (int)(fMax - fMin + 1));
}
