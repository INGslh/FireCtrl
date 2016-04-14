#include "xfserialport.h"
#include "ui_xfserialport.h"

xfserialport::xfserialport(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::xfserialport)
{
  ui->setupUi(this);
  my_serialport= new QSerialPort("COM5");

  connect(my_serialport,SIGNAL(readyRead()),this,SLOT(serialportread()));
}

xfserialport::~xfserialport()
{
  delete ui;
  delete my_serialport;
}

void xfserialport::on_BtnOpen_clicked()
{
  static bool openOnce=true;
  if(openOnce)
    {
      openOnce=false;
      my_serialport->open(QIODevice::ReadWrite);
      my_serialport->setBaudRate(QSerialPort::Baud4800);
      my_serialport->setDataBits(QSerialPort::Data8);
      my_serialport->setParity(QSerialPort::NoParity);
      my_serialport->setStopBits(QSerialPort::OneStop);
      my_serialport->setFlowControl(QSerialPort::NoFlowControl);
      ui->EditRev->append("open successfully");
      ui->BtnOpen->setText("Close");
    }
  else
    {
      openOnce=true;
      ui->EditRev->append("close successfully");
      ui->BtnOpen->setText("Open");
      my_serialport->close();
    }

}

void xfserialport::on_BtnSend_clicked()
{
  my_serialport->write(ui->EditSend->text().toLatin1());
}

void xfserialport::serialportread()
{

  /*static QByteArray allData;
  QByteArray dataTemp;
   while (!my_serialport->atEnd())
     {
       dataTemp +=my_serialport->readAll();
       if(dataTemp.data()[dataTemp.length() - 1]=='~')
         {
           allData += dataTemp;
           allData.resize(allData.size()-1);
           ui->EditRev->append(allData);
           allData.clear();
         }
       else
         {
           allData +=dataTemp;
         }
     }*/

  QByteArray requestData;
  requestData = my_serialport->readAll();

  ui->EditRev->append(tr(requestData));

  requestData.clear();
}
