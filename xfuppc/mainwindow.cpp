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

#include "item.h"
#include "mainwindow.h"
#include "view.h"
#include <time.h>
#include <QHBoxLayout>
#include <QGraphicsSceneEvent>
#include <QSplitter>
#include <QDebug>
#include <QTimer>

static int flag_checkScene = 0;



bool flag_help_selected = false;
bool flag_dangerous_selected = false;
bool flag_enter_selected = false;
bool flag_exit_selected = false;
bool flag_wall_selected = false;



class Astar;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QPalette paletteMainWindow(this->palette());
    paletteMainWindow.setColor(QPalette::Background,Qt::lightGray);
    this->setPalette(paletteMainWindow);

    populateScene();

    h1Splitter = new QSplitter;
    h2Splitter = new QSplitter;

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);

    view = new View("ONE view");

    connect(view->InputDataBtn,SIGNAL(clicked()),this,SLOT(InputXfData()));
    connect(view->Btn_Pathfinding,SIGNAL(clicked()),this,SLOT(Pathfinding()));

    view->view()->setScene(scene_1);
    h1Splitter->addWidget(view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("Z-FireMan"));
    view->EditWindow->setFontPointSize(20);
    view->EditWindow->setFontFamily("simsun");
    view->EditWindow->setPlainText("Z-FIREMAN RUNING\n");
    view->EditWindow->append("--------------------------");
}


void MainWindow::InputXfData()
{
  srand(time(NULL));
  QString help_x,help_y;
  int Distance[3];
  int intNumberHelp =  view->combobox->currentIndex()+1;
  qDebug()<<"numberhelp"<<intNumberHelp;

  for(int i=0;i<intNumberHelp;i++)
    {
      astar->helpPoint_x[i] = rand()%18 ;
      astar->helpPoint_x[i]++;
      astar->helpPoint_y[i] = rand()%18 ;
      astar->helpPoint_y[i]++;
      if(astar->SceneOne_infor[astar->helpPoint_x[i]][astar->helpPoint_y[i]].haveitem ){
          astar->helpPoint_x[i] = rand()%3 ;
          astar->helpPoint_x[i] +=5 ;//避免与墙重合
          astar->helpPoint_y[i] = rand()%18 ;
          astar->helpPoint_y[i]++;
       }
      Distance[i]= astar->helpPoint_x[i] + astar->helpPoint_y[i];
    }
  qDebug()<<"Distance"<<Distance[0]<<Distance[1]<<Distance[2];
  qDebug()<<"qian_helpPoint[0]"<<astar->helpPoint_x[0]<<astar->helpPoint_y[0];
  qDebug()<<"qian_helpPoint[1]"<<astar->helpPoint_x[1]<<astar->helpPoint_y[1];
  qDebug()<<"qian_helpPoint[2]"<<astar->helpPoint_x[2]<<astar->helpPoint_y[2];
  int torlent_x,torlent_y;
  if(intNumberHelp == 2){
      if(Distance[0]>Distance[1]){
          torlent_x = astar->helpPoint_x[0];
          torlent_y = astar->helpPoint_y[0];
          astar->helpPoint_x[0] = astar->helpPoint_x[1];
          astar->helpPoint_y[0] = astar->helpPoint_y[1];
          astar->helpPoint_x[1] = torlent_x;
          astar->helpPoint_y[1] = torlent_y;
        }
    }
  else if(intNumberHelp == 3){//3个数排序
      if(Distance[0]>Distance[1]){
          if(Distance[2]>Distance[0]){
              torlent_x = astar->helpPoint_x[1];
              torlent_y = astar->helpPoint_y[1];
              astar->helpPoint_x[1] = astar->helpPoint_x[0];
              astar->helpPoint_y[1] = astar->helpPoint_y[0];
              astar->helpPoint_x[0] = torlent_x;
              astar->helpPoint_y[0] = torlent_y;
            }
          else if(Distance[2]<Distance[1]){
              torlent_x = astar->helpPoint_x[2];
              torlent_y = astar->helpPoint_y[2];
              astar->helpPoint_x[2] = astar->helpPoint_x[0];
              astar->helpPoint_y[2] = astar->helpPoint_y[0];
              astar->helpPoint_x[0] = torlent_x;
              astar->helpPoint_y[0] = torlent_y;
            }
          else{
              torlent_x = astar->helpPoint_x[0];
              torlent_y = astar->helpPoint_y[0];
              astar->helpPoint_x[0] = astar->helpPoint_x[1];
              astar->helpPoint_y[0] = astar->helpPoint_y[1];
              astar->helpPoint_x[1] = astar->helpPoint_x[2];
              astar->helpPoint_y[1] = astar->helpPoint_y[2];
              astar->helpPoint_x[2] = torlent_x;
              astar->helpPoint_y[2] = torlent_y;
            }
        }
      else if(Distance[1]>Distance[0]){
          if(Distance[2]>Distance[1]){

            }
          else if(Distance[2]<Distance[0]){
              torlent_x = astar->helpPoint_x[2];
              torlent_y = astar->helpPoint_y[2];
              astar->helpPoint_x[2] = astar->helpPoint_x[1];
              astar->helpPoint_y[2] = astar->helpPoint_y[1];
              astar->helpPoint_x[1] = astar->helpPoint_x[0];
              astar->helpPoint_y[1] = astar->helpPoint_y[0];
              astar->helpPoint_x[0] = torlent_x;
              astar->helpPoint_y[0] = torlent_y;
            }
          else{
              torlent_x = astar->helpPoint_x[2];
              torlent_y = astar->helpPoint_y[2];
              astar->helpPoint_x[2] = astar->helpPoint_x[1];
              astar->helpPoint_y[2] = astar->helpPoint_y[1];
              astar->helpPoint_x[1] = torlent_x;
              astar->helpPoint_y[1] = torlent_y;
            }
        }
    }
  qDebug()<<"hou_helpPoint[0]"<<astar->helpPoint_x[0]<<astar->helpPoint_y[0];
  qDebug()<<"hou_helpPoint[1]"<<astar->helpPoint_x[1]<<astar->helpPoint_y[1];
  qDebug()<<"hou_helpPoint[2]"<<astar->helpPoint_x[2]<<astar->helpPoint_y[2];
  for(int i=0;i<intNumberHelp;i++)
    {
      help_item = new HelpItem(astar->helpPoint_x[i],astar->helpPoint_y[i]);
      astar->SceneOne_infor[astar->helpPoint_x[i]][astar->helpPoint_y[i]].haveitem = ITEM_HELPPOINT ;//help
      help_item -> setPos(QPoint((40*astar->helpPoint_x[i]-400),(40*astar->helpPoint_y[i]-400)));
      scene_1->addItem(help_item);
      help_x = QString::number(astar->helpPoint_x[i]);
      help_y = QString::number(astar->helpPoint_y[i]);
      view->EditWindow->append("HelpPoint: "+ help_x +","+help_y[i]);
      view->EditWindow->append("DangerousPoint: ");
    }


  int xx=0;
  for(int i =-400;  i<400 ;i +=40){
      int yy = 0;
      for(int j =-400; j<400 ;j +=40)
      {
         int temp = rand()% 30;
         if(!temp && astar->SceneOne_infor[xx][yy].haveitem == ITEM_UNKOWN)
         {
           if((xx==1&&yy==1)||(xx==18&&yy==18))
             break;
           dangerous_item = new Dangerous(xx,yy);
           view->EditWindow->append(QString::number(xx,10)+","+QString::number(yy,10));
           dangerous_item->setPos(QPointF(i, j));
           astar->SceneOne_infor[xx][yy].haveitem = ITEM_DANGEROUS ;//dangerous
           scene_1->addItem(dangerous_item);
         }
         yy++;
      }
      xx++;
    }
  int i=0;
  for(int x_num =0;x_num <20 ;x_num++){//起始为1，终止为20
      for(int y_num =0;y_num<20 ;y_num++){
          switch(astar->SceneOne_infor[x_num][y_num].haveitem)
          {
            case ITEM_UNKOWN:
              astar->SceneOne_infor[x_num][y_num].type = APT_UNKNOWN;
              break;
            case ITEM_WALL:
              astar->SceneOne_infor[x_num][y_num].type = APT_OBSTACLE;
              break;
            case ITEM_DANGEROUS:
              astar->SceneOne_infor[x_num][y_num].type = APT_OBSTACLE;
              break;
            case ITEM_STARTpOINT:
              astar->SceneOne_infor[x_num][y_num].type = APT_STARTPOINT;
              astar->startPoint_x = x_num;
              astar->startPoint_y = y_num;
              break;
           case ITEM_ENDPOINT:
              astar->SceneOne_infor[x_num][y_num].type = APT_ENDPOINT;
              astar->endPoint_x = x_num;
              astar->endPoint_y = y_num;
              break;
           case ITEM_HELPPOINT:
              astar->SceneOne_infor[x_num][y_num].type = APT_ENDPOINT_TO;
              astar->helpPoint_x[i] = x_num;
              astar->helpPoint_y[i] = y_num;
              i++;
            default:
            break;
        }
        astar->SceneOne_infor[x_num][y_num].g = 0;
        astar->SceneOne_infor[x_num][y_num].h = 0;
        astar->SceneOne_infor[x_num][y_num].f = 0;
      }
    }
  //qDebug()<<"helpPoint_1"<<astar->helpPoint_x[0]<<astar->helpPoint_y[0];
  //qDebug()<<"helpPoint_2"<<astar->helpPoint_x[1]<<astar->helpPoint_y[1];
}


void MainWindow::populateScene()
{
    scene_1 = new QGraphicsScene;
    QPalette palette_scene = scene_1->palette();
    palette_scene.setColor(QPalette::Background,Qt::lightGray);
    astar = new Astar;

    for( int num =0; num<5 ;num++){
        astar->helpPoint_x[num]=0;
        astar->helpPoint_y[num]=0;
      }

    for(int line=-400;line<=400; line +=40)//向所有场景画坐标系
      {
        QGraphicsItem *scene_1_item_lie = new QGraphicsLineItem(line,-400,line,400);
        QGraphicsItem *scene_1_item_hang = new QGraphicsLineItem(-400,line,400,line);

        scene_1->addItem(scene_1_item_lie);
        scene_1->addItem(scene_1_item_hang);

      }
    int xx = 0;
    bool flag_scene_1=false;
    for (int i = -400; i < 400; i += 40) {
        int yy = 0;
        for (int j = -400; j < 400; j += 40) {
            if((xx == 0&&yy!=0)||(xx ==19&&yy!=19)
               ||(yy==0&&xx!=0)||(yy==19&&xx!=19)||(xx==0&&yy==0)||xx==19&&yy==19)
              {
                if(xx==19&&yy==18){
                    item = new ExitItem(xx,yy);
                    astar->SceneOne_infor[xx][yy].haveitem = ITEM_ENDPOINT;//exit
                  }
                else if(xx==0&&yy==1){
                    item = new EnterItem(xx,yy);
                    astar->SceneOne_infor[xx][yy].haveitem = ITEM_STARTpOINT;//enter
                  }
                else{
                    item = new Chip(xx,yy);
                    astar->SceneOne_infor[xx][yy].haveitem = ITEM_WALL;
                  }
                flag_scene_1 = true;
              }
            else if(((xx>1&&xx<5)||(xx>7&&xx<11)||(xx>13&&xx<17))
                    &&((yy>2&&yy<5)||(yy>6&&yy<9)||(yy>10&&yy<13)||(yy>14&&yy<17)))
            {
              item = new Chip(xx,yy);
              flag_scene_1 = true;
              astar->SceneOne_infor[xx][yy].haveitem = 1;//chip
            }
            if(flag_scene_1)
            {
              item->setPos(QPointF(i, j));
              scene_1->addItem(item);//向scene_1加item
              flag_scene_1 = false;
            }
            yy++;
        }
        xx++;
    }
}

void MainWindow::Pathfinding()
{
  CalcNextPoint(astar->startPoint_x,astar->startPoint_y);
  Path_timer = new QTimer;
  Path_timer->setInterval(500);
  connect(Path_timer,SIGNAL(timeout()),this,SLOT(Displaypath()));
  Path_timer->start();
  //path_num = path_num-1;
  //qDebug()<<"path_num"<<path_num;
}

void MainWindow::Displaypath()
{
  //path_num -=1;
  if(--path_num>=0)//这里加一个循环，输出到达H点之前和之后的路径，path_num[]
    {
      path_item = new QGraphicsRectItem(4,4,32,32);
      path_item ->setBrush(QColor(255,255,0,150));
      int point_x = 40*(Point_path[path_num][0])-400;//
      int point_y = 40*(Point_path[path_num][1])-400;
      path_item->setPos(QPointF(point_x,point_y));
      scene_1->addItem(path_item);
      if(path_num == 0)
        {
          Path_timer -> stop();
          delete Path_timer;
          Path_timer = NULL;
        }
    }
}


bool MainWindow::CalcNextPoint(int coord_x , int coord_y)
{
  static int i = 0;
  if(coord_x >20 ||coord_y >20)
    return false;
  int xmin = coord_x;
  int ymin = coord_y;
  int vmin = 0;
  qDebug()<<"coord"<<coord_x<<coord_y;
  if((coord_x == astar->helpPoint_x[i] && abs(coord_y-astar->helpPoint_y[i]) ==1)||
     (coord_y == astar->helpPoint_y[i] && abs(coord_x-astar->helpPoint_x[i])==1)){
      if((coord_x == astar->endPoint_x && (abs(coord_y - astar->endPoint_y))==1)||
        (coord_y == astar->endPoint_y && (abs(coord_x - astar->endPoint_x)==1)))//到终点的周围
        {
          astar->SceneOne_infor[astar->endPoint_x][astar->endPoint_y].g =
              astar->SceneOne_infor[coord_x][coord_y].g + 1;
          path_num = astar->SceneOne_infor[astar->endPoint_x][astar->endPoint_y].g-1;
          //path_num为移动总花费，如果要实现分段寻径，是否要设置为数组
          vmin = 0;
          if(FindPath(astar->endPoint_x,astar->endPoint_y,
                      //astar->helpPoint_x[i-1],astar->helpPoint_y[i-1],
                      0,1,
                      astar->SceneOne_infor[astar->endPoint_x][astar->endPoint_y].g-1))
            return true;
        }
      else{
        astar->SceneOne_infor[astar->helpPoint_x[i]][astar->helpPoint_y[i]].g =
            astar->SceneOne_infor[coord_x][coord_y].g + 1;
        vmin = 0;
        astar->startPoint_x =astar->helpPoint_x[i];
        astar->startPoint_y =astar->helpPoint_y[i];
        i++;
        if(astar->helpPoint_x[i] || astar->helpPoint_y[i])
          return CalcNextPoint(astar->startPoint_x,astar->startPoint_y);
        else{
          astar->helpPoint_x[i] = astar->endPoint_x;
          astar->helpPoint_y[i] = astar->endPoint_y;
          return CalcNextPoint(astar->startPoint_x,astar->startPoint_y);
          }
        }
    }
  if(astar->SceneOne_infor[coord_x+1][coord_y].type == APT_UNKNOWN && coord_x<19)//右
      {
        astar->SceneOne_infor[coord_x+1][coord_y].g = astar->SceneOne_infor[coord_x][coord_y].g+1;
        astar->SceneOne_infor[coord_x+1][coord_y].h =
            10*(abs((coord_x+1) - astar->helpPoint_x[i])+abs(coord_y - astar->helpPoint_y[i]));
        astar->SceneOne_infor[coord_x+1][coord_y].f =
            astar->SceneOne_infor[coord_x+1][coord_y].g + astar->SceneOne_infor[coord_x+1][coord_y].h;
        astar->SceneOne_infor[coord_x+1][coord_y].type = APT_OPENED;
        if(vmin == 0|| vmin > astar->SceneOne_infor[coord_x+1][coord_y].h)
          {
            xmin = coord_x+1;
            ymin = coord_y;
            vmin = astar->SceneOne_infor[coord_x+1][coord_y].h;
          }
      }

  if(astar->SceneOne_infor[coord_x][coord_y+1].type == APT_UNKNOWN && coord_y<19)//下
    {
      astar->SceneOne_infor[coord_x][coord_y+1].g = astar->SceneOne_infor[coord_x][coord_y].g+1;
      astar->SceneOne_infor[coord_x][coord_y+1].h =
          //10*(abs(coord_x - astar->endPoint_x)+abs(coord_y - astar->endPoint_y));
          10*(abs(coord_x - astar->helpPoint_x[i])+abs((coord_y+1) - astar->helpPoint_y[i]));
      astar->SceneOne_infor[coord_x][coord_y+1].f =
          astar->SceneOne_infor[coord_x][coord_y+1].g + astar->SceneOne_infor[coord_x][coord_y+1].h;
      astar->SceneOne_infor[coord_x][coord_y+1].type = APT_OPENED;
      if(vmin == 0|| vmin > astar->SceneOne_infor[coord_x][coord_y+1].h)
        {
          xmin = coord_x;
          ymin = coord_y+1;
          vmin = astar->SceneOne_infor[coord_x][coord_y+1].h;
          //qDebug()<<"vmin_under"<<vmin;
        }
    }

  if(astar->SceneOne_infor[coord_x][coord_y-1].type == APT_UNKNOWN && coord_y >0)//上
    {
      //qDebug()<<"helppoint[i]"<<i<<astar->helpPoint_x[i]<<astar->helpPoint_y[i];
      astar->SceneOne_infor[coord_x][coord_y-1].g = astar->SceneOne_infor[coord_x][coord_y].g+1;
      astar->SceneOne_infor[coord_x][coord_y-1].h =
          //10*(abs(coord_x - astar->endPoint_x)+abs(coord_y - astar->endPoint_y));
          10*(abs(coord_x - astar->helpPoint_x[i])+abs((coord_y-1) - astar->helpPoint_y[i]));
      astar->SceneOne_infor[coord_x][coord_y-1].f =
          astar->SceneOne_infor[coord_x][coord_y-1].g + astar->SceneOne_infor[coord_x][coord_y-1].h;
      astar->SceneOne_infor[coord_x][coord_y-1].type = APT_OPENED;
      if(vmin == 0|| vmin > astar->SceneOne_infor[coord_x][coord_y-1].h)
        {
          xmin = coord_x;
          ymin = coord_y-1;
          vmin = astar->SceneOne_infor[coord_x][coord_y-1].h;
        }
    }
  if(astar->SceneOne_infor[coord_x-1][coord_y].type == APT_UNKNOWN && coord_x>0)//左
    {
      astar->SceneOne_infor[coord_x-1][coord_y].g = astar->SceneOne_infor[coord_x][coord_y].g+1;
      astar->SceneOne_infor[coord_x-1][coord_y].h =
          10*(abs((coord_x-1) - astar->helpPoint_x[i])+abs(coord_y - astar->helpPoint_y[i]));
      astar->SceneOne_infor[coord_x-1][coord_y].f =
          astar->SceneOne_infor[coord_x-1][coord_y].g + astar->SceneOne_infor[coord_x-1][coord_y].h;
      astar->SceneOne_infor[coord_x-1][coord_y].type = APT_OPENED;
      if(vmin == 0|| vmin > astar->SceneOne_infor[coord_x-1][coord_y].h)
        {
          xmin = coord_x-1;
          ymin = coord_y;
          vmin = astar->SceneOne_infor[coord_x-1][coord_y].h;
        }
    }
  //qDebug()<<"coord_point"<<coord_x<<coord_y;
  //qDebug()<<"next_point" <<xmin<<ymin;
  //qDebug()<<"i"<<i;
  //qDebug()<<"helpPoint"<<astar->helpPoint_x[i]<<astar->helpPoint_y[i];
  //qDebug()<<"coord_h"<<vmin;
  //qDebug()<<"*****************";
  int vim_campare_x,vim_campare_y;

  if(vmin==0){//vmin == 0  上下左右四个点都非unknow，代表是死路
      int cost = astar->SceneOne_infor[astar->startPoint_x][astar->startPoint_y].h;
      for(int for_x = 0;for_x < 20;for_x++){
          for(int for_y = 0;for_y < 20; for_y++){
              while((astar->SceneOne_infor[for_x][for_y].type == APT_OPENED)&&
                    astar->SceneOne_infor[for_x][for_y].h <cost)
                {
                  vmin = astar->SceneOne_infor[for_x][for_y].h;
                  cost = astar->SceneOne_infor[for_x][for_y].h;
                  vim_campare_x = for_x;
                  vim_campare_y = for_y;
                }
            }
        }
        astar->curpoint_x = vim_campare_x;
        astar->curpoint_y = vim_campare_y;
        astar->SceneOne_infor[vim_campare_x][vim_campare_y].type = APT_CLOSED;
        return CalcNextPoint(astar->curpoint_x,astar->curpoint_y);
    }
  else{
      astar->SceneOne_infor[astar->startPoint_x][astar->startPoint_y].h =
          10*(abs(coord_x - astar->helpPoint_x[i])+abs(coord_y - astar->helpPoint_y[i]));
          astar->curpoint_x = xmin;
          astar->curpoint_y = ymin;
          astar->SceneOne_infor[xmin][ymin].type = APT_CLOSED;
          return CalcNextPoint(astar->curpoint_x,astar->curpoint_y);
    }
}

bool MainWindow::FindPath(int end_x, int end_y, int start_x, int start_y, int temp)
{
  static int path_i=0;
  if(((end_x == start_x) && abs(end_y-start_y)==1)||  //应该推回到初始点！  初始点可使用宏定义
     ((end_y== start_y) && abs(end_x-start_x)==1)){
      qDebug()<<"final_end"<<end_x<<end_y<<"final_start"<<start_x<<start_y<<"path_i"<<path_i;
      return true;
    }
  if((astar->SceneOne_infor[end_x-1][end_y].type == APT_CLOSED||APT_ENDPOINT_TO)&&
     astar->SceneOne_infor[end_x-1][end_y].g == temp)
    {
      Point_path[path_i][0] = end_x-1;
      Point_path[path_i][1] = end_y;
      astar->SceneOne_infor[end_x-1][end_y].type = APT_OPENED;
      path_i++;
      temp--;
      return FindPath(end_x-1,end_y,start_x,start_y,temp);
    }
  if((astar->SceneOne_infor[end_x+1][end_y].type == APT_CLOSED||APT_ENDPOINT_TO)&&
     astar->SceneOne_infor[end_x+1][end_y].g == temp)
    {
      Point_path[path_i][0] = end_x+1;
      Point_path[path_i][1] = end_y;
      astar->SceneOne_infor[end_x+1][end_y].type = APT_OPENED;
      path_i++;
      temp--;
      return FindPath(end_x+1,end_y,start_x,start_y,temp);
    }
  if((astar->SceneOne_infor[end_x][end_y+1].type == APT_CLOSED||APT_ENDPOINT_TO)&&
     astar->SceneOne_infor[end_x][end_y+1].g == temp)
    {
      Point_path[path_i][0] = end_x;
      Point_path[path_i][1] = end_y+1;
      astar->SceneOne_infor[end_x][end_y+1].type = APT_OPENED;
      path_i++;
      temp--;
      return FindPath(end_x,end_y+1,start_x,start_y,temp);
    }
  if((astar->SceneOne_infor[end_x][end_y-1].type == APT_CLOSED||APT_ENDPOINT_TO)&&
     astar->SceneOne_infor[end_x][end_y-1].g == temp)
    {
      Point_path[path_i][0] = end_x;
      Point_path[path_i][1] = end_y-1;
      astar->SceneOne_infor[end_x][end_y-1].type = APT_OPENED;
      path_i++;
      temp--;
      return FindPath(end_x,end_y-1,start_x,start_y,temp);
    }
  //都不符合退回上个点
  astar->SceneOne_infor[end_x][end_y].type = APT_OPENED;
  path_i--;
  temp++;
  end_x = Point_path[path_i][0];
  end_y = Point_path[path_i][1];
  return FindPath(end_x,end_y,start_x,start_y,temp);//这是返回当前点
}
