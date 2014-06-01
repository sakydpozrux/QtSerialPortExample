#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), serial()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    closeSerialPort();
    delete ui;
}

void MainWindow::openSerialPort()
{
    QString name = "/dev/ttyACM0";
    QString stringBaudRate = "9600";
    QString stringDataBits = "8bits";

    serial.setPortName(name);

    if (serial.open(QIODevice::ReadWrite))
    {
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        ui->statusBar->showMessage(
                    QString("Connected to %1 : %2, %3, %4, %5, %6. Why not try sending dupa???")
                    .arg(name)
                    .arg(stringBaudRate)
                    .arg(stringDataBits));
    }
    else
    {
        QMessageBox::critical(this, "Error", serial.errorString());
        ui->statusBar->showMessage("OMG open error!!!! WTF IS HAPPENING!!!");
    }
}

void MainWindow::closeSerialPort()
{
    serial.close();
    ui->statusBar->showMessage("You closed connection... WHYYYYYY");
}

void MainWindow::readData()
{
    QByteArray data = serial.readAll();
    ui->plainTextEdit_2->appendPlainText(QString(data));
}

void MainWindow::on_pushButton_clicked()
{
    QString line_to_send = ui->lineEdit->text();
    if (line_to_send == "dupa") line_to_send = "sam jestes glupi";

    QByteArray data = QByteArray((line_to_send + '\n').toStdString().c_str());
    serial.write(data);
    readData();


    ui->plainTextEdit->appendPlainText(line_to_send);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked)
    {
        openSerialPort();
        ui->pushButton->setEnabled(true);
    }
    else
    {
        closeSerialPort();
        ui->pushButton->setEnabled(false);
    }
}
