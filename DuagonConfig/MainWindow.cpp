#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    timer = new QTimer(this);
    ui->setupUi(this);
    ui->portInfoBtn->setEnabled(false);
    ui->openPortBtn->setEnabled(false);
    ui->closePortBtn->setEnabled(false);
    ui->commandFromFileBtn->setEnabled(false);
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        ui->portcomboBox->addItem(portInfo.portName());
    }

    connect(ui->portcomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOpenBtnEnable()));
    connect(ui->portInfoBtn,SIGNAL(clicked(bool)),this,SLOT(printPortInfo()));
    connect(ui->clearViewBtn,SIGNAL(clicked(bool)),this,SLOT(clearTextView()));
    connect(ui->openPortBtn,SIGNAL(clicked(bool)),this,SLOT(openPort()));
    connect(ui->closePortBtn,SIGNAL(clicked(bool)),this,SLOT(closePort()));
    connect(ui->commandFromFileBtn,SIGNAL(clicked(bool)),this,SLOT(commandFileOpen()));
    connect(timer,SIGNAL(timeout()),this,SLOT(portMesgShowOnView()));

}

MainWindow::~MainWindow()
{
    port->close();
    delete port;
    delete ui;
}


//SLOT
void MainWindow::setOpenBtnEnable(){
    if (ui->portcomboBox->currentIndex() == 0) {
        ui->openPortBtn->setEnabled(false);
        ui->portInfoBtn->setEnabled(false);
    }else{
        ui->openPortBtn->setEnabled(true);
        ui->portInfoBtn->setEnabled(true);
    }
}

void MainWindow::openPort(){

    QByteArray commandArray;
    char p[8]="ps -a\n";
//    char pp[24]="pc -t SINK -s 32 0x01\n";
    port = new QSerialPort(QSerialPortInfo::availablePorts().at(ui->portcomboBox->currentIndex()-1),this);

    if (port->open(QIODevice::ReadWrite)) {
        port->setBaudRate (QSerialPort::Baud115200 );
        port->setDataBits (QSerialPort::Data8 );
        port->setStopBits (QSerialPort::OneStop );
        port->setParity (QSerialPort::NoParity );
        port->setFlowControl(QSerialPort::NoFlowControl);
        connect(port,SIGNAL(readyRead()),this,SLOT(portMesgShowOnView()));

        ui->portcomboBox->setEnabled(false);
        ui->openPortBtn->setText("已连接");
        ui->openPortBtn->setEnabled(false);
        ui->closePortBtn->setEnabled(true);
        ui->commandFromFileBtn->setEnabled(true);
        ui->portManageTextView->append(tr("连接%1成功!^_^").arg(port->portName()));
//            port->QSerialPort::write(pp);
            port->QSerialPort::write(p,8);

//            port->readAll();
//            qDebug()<<QString(port->readAll());
//            qDebug()<<port->bytesAvailable();
                timer->start(10000);
//                ui->portManageTextView->append(QString(port->readAll()));
    }else {
        showWarnningMesge(tr("连接%1失败!T_T").arg(port->portName()));
//        ui->portManageTextView->append(tr("连接%1失败!T_T").arg(port->portName()));
    }
}

void MainWindow::closePort(){
    port->close();
    ui->commandFromFileBtn->setEnabled(false);
    ui->openPortBtn->setEnabled(true);
    ui->openPortBtn->setText("打开串口");
    ui->closePortBtn->setEnabled(false);
    ui->portcomboBox->setEnabled(true);
    ui->portManageTextView->append(tr("断开%1成功!^_^").arg(port->portName()));
    timer->stop();
    delete port;
}

void MainWindow::commandFileOpen(){
    QString commandFileName = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Txt files(*.txt)"));

    if (!commandFileName.isEmpty()) {
        QFile commandFile(commandFileName);
        if (commandFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while(!commandFile.atEnd()){            
                QByteArray line = commandFile.readLine();
                if (QString(line).startsWith("#")) {

                }else{
                    port->write(QString(line));
                }
                qDebug() << QString(line);
            }
        }else{
            showWarnningMesge("文件打开失败 T_T");

        }
    }else{
        showWarnningMesge("文件为空或未选择文件 T_T");
    }

//    port->write("pc -t SINK -s 32 0x01\n");
//    ui->portManageTextView->append(QString(port->readAll()));
//    port->writeData("")


}

void MainWindow::portMesgShowOnView(){
//    QByteArray temp;QString strhex;
//    if(port->bytesAvailable()>=7)
//    {
//        temp=port->readAll(); //全部读取
//        QDataStream out(&temp,QIODevice::ReadWrite);
//        while(!out.atEnd())
//        {
//            qint8 outchar=0;
//            out>>outchar;
//            QString str=QString("%1").arg(outchar&0xFF,2,16,QLatin1Char('0'));
//                    strhex+=str;
//        }
//        qDebug()<<strhex;
//    }
//    QByteArray temp;
//    if(port->bytesAvailable()>=7)
//    {
//        temp=port->readAll(); //全部读取

//        qDebug()<<QString(temp);
//    }
    allData = receiveData.append(port->readAll());

    ui->portManageTextView->append(QString(allData));
}


void MainWindow::clearTextView(){
    ui->portManageTextView->clear();
}

void MainWindow::printPortInfo(){
    portInfo = (QSerialPortInfo::availablePorts().at(ui->portcomboBox->currentIndex()-1));

    ui->portManageTextView->append("port name:" + portInfo.portName());
    ui->portManageTextView->append("description:" + portInfo.description());
    ui->portManageTextView->append("manufacturer:" + portInfo.manufacturer());
    ui->portManageTextView->append("productIdentifier:" + QString::number(portInfo.productIdentifier()));
    ui->portManageTextView->append("serialNumber:" + portInfo.serialNumber());
    ui->portManageTextView->append("systemLocation:" + portInfo.systemLocation());
    ui->portManageTextView->append("vendorIdentifier:" + QString::number(portInfo.vendorIdentifier()));
}

void MainWindow::showWarnningMesge(QString mesg){
    QMessageBox mesgBox;
    mesgBox.setText(mesg);
    mesgBox.setWindowTitle("出错啦");
//    mesgBox.setWindowIcon(QIcon("Error.ico"));
    mesgBox.setIcon(QMessageBox::Warning);
    mesgBox.exec();
}


