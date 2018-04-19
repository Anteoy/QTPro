#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile(); //xin jian cao zuo
    bool maybeSave(); //pan duan shi fou xu yao bao cun
    bool save();
    bool saveAs(); // ling cun wei
    bool saveFile(const QString &fileName); //bao cun wei jian
    bool loadFile(const QString &fileName); // 加载文件

private slots:
    void on_action_N_triggered();

    void on_action1_triggered();

    void on_action2_2_triggered();

private:
    Ui::MainWindow *ui;
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool isUntitled;
    // 保存当前文件的路径
    QString curFile;
};

#endif // MAINWINDOW_H
