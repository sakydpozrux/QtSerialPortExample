#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSerialPort>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QSerialPort serial;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openSerialPort();
    void closeSerialPort();

    void readData();

private slots:
    void on_pushButton_clicked();


    void on_checkBox_toggled(bool checked);
};

#endif // MAINWINDOW_HPP
