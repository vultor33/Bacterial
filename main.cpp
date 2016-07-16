#include <QApplication>

#include "widget.h"
#include "PlotGraph.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <vector>

// CONSTRUIR O VETOR INTEIRO E PASSAR PARA OS CARAS JA O RESULTADO
// A CADA TIME EVENT EU APENAS ATUALIZO A SITUACAO

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::vector<double> x(20);
    x[0] = 3;
    x[1] = 6;
    x[2] = 9;
    x[3] = 12;
    x[4] = 15;
    x[5] = 16;
    x[6] = 15;
    x[7] = 16;
    x[8] = 9;
    x[9] = 1;
    x[10] = 20;
    x[11] = 22;
    x[12] = 23;
    x[13] = 40;
    x[14] = 60;
    x[15] = 100;
    x[16] = 120;
    x[17] = 140;
    x[18] = 180;
    x[19] = 200;

    //bacterias
    //widget *pWidget = new widget;
    //grafico
    PlotGraph *pWidget = new PlotGraph(x);

    QMainWindow mainWindow;
    mainWindow.setFixedHeight(500);
    mainWindow.setFixedWidth(500);
    mainWindow.setCentralWidget(pWidget);
    mainWindow.show();

    return app.exec();

}

// crescimento de bacterias em placa de petri
// divide os bichos



