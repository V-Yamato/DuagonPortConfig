#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

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
    void commandFileOpen();

    void showWarnningMesge(QString mesg);


    void portMesgShowOnView();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QSerialPortInfo portInfo;
    QTimer *timer;
    QByteArray allData;
    QByteArray receiveData;

};

#endif // MAINWINDOW_H
