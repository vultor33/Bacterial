#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H


#include <QGraphicsView>
#include <vector>


class PlotGraph : public QGraphicsView
{
    Q_OBJECT

public:
    PlotGraph(QWidget *parent = 0);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    int timerId;
};

#endif // PLOTGRAPH_H
