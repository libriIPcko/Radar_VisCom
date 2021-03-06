#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPortVersion>
#include <QtSerialPort/QtSerialPortDepends>

//4Test Case var
int temp_count = 0;
QSerialPort port1;
QSerialPort port2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //QMetaObject::connectSlotsByName(MainWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //ui->listView->
    //ui->listView->setAttribute()
    //QtSerialPortInfo::
    //a = QSerialPortInfo("COM7");
    ui->textBrowser->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                    + QObject::tr("Location: ") + info.systemLocation() + "\n"
                    + QObject::tr("Description: ") + info.description() + "\n"
                    + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                    + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n";
                   // + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

        //auto label = new QLabel(s);
        //layout->addWidget(label);
        //ui->textBrowser->setPlainText(s);
        ui->textBrowser->append(s);
    }
}

void MainWindow::on_pushButton_connect2_clicked()
{
    //4GetTxt

    port2.setBaudRate(9600);
    port2.setPortName(ui->textBrowser_Port2->toPlainText());

    if (port2.open(QIODevice::ReadWrite) == 1){
        //opened
        ui->pushButton_connect1->setAutoFillBackground(true);
        QPalette palette = ui->textBrowser_Port2->palette();
        palette.setColor(QPalette::ButtonText,QColor(Qt::green));
        ui->pushButton_connect1->setPalette(palette);
        ui->pushButton_connect1->update();

        //QObject::connect(port2,SIGNAL(readyRead()),this,SLOT(readSerial_2()));
        //port2.connect(SIGNAL(port2.readyRead()),SLOT(readSerial_2()));
        //QObject::connect(port2,SIGNAL(port.readyRead()),this,SLOT(readSerial_2()));
        //connect(port2,SIGNAL(readyRead()),this,SLOT(readSerial_2()));
        /*
         QTimer mTimer;
        mTimer.setInterval(10);
        mTimer.setSingleShot(false);
        connect(mTimer,SIGNAL(timeout()),this,SLOT(readSerial2()));
        mTimer.start();
        */

    }
    else{
        //error, or closed
        ui->pushButton_connect2->setAutoFillBackground(true);
        QPalette palette = ui->textBrowser_Port2->palette();
        palette.setColor(QPalette::ButtonText,QColor(Qt::red));
        ui->pushButton_connect2->setPalette(palette);
        ui->pushButton_connect2->update();
    }
}

void MainWindow::readSerial_2(){
        ui->textBrowser_Port1->setPlainText("Received: ");
        ui->textBrowser_Port1->setPlainText(port2.readAll());
        ui->textBrowser_Port1->setPlainText("\n");
}

void MainWindow::on_pushButton_connect1_toggled(bool checked)
{
    temp_count++;
    ui->textBrowser_Port1->clear();
    //4GetTxt
    //QSerialPort port1;
    port1.setBaudRate(9600);
    //checked = !checked;
    if (checked == 1){
        port1.setPortName(ui->textEdit_Port1->toPlainText());
        port1.setDataBits(QSerialPort::Data8);
        //port1.openMode();
        port1.open(QIODevice::ReadWrite);
        QString data = QString::number(temp_count)+" Check status: "+QString::number(checked)+"\n";
        ui->textBrowser_Port1->insertPlainText(data);

        if (port1.isOpen() == 1){
            //opened
            ui->pushButton_connect1->setAutoFillBackground(true);
            QPalette palette = ui->textBrowser_Port1->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::green));
            ui->pushButton_connect1->setPalette(palette);
            ui->pushButton_connect1->update();
            ui->pushButton_connect1->setText("Connected");
        }
        else{
            //error, or closed
            ui->pushButton_connect1->setAutoFillBackground(true);
            QPalette palette = ui->textBrowser_Port1->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::red));
            ui->pushButton_connect1->setPalette(palette);
            ui->pushButton_connect1->update();
            //4TestCase
            ui->textBrowser_Port1->insertPlainText(QString::number(temp_count));
            ui->textBrowser_Port1->insertPlainText(": ");
            ui->textBrowser_Port1->insertPlainText("\t ");
            ui->textBrowser_Port1->insertPlainText("Port Name: ");
            ui->textBrowser_Port1->insertPlainText(ui->textEdit_Port1->toPlainText());
            ui->textBrowser_Port1->insertPlainText("\n");
            //ui->textBrowser_Port1->insertPlainText(port1.);
            ui->textBrowser_Port1->insertPlainText("\tDeviceNotFoundError: ");
            //ui->textBrowser_Port1->insertPlainText(QString::number(QSerialPort::DeviceNotFoundError));
            ui->textBrowser_Port1->insertPlainText(QString::number(port1.DeviceNotFoundError));
            ui->textBrowser_Port1->insertPlainText("\n");
            ui->textBrowser_Port1->insertPlainText("\tOpenError: ");
            ui->textBrowser_Port1->insertPlainText(QString::number(port1.OpenError));
            ui->textBrowser_Port1->insertPlainText("\n");
            ui->textBrowser_Port1->insertPlainText("\tPermissionError: ");
            ui->textBrowser_Port1->insertPlainText(QString::number(port1.PermissionError));
            ui->textBrowser_Port1->insertPlainText("\n");
        }
    }
    else{
        QString data = QString::number(temp_count)+" Check status: "+QString::number(checked)+"\n";
        ui->textBrowser_Port1->insertPlainText(data);
        port1.close();
        if(port1.isOpen()){
            ui->pushButton_connect1->setText("Conected");
        }
        else {
            QPalette palette = ui->textBrowser_Port1->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::black));
            ui->pushButton_connect1->setPalette(palette);
            ui->pushButton_connect1->update();
            ui->pushButton_connect1->setText("Disconnected");
        }
    }
}


void MainWindow::on_pushButton_connect2_toggled(bool checked)
{
    temp_count++;
    ui->textBrowser_Port2->clear();
    //4GetTxt
    QSerialPort Port2;
    Port2.setBaudRate(9600);
    //checked = !checked;
    if (checked == 1){
        Port2.setPortName(ui->textEdit_Port2->toPlainText());
        Port2.setDataBits(QSerialPort::Data8);
        //Port2.openMode();
        Port2.open(QIODevice::ReadWrite);
        QString data = QString::number(temp_count)+" Check status: "+QString::number(checked)+"\n";
        ui->textBrowser_Port2->insertPlainText(data);

        if (Port2.isOpen() == 1){
            //opened
            ui->pushButton_connect2->setAutoFillBackground(true);
            QPalette palette = ui->textBrowser_Port2->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::green));
            ui->pushButton_connect2->setPalette(palette);
            ui->pushButton_connect2->update();
            ui->pushButton_connect2->setText("Connected");

        }
        else{
            //error, or closed
            ui->pushButton_connect2->setAutoFillBackground(true);
            QPalette palette = ui->textBrowser_Port2->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::red));
            ui->pushButton_connect2->setPalette(palette);
            ui->pushButton_connect2->update();
            //4TestCase
            ui->textBrowser_Port2->insertPlainText(QString::number(temp_count));
            ui->textBrowser_Port2->insertPlainText(": ");
            ui->textBrowser_Port2->insertPlainText("\t ");
            ui->textBrowser_Port2->insertPlainText("Port Name: ");
            ui->textBrowser_Port2->insertPlainText(ui->textEdit_Port2->toPlainText());
            ui->textBrowser_Port2->insertPlainText("\n");
            //ui->textBrowser_Port2->insertPlainText(Port2.);
            ui->textBrowser_Port2->insertPlainText("\tDeviceNotFoundError: ");
            //ui->textBrowser_Port2->insertPlainText(QString::number(QSerialPort::DeviceNotFoundError));
            ui->textBrowser_Port2->insertPlainText(QString::number(Port2.DeviceNotFoundError));
            ui->textBrowser_Port2->insertPlainText("\n");
            ui->textBrowser_Port2->insertPlainText("\tOpenError: ");
            ui->textBrowser_Port2->insertPlainText(QString::number(Port2.OpenError));
            ui->textBrowser_Port2->insertPlainText("\n");
            ui->textBrowser_Port2->insertPlainText("\tPermissionError: ");
            ui->textBrowser_Port2->insertPlainText(QString::number(Port2.PermissionError));
            ui->textBrowser_Port2->insertPlainText("\n");
        }
    }
    else{
        QString data = QString::number(temp_count)+" Check status: "+QString::number(checked)+"\n";
        ui->textBrowser_Port2->insertPlainText(data);
        Port2.close();
        if(Port2.isOpen()){
            ui->pushButton_connect2->setText("Connected");
        }
        else {
            QPalette palette = ui->textBrowser_Port2->palette();
            palette.setColor(QPalette::ButtonText,QColor(Qt::black));
            ui->pushButton_connect2->setPalette(palette);
            ui->pushButton_connect2->update();
            ui->pushButton_connect2->setText("Disconnected");
        }
    }
}


void MainWindow::on_pushButton_port1_clear_clicked()
{
    ui->textBrowser_Port1->clear();
}


void MainWindow::on_pushButton_port2_clear_clicked()
{
    ui->textBrowser_Port2->clear();
}


void MainWindow::on_pushButton_4_clicked()
{
    //QString data = ui->textBrowser_Port1->toPlainText();
    //QByteArray ListOfString = ui->textBrowser_Port1->toPlainText();
    QString txt = ui->textBrowser_Port1->toPlainText();
    QByteArray data = txt.toUtf8();
    port1.write(data);

}


void MainWindow::on_pushButton_5_clicked()
{
    QString txt = ui->textBrowser_Port2->toPlainText();
    QByteArray data = txt.toUtf8();
    port2.write(data);
}






void MainWindow::on_pushButton_2_clicked()
{
    Graphics gr;
    gr.setModal(true);
    gr.exec();
}

