#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H


#include <QGraphicsView>
#include <vector>


class PlotGraph : public QGraphicsView
{
    Q_OBJECT

public:
    PlotGraph(
            std::vector<double> & firstRow_in,
            std::vector<double> & secondRow_in,
            std::vector<double> & thirdRow_in,
            std::vector<double> & fourthRow_in,
            QWidget *parent = 0);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    std::vector<double> firstRow;
    std::vector<double> secondRow;
    std::vector<double> thirdRow;
    std::vector<double> fourthRow;
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

    double maxValue(std::vector<double> & x);

};

#endif // PLOTGRAPH_H
