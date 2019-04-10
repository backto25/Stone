/*  *****************************************************
*****************************************************  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>

#include "newgroup.h"
#include "newgroupsecondstep.h"
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
    bool updateView();//更新整个UI
    bool updateGroupBoxView();//更新分组管理视图
    bool updatePcBoxView();//更新台位视图
    bool updateStaffBoxView();//更新人员表视图

    bool pushPcToList(QList<QToolButton*> *pList);//保存ui上的电脑实体，方便管理

private slots:

    void on_pushButtonAddGroup_clicked();
    bool addGroup_secondStep_choosePc();
    bool backTo_firstStep_chooseStaff();
    bool shutDown_firstStep();

    void on_listWidgetStaff_customContextMenuRequested(const QPoint &pos);

    void on_listWidgetGroups_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;//Qt设计师
    NewGroup *newGroupFirstStep;//新建分组窗口第一步
    NewGroupSecondStep *newGroupSecondStep;//新建分组窗口第二步
    QList<QToolButton*> *pcList;//保存ui上的电脑实体，方便管理

};

#endif // MAINWINDOW_H
