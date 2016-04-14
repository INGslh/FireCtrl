#include "xfserialport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  xfserialport w;
  w.show();

  return a.exec();
}
