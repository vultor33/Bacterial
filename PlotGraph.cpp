#include "PlotGraph.h"

PlotGraph::PlotGraph(QWidget *parent)
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
    setWindowTitle(tr("Bacterial Growth - Graph"));

    timerId = startTimer(1000 / 50);
}



void PlotGraph::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "Timer ID:" << event->timerId();

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
}
