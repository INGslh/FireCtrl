/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "item.h"//自定义头文件，定义若干对item操作的函数
#include <QtWidgets>

extern bool flag_help_selected;
extern bool flag_dangerous_selected;
extern bool flag_enter_selected;
extern bool flag_exit_selected;
extern bool flag_wall_selected;//定义若干外部变量作为标志，用于判断该item是否被选择


Chip::Chip(int x, int y)//新建“障碍物”item函数
{
    this->x = x;//确定新建item的坐标x
    this->y = y;//确定新建item的坐标y
    this->color = color;//选择颜色
    setZValue((x + y) % 2);//确定该item位于scene的层数
    setFlags(ItemIsSelectable | ItemIsMovable);//障碍物item可被选中和可移动
    setAcceptHoverEvents(true);//可以接受外部事件，例如鼠标点击
}

QRectF Chip::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath Chip::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void Chip::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);


    painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/blackwall.png"));
/*
    if(option->state & QStyle::State_Selected)
      {
        QColor fillColor=QColor(255,0,0,150);
        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(4, 4, 32, 32);
        painter->setBrush(b);
        return;
      }
    //QColor fillColor = (option->state & QStyle::State_Selected) ? Qt::green.light(150) : color;
    /*if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.2) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(13, 13, 97, 57);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);

    if (lod >= 1) {
        painter->setPen(QPen(Qt::gray, 1));
        painter->drawLine(15, 54, 94, 54);
        painter->drawLine(94, 53, 94, 15);
        painter->setPen(QPen(Qt::black, 0));
    }

    // Draw text
    if (lod >= 2) {
        QFont font("Times", 10);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->scale(0.1, 0.1);
        painter->drawText(170, 180, QString("Model: VSC-2000 (Very Small Chip) at %1x%2").arg(x).arg(y));
        painter->drawText(170, 200, QString("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
        painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
        painter->restore();
    }

    // Draw lines
    QVarLengthArray<QLineF, 36> lines;
    if (lod >= 0.5) {
        for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
            lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
        }
        for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
            lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
        }
    }
    if (lod >= 0.4) {
        const QLineF lineData[] = {
            QLineF(25, 35, 35, 35),
            QLineF(35, 30, 35, 40),
            QLineF(35, 30, 45, 35),
            QLineF(35, 40, 45, 35),
            QLineF(45, 30, 45, 40),
            QLineF(45, 35, 55, 35)
        };
        lines.append(lineData, 6);
    }
    painter->drawLines(lines.data(), lines.size());

    // Draw red ink
    if (stuff.size() > 1) {
        QPen p = painter->pen();
        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::NoBrush);
        QPainterPath path;
        path.moveTo(stuff.first());
        for (int i = 1; i < stuff.size(); ++i)
            path.lineTo(stuff.at(i));
        painter->drawPath(path);
        painter->setPen(p);
    }*/
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Chip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

Dangerous::Dangerous(int x, int y)
{
    this->x = x;
    this->y = y;
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

HelpItem::HelpItem(int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF HelpItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath HelpItem::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void HelpItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/help.png"));
}

void HelpItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void HelpItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void HelpItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

PathItem::PathItem(int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF PathItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath PathItem::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void PathItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);
  Q_UNUSED(option);
  Q_UNUSED(painter);

  /*if(flag_selected && flag_help_selected ){
      static unsigned int i = 0;
      painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/help.png"));
      help_point[++i] = scenePos();
      qDebug()<< "help_point[i]"<< i << help_point[i];
      flag_selected = false ;
    }
  else if(flag_selected && flag_dangerous_selected ){
      static unsigned int i = 0;
      painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/dangerous.png"));
      dangerous_point[++i] = scenePos();
      qDebug()<< "dangerous_point[i]"<<i <<dangerous_point[i];
      flag_selected = false;
    }
  else if(flag_selected && flag_enter_selected ){
      painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/painter.png"));
      //flag_selected = false;
      return;
    }
  else if(flag_selected && flag_exit_selected ){
      painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/exit.png"));
      //flag_selected = false;
      return;
    }
  else if(flag_selected && flag_wall_selected ){
      static unsigned int i = 0;
      painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/blackwall.png"));
      wall_point[++i] = scenePos();
      qDebug()<< "wall_point[i]"<< i <<wall_point[i];
      flag_selected = false;
      return;
    }*/
}

void PathItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"item position"<<event->scenePos();
    QGraphicsItem::mousePressEvent(event);
    flag_selected = true;
    //update();//转到paint函数
}

void PathItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    //flag_selected = false;
    QGraphicsItem::mouseMoveEvent(event);
}

void PathItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    //update();
}

ExitItem::ExitItem(int x, int y)
{
    this->x = x;
    this->y = y;
    setZValue((x + y) % 2);
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF ExitItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath ExitItem::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void ExitItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);


    painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/exit.png"));
}

void ExitItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void ExitItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void ExitItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

EnterItem::EnterItem(int x, int y)
{
    this->x = x;
    this->y = y;
    setZValue((x + y) % 2);
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF EnterItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

QPainterPath EnterItem::shape() const
{
    QPainterPath path;
    path.addRect(4, 4, 32, 32);
    return path;
}

void EnterItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(QRect(4,4,32,32),QPixmap(":/enter.png"));
}

void EnterItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void EnterItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void EnterItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

