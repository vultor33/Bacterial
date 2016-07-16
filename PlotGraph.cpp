#include "PlotGraph.h"

PlotGraph::PlotGraph(std::vector<double> & firstRow_in,
                     QWidget *parent)
    :QGraphicsView(parent)
{
    firstRow = firstRow_in;
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

    timerId = startTimer(1000 / 5);

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
    if(addingLine < (int)firstRow.size())
    {
        double y0 = firstRow[addingLine -1];
        double y1 = firstRow[addingLine];
        this->scene()->addLine(xOrigin + addingLine * xStep,
                               yOrigin - y0 ,
                               xOrigin + (1 + addingLine) * xStep,
                               yOrigin - y1,
                               QPen(Qt::blue, 2));
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

}
