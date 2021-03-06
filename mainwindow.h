#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: signals:
    void timeout();
    void readyRead();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_connect2_clicked();

    void readSerial_2();

    void on_pushButton_connect1_toggled(bool checked);

    void on_pushButton_connect2_toggled(bool checked);

    void on_pushButton_port1_clear_clicked();

    void on_pushButton_port2_clear_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
