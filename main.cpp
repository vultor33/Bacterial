#include <QApplication>

#include "widget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>

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
