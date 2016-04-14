#ifndef XFSERIALPORT_H
#define XFSERIALPORT_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
  class xfserialport;
}

class xfserialport : public QDialog
{
  Q_OBJECT

public:
  explicit xfserialport(QWidget *parent = 0);
  ~xfserialport();

private slots:
  void on_BtnOpen_clicked();
  void on_BtnSend_clicked();
  void serialportread();

private:
  Ui::xfserialport *ui;
  QSerialPort *my_serialport;
};

#endif // XFSERIALPORT_H
