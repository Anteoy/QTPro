#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    id1 = startTimer(1000);  // 开启一个1秒定时器，返回其ID
    id2 = startTimer(2000);
    id3 = startTimer(10000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
   if (event->timerId() == id1) {       // 判断是哪个定时器
       ui->label->setText(tr("%1").arg(qrand()%10));
   }
   else if (event->timerId() == id2) {
       ui->label_2->setText(tr("hello world!"));
   }
   else {
       qApp->quit();
   }
}
