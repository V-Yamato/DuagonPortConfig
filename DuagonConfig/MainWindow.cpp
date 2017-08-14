#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    port = new QSerialPort();
    ui->setupUi(this);
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        ui->portcomboBox->addItem(portInfo.portName());
    }
}

MainWindow::~MainWindow()
{
    port->close();
    delete ui;
}

//void MainWindow::setUpPort(){
//    port->setBaudRate();

//}
