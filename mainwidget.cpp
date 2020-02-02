#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QString>
#include <QKeyEvent>

/*
--------------猜数游戏-----------------------
By lhl
打包命令  windeployqt
*/


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->beginpage);//设定启动界面
    //失败动画
    failureMovie.setFileName(":/im/over.gif");
    ui->labelfailure->setMovie(&failureMovie);//给标签设置动画
    ui->labelfailure->setScaledContents(true);//让动画自动适应标签大小

    //胜利动画
    winMovie.setFileName(":/im/win.gif");
    ui->labelwin->setMovie(&winMovie);
    ui->labelwin->setScaledContents(true);

    connect(ui->pushButton_0,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_1,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&MainWidget::dealNum);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&MainWidget::dealNum);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_pushButton_begin_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamepage);//转到游戏界面
    gameTime = ui->comboBox->currentText().toInt();//得到下拉框的游戏时间
    //设置进度条
    ui->progressBar_time->setMinimum(0);//最小值
    ui->progressBar_time->setMaximum(gameTime);//最大值
    ui->progressBar_time->setValue(gameTime); //当前值
    inputnumStr.clear();//清空输入
    ui->textEdit->setText(inputnumStr);

    int num;
    qsrand( QTime(0,0,0).secsTo( QTime::currentTime() ) );//以从0时0分0秒到现在的秒数为种子
    //调用全局的qrand()函数生成随机数，对10000取余，保证位于10000的范围内
    num = qrand()%10000 ;
    rightnumStr = QString::number(num);
    //qDebug() << "rightNum = " << rightnumStr;

    gameTimerId = 0;
    //启动定时器
    gameTimerId = startTimer(1000); //以 1000 毫秒（即1s）作为时间间隔
}

//数字处理
void MainWidget::dealNum()
{
    //获取信号接收者
    QObject * mySender = sender();
    //转换为按钮类型
    QPushButton *p = (QPushButton *)mySender;
    if(p !=NULL)
    {
        //获取按钮的内容
        QString numStr = p->text();
        if(inputnumStr.size()<rightnumStr.size())
        {
            inputnumStr +=numStr;
            if(inputnumStr != '0')//数字不能以0开始
            {
                ui->textEdit->setText(inputnumStr);
            }
            else
            {
                inputnumStr.chop(1); //删除最后一位字符;
            }
        }
        if(inputnumStr.size() == rightnumStr.size())
        {
            if(inputnumStr == rightnumStr)
            {
                killTimer(gameTimerId);//关闭定时器
                winMovie.start();//启动动画
                ui->stackedWidget->setCurrentWidget(ui->winpage);//切换成功动画页面
                winTimerId = startTimer(5000); //启动定时器
                QMessageBox::information(this, "成功", "你猜对了！！！");
            }
            else if(inputnumStr.toInt() < rightnumStr.toInt())
            {
                 ui->textEdit->append("猜小了!!!");
            }
            else if(inputnumStr.toInt() > rightnumStr.toInt())
            {
                 ui->textEdit->append("猜大了!!!");
            }
        }
       // qDebug()<<inputnumStr.size();
    }

}

//定时器中断函数
void MainWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == gameTimerId)
    {
        gameTime--;
        ui->progressBar_time->setValue(gameTime); //进度条设置当前值

        if(gameTime == 0)//时间到
        {
            killTimer(gameTimerId);//关闭定时器
            failureMovie.start();//启动动画
            //切换失败动画页面
            ui->stackedWidget->setCurrentWidget(ui->failurepage);
            failureTimerId = startTimer(5000); //启动定时器
            QMessageBox::information(this, "失败", "时间到了啊！！！");
        }

    }
    else if(e->timerId() == failureTimerId)
    {
        killTimer(failureTimerId);//关闭定时器
        ui->stackedWidget->setCurrentWidget(ui->beginpage);//设定启动界面
    }
    else if(e->timerId() == winTimerId)
    {
        killTimer(winTimerId);//关闭定时器
        ui->stackedWidget->setCurrentWidget(ui->beginpage);//设定启动界面
    }

}

void MainWidget::on_pushButton_back_clicked()
{
    killTimer(gameTimerId);//关闭定时器
    ui->stackedWidget->setCurrentWidget(ui->beginpage);//设定启动界面
}

void MainWidget::on_pushButton_exit_clicked()
{
    this->close(); //关闭窗口
}

void MainWidget::on_pushButton_del_clicked()
{
    inputnumStr.chop(1); //删除最后一位字符;
    ui->textEdit->setText(inputnumStr);
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    QString numStr;
    switch (event->key())
    {
        case Qt::Key_0:
            numStr = '0';
            break;
        case Qt::Key_1:
            numStr = '1';
            break;
        case Qt::Key_2:
            numStr = '2';
            break;
        case Qt::Key_3:
            numStr = '3';
            break;
        case Qt::Key_4:
            numStr = '4';
            break;
        case Qt::Key_5:
            numStr = '5';
            break;
        case Qt::Key_6:
            numStr = '6';
            break;
        case Qt::Key_7:
            numStr = '7';
            break;
        case Qt::Key_8:
            numStr = '8';
            break;
        case Qt::Key_9:
            numStr = '9';
            break;
        case Qt::Key_Backspace:
            inputnumStr.chop(1); //删除最后一位字符;
            ui->textEdit->setText(inputnumStr);
            break;
        case Qt::Key_Enter:  //数字小键盘旁边的回车
        case Qt::Key_Return:  //字母键旁边的回车
            MainWidget::on_pushButton_prompt_clicked();
            break;
    }

    if(inputnumStr.size()<rightnumStr.size())
    {
        //数字不能以0开始
        if(inputnumStr == "0")
        {
            inputnumStr.clear();
        }
        else if(numStr != "")//inputnumStr.size() != 0 && numStr != 0) //原为else，有Bug，按键无法正常提示，因为inputnumStr被清空了然侯在这里显示了
        {
            inputnumStr +=numStr;
            ui->textEdit->setText(inputnumStr);
        }

    }
    if((inputnumStr.size() == rightnumStr.size())&&(inputnumStr.size() != 0))
    {
        if(inputnumStr == rightnumStr)
        {
            killTimer(gameTimerId);//关闭定时器
            winMovie.start();//启动动画
            ui->stackedWidget->setCurrentWidget(ui->winpage);//切换成功动画页面
            winTimerId = startTimer(5000); //启动定时器
            QMessageBox::information(this, "成功", "你猜对了！！！");
        }
        else if(inputnumStr.toInt() < rightnumStr.toInt())
        {
             ui->textEdit->append("猜小了!!!");
        }
        else if(inputnumStr.toInt() > rightnumStr.toInt())
        {
             ui->textEdit->append("猜大了!!!");
        }
    }
}



void MainWidget::on_pushButton_prompt_clicked()
{
   // inputnumStr.clear();
    ui->textEdit->setText( "随机数为：" + rightnumStr );
}
