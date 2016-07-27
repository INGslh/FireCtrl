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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QToolButton>
#include <QGraphicsScene>
#include <view.h>

extern bool flag_help_selected ;
extern bool flag_dangerous_selected ;
extern bool flag_enter_selected ;
extern bool flag_exit_selected ;
extern bool flag_wall_selected ;

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class MyScene;
class QSplitter;
QT_END_NAMESPACE
class Astar;

class MainWindow : public QWidget
{
    Q_OBJECT
  QGraphicsScene m_scene;
public:
    MainWindow(QWidget *parent = 0);
    QGraphicsScene *scene_1;

    Astar *astar;

    void populateScene();
    bool CalcNextPoint(int coord_x, int coord_y);
    bool FindPath(int end_x,int end_y,int start_x,int start_y,int temp);

public slots:
    void  InputXfData();
    void  Pathfinding();
    void  Displaypath();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *m);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *m);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *m);

private:
    View *view;
    QGraphicsItem *item;
    QGraphicsItem *help_item;
    QGraphicsItem *dangerous_item;
    QGraphicsRectItem *path_item;
    int Point_path[200][2];
    int path_num;
    void setupMatrix();
    QSplitter *h1Splitter;
    QSplitter *h2Splitter;
    QTimer *Path_timer;
};

/*******************A-star*************************/

enum APointType{
	APT_UNKNOWN, // 未知状态
	APT_OPENED, // 开放列表中
	APT_CLOSED, // 关闭列表中
	APT_STARTPOINT, // 起始点
	APT_ENDPOINT, // 结束点
	APT_ENDPOINT_TO,   //中间节点
	APT_OBSTACLE
};

enum HaveItem{
	ITEM_UNKOWN,
	ITEM_WALL,
	ITEM_DANGEROUS,
	ITEM_STARTpOINT,
	ITEM_ENDPOINT,
	ITEM_HELPPOINT
};

typedef struct _scene_infor{
          char status;
          int type = APT_UNKNOWN;
          int g;
          int h;
          int f;
          int haveitem = 0;
}*scene_infor;

class Astar : public QWidget
{
    Q_OBJECT
public :
  struct _SceneOne_infor{
    int type;
    int haveitem = 0;
    int g;
    int h;
    int f;
  }SceneOne_infor[20][20];
  int startPoint_x;
  int startPoint_y;
  int endPoint_x;
  int endPoint_y;
  int helpPoint_y[5];
  int helpPoint_x[5];
  int curpoint_x;
  int curpoint_y;




private:
  int m_nAPointArrWidth = 0;
  int m_nAPointArrHeight = 0;
  char* m_pOldArr;

public:
  int row_num;
 // PAPoint m_pShopPoint[24];
  void ReadxfCoord(scene_infor *SceneOne_infor, int nWidth, int nHeight);
  void SetStartPoint(int x, int y);
  void SetEndPoint(int x, int y);
  void SetOpened(int x, int y);
  void SetClosed(int x, int y);
  void SetCurrent(int x, int y);
  void PrintCharArr(char* pDateArr);
  //PAPoint CalcNextPoint(PAPoint ptCalc, char* pDateArr); // 应用迭代的办法进行查询
  //PAPoint FindPointPath(int x,int y,int temp);

};


#endif // MAINWINDOW_H
