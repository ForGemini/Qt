#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_begin_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_exit_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_prompt_clicked();

protected:
    void timerEvent(QTimerEvent *e) override; //定时器
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWidget *ui;

    int gameTime;       //游戏时间
    int gameTimerId;    //游戏时间定时器ID
    int failureTimerId;    //失败动画定时器ID
    int winTimerId;     //成功动画定时器ID
    QString inputnumStr;  //输入的数字
    QString rightnumStr;  //正确答案
    QMovie failureMovie;   //失败动画
    QMovie winMovie;    //胜利动画

    void dealNum();//数字处理槽函数
};
#endif // MAINWIDGET_H
