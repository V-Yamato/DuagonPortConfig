#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setOpenBtnEnable();
    void printPortInfo();
    void clearTextView();
    void openPort();
    void closePort();
//    void setCloseBtnEnable();
//    void setOpenBtnDisable();
//    void setCloseBtnDisable();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QSerialPortInfo portInfo;

//    void setUpPort;

};

#endif // MAINWINDOW_H
