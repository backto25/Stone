/*  *****************************************************
*****************************************************  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>

#include "newgroup.h"
/*  *****************************************************
*****************************************************  */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//视图更新
    bool initUI();//更新整个UI
    bool updateGroupManegeView();//更新分组管理视图
    bool updatePcBoxView();//更新台位视图

    bool pushPcToList(QList<QToolButton*> *pList);//保存ui上的电脑实体，方便管理

private slots:

    void on_pushButtonAddGroup_clicked();
    bool addGroup_secondStep_choosePc(Group tempGroup);

private:
    Ui::MainWindow *ui;//Qt设计师
    NewGroup *newGroupDialog;//新建分组窗口
    QList<QToolButton*> *pcList;//保存ui上的电脑实体，方便管理
};

#endif // MAINWINDOW_H
