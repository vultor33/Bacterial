#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H


#include <QGraphicsView>
#include <vector>


class PlotGraph : public QGraphicsView
{
    Q_OBJECT

public:
    PlotGraph(std::vector<double> & firstRow_in, QWidget *parent = 0);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    std::vector<double> firstRow;
    int timerId;
    int sceneX;
    int sceneY;
    int sceneHeigth;
    int sceneWidth;

    int xOrigin;
    int yOrigin;
    int xMax;
    int yMax;

    int nPlottingPoints;
    int addingLine;

};

#endif // PLOTGRAPH_H
