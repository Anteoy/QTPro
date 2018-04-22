#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))
    {  //本地主机的6666端口，如果出错就输出错误信息，并关闭
        qDebug() << tcpServer->errorString();
        close();
    }
    //连接信号和相应槽函数
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage()
{
    //用于暂存我们要发送的数据
    QByteArray block;

    //使用数据流写入数据
    QDataStream out(&block,QIODevice::WriteOnly);

    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_6);

    //在服务器端，在发送数据时就要首先发送实际文件的大小信息，但是，文件的大小一开始是无法预知的，所以这里先使用了out<<(quint16) 0;
    //在block的开始添加了一个quint16大小的空间，也就是两字节的空间，它用于后面放置文件的大小信息。
    out<<(quint16) 0;
    //输入实际的文件，这里是字符串
    out<<tr("hello Tcp!!!");
    //返回到block的开始
    out.device()->seek(0);
    //加入实际的文件大小信息
    out<<(quint16) (block.size() - sizeof(quint16));

    //我们获取已经建立的连接的子套接字
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    //当发送完成时就会断开连接
    //最后调用deleteLater()函数保证在关闭连接后删除该套接字clientConnection
    //关联了disconnected()信号和deleteLater()槽
    connect(clientConnection,SIGNAL(disconnected()),clientConnection,
           SLOT(deleteLater()));
    //发送数据
    clientConnection->write(block);

    clientConnection->disconnectFromHost();

    //发送数据成功后，显示提示
    ui->statusLabel->setText("send message successful!!!");
}
