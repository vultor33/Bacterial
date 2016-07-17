#include <QApplication>

#include "widget.h"
#include "PlotGraph.h"
#include "BacteriaSystem.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QDebug>
#include <vector>


// CONSTRUIR O VETOR INTEIRO E PASSAR PARA OS CARAS JA O RESULTADO
// A CADA TIME EVENT EU APENAS ATUALIZO A SITUACAO
// --> NAO - TEM QUE FAZER EM TEMPO REAL, MUDANDO OS PARAMETROS NA
//           HORA, AI SIM E EMOCAO.

int main(int argc, char *argv[])
{
    BacteriaSystem bac_;
    bac_.propagate();


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
    std::vector<double> a,b,c;
    a = x;
    b = x;
    c = x;
    for(size_t i =0; i < x.size(); i++)
    {
        a[i] -= i;
        b[i] = b[i] + i;
        c[i] *= 1.1;

    }
    x = bac_.getAlimento();
    a = bac_.getReagente();
    b = bac_.getMetabolito();
    c = bac_.getResiduo();
    qDebug() << x[0] << "   size   " << x.size() << endl;
    PlotGraph *pWidget = new PlotGraph(x,a,b,c);

    QMainWindow mainWindow;
    mainWindow.setFixedHeight(500);
    mainWindow.setFixedWidth(500);
    mainWindow.setCentralWidget(pWidget);
    mainWindow.show();

    return app.exec();

}

// crescimento de bacterias em placa de petri
// divide os bichos



