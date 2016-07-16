#include <QApplication>

#include "widget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>

// CONSTRUIR O VETOR INTEIRO E PASSAR PARA OS CARAS JA O RESULTADO
// A CADA TIME EVENT EU APENAS ATUALIZO A SITUACAO

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    widget *pWidget = new widget;

    QMainWindow mainWindow;
    mainWindow.setFixedHeight(500);
    mainWindow.setFixedWidth(500);
    mainWindow.setCentralWidget(pWidget);
    mainWindow.show();

    return app.exec();

}

// crescimento de bacterias em placa de petri
// divide os bichos



