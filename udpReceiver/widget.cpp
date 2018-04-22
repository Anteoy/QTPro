#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    //将receiver绑定到45454端口 绑定模式QUdpSocket::ShareAddress，它表明其他服务也可以绑定到这个端口上。
    receiver->bind(45454,QUdpSocket::ShareAddress);
    //当receiver发现有数据报到达时就会发出readyRead()信号，所以将其和数据报处理函数相关联。
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(processPendingDatagram()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::processPendingDatagram() //处理等待的数据报
{
    while(receiver->hasPendingDatagrams())  //拥有等待的数据报
    {
       QByteArray datagram; //拥于存放接收的数据报
//让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
       datagram.resize(receiver->pendingDatagramSize());
       //接收数据报，将其存放到datagram中
       receiver->readDatagram(datagram.data(),datagram.size());
       //将数据报内容显示出来
       ui->label->setText(datagram);
    }
}
