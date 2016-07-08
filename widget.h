#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QList>
#include <vector>

class widget : public QGraphicsView
{
    Q_OBJECT

public:
    widget(QWidget *parent = 0);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;




};

#endif // WIDGET_H
