#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->portInfoBtn->setEnabled(false);
    ui->openPortBtn->setEnabled(false);
    ui->closePortBtn->setEnabled(false);
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        ui->portcomboBox->addItem(portInfo.portName());
    }

    connect(ui->portcomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOpenBtnEnable()));
    connect(ui->portInfoBtn,SIGNAL(clicked(bool)),this,SLOT(printPortInfo()));
    connect(ui->clearViewBtn,SIGNAL(clicked(bool)),this,SLOT(clearTextView()));
    connect(ui->openPortBtn,SIGNAL(clicked(bool)),this,SLOT(openPort()));

}

MainWindow::~MainWindow()
{
    port->close();
    delete port;
    delete ui;
}

//void MainWindow::setUpPort(){
//    port->setBaudRate();

//}

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
    port = new QSerialPort(QSerialPortInfo::availablePorts().at(ui->portcomboBox->currentIndex()-1),this);

    if (port->open(QIODevice::ReadWrite)) {
        ui->portcomboBox->setEnabled(false);
        ui->openPortBtn->setText("已连接");
        ui->openPortBtn->setEnabled(false);
        ui->closePortBtn->setEnabled(true);
        ui->portManageTextView->append(tr("连接%1成功!^_^").arg(port->portName()));
    }else {
        ui->portManageTextView->append(tr("连接%1失败!T_T").arg(port->portName()));

    }
}

void MainWindow::closePort(){
    port->close();
    ui->openPortBtn->setEnabled(true);
    ui->openPortBtn->setText("打开串口");
    ui->closePortBtn->setEnabled(false);
    ui->portcomboBox->setEnabled(true);
    ui->portManageTextView->append(tr("断开%1成功!^_^").arg(port->portName()));
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

