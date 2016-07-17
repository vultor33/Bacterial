#include "PlotGraph.h"

#include <QGraphicsTextItem>

PlotGraph::PlotGraph(std::vector<double> & firstRow_in,
                     std::vector<double> & secondRow_in,
                     std::vector<double> & thirdRow_in,
                     std::vector<double> & fourthRow_in,
                     QWidget *parent)
    :QGraphicsView(parent)
{
    firstRow = firstRow_in;
    secondRow = secondRow_in;
    thirdRow = thirdRow_in;
    fourthRow = fourthRow_in;
    nPlottingPoints = firstRow.size();
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneX = -250;
    sceneY = -250;
    sceneHeigth = 490;
    sceneWidth = 490;

    xOrigin = sceneX + 30;
    yOrigin = sceneY + sceneHeigth - 80;
    xMax = sceneX + sceneWidth - 30;
    yMax = sceneY + 30;

    scene->setSceneRect(sceneX, sceneY, sceneHeigth, sceneWidth);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setWindowTitle(tr("Bacterial Growth - Graph"));

    timerId = startTimer(1000 / 50);

    addingLine = 0;
}



void PlotGraph::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "Timer ID:" << event->timerId();

    //ATENCAO - y e invertido

    // uma linha e uma coluna cheia de numero.
    // x e o t.
    // e o y max e minimo deve ser reescalonado para caber aqui, ou limitado de alguma forma.

    addingLine++;
    int xStep = (xMax - xOrigin) / nPlottingPoints;
    double maxY = maxValue(firstRow) / (-yMax + yOrigin);
    if(addingLine < (int)firstRow.size())
    {
        double y1a = firstRow[addingLine -1] / maxY;
        double y1b = firstRow[addingLine] / maxY;
        this->scene()->addLine(xOrigin + (-1 + addingLine) * xStep,
                               yOrigin - y1a,
                               xOrigin + addingLine * xStep,
                               yOrigin - y1b,
                               QPen(Qt::blue, 2));

        if(secondRow.size() > 0)
        {

            double y2a = secondRow[addingLine -1] / maxY;
            double y2b = secondRow[addingLine] / maxY;
            this->scene()->addLine(xOrigin + (-1 + addingLine) * xStep,
                               yOrigin - y2a,
                               xOrigin + addingLine * xStep,
                               yOrigin - y2b,
                               QPen(Qt::darkGreen, 2));
        }
        if(thirdRow.size() > 0)
        {

            double y3a = thirdRow[addingLine -1] / maxY;
            double y3b = thirdRow[addingLine] / maxY;
            this->scene()->addLine(xOrigin + (-1 + addingLine) * xStep,
                               yOrigin - y3a,
                               xOrigin + addingLine * xStep,
                               yOrigin - y3b,
                               QPen(Qt::darkRed, 2));
        }
        if(fourthRow.size() > 0)
        {

            double y4a = fourthRow[addingLine -1] / maxY;
            double y4b = fourthRow[addingLine] / maxY;
            this->scene()->addLine(xOrigin + (-1 + addingLine) * xStep,
                               yOrigin - y4a,
                               xOrigin + addingLine * xStep,
                               yOrigin - y4b,
                               QPen(Qt::darkGray, 2));
        }



    }



    // bate aqui ele adiciona um ponto para todas as concentracoes
    // seria legal se a cada vez que reproduzisse ele criasse uma nova janela de evolucao.
}

void PlotGraph::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::white);
    painter->setOpacity(0.7);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(QPointF(sceneX + 30, sceneY + 30), QPointF(sceneX + 30, sceneY + sceneHeigth - 30));
    painter->drawLine(QPointF(sceneX + 20, sceneY + sceneHeigth - 80), QPointF(sceneX + sceneWidth - 30, sceneY + sceneHeigth - 80));


    painter->setPen(QPen(Qt::blue, 3));
    painter->drawEllipse(QPointF(sceneX+50,sceneY+30),5,5);
    painter->setPen(QPen(Qt::darkGreen, 3));
    painter->drawEllipse(QPointF(sceneX+50,sceneY+50),5,5);
    painter->setPen(QPen(Qt::darkRed, 3));
    painter->drawEllipse(QPointF(sceneX+50,sceneY+70),5,5);
    painter->setPen(QPen(Qt::darkGray, 3));
    painter->drawEllipse(QPointF(sceneX+50,sceneY+90),5,5);

    QGraphicsTextItem *text1 = this->scene()->addText("Alimento");
    QGraphicsTextItem *text2 = this->scene()->addText("Reagente");
    QGraphicsTextItem *text3 = this->scene()->addText("Metabolito");
    QGraphicsTextItem *text4 = this->scene()->addText("Residuo");
    text1->setPos(sceneX+60,sceneY+20);
    text2->setPos(sceneX+60,sceneY+40);
    text3->setPos(sceneX+60,sceneY+60);
    text4->setPos(sceneX+60,sceneY+80);


}

double PlotGraph::maxValue(std::vector<double> & x)
{
    int iMax = 0;
    double max = x[iMax];
    for(size_t i = 1; i < x.size(); i++)
    {
        if(x[i] > max)
        {
            iMax = i;
            max = x[i];
        }
    }
    return max;
}
