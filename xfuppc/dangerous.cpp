#include "chip.h"
#include <QtWidgets>

Dangerous::Dangerous(int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Dangerous::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath Dangerous::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void Dangerous::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);


    painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/dangerous.png"));
}

void Dangerous::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Dangerous::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Dangerous::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
