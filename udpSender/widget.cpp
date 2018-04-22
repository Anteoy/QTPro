#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QByteArray datagram = "hello world!";
    //数据报的内容，数据报的大小，主机地址和端口号。
    sender->writeDatagram(datagram.data(),datagram.size(),
                              QHostAddress::Broadcast,45454);
}
