/*  *****************************************************
*****************************************************  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QUdpSocket>

#include "logindialog.h"
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
    bool pushPcToList(QList<QToolButton*> *pList);//保存ui上的电脑实体，方便管理

    //视图更新
    bool updateView();//更新整个UI
    bool updateGroupBoxView();//更新分组管理视图
    bool updatePcBoxView();//更新台位视图
    bool updateStaffBoxView();//更新人员表视图
    bool updatePcHalfInfo();
    bool updatePcAnotherHalfInfo();
    bool updateDetailGroupInfo();
    void screen_full();
    void screen_normal();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    bool addGroup_secondStep_choosePc();
    bool backTo_firstStep_chooseStaff();
    bool shutDown_firstStep();
    void deleteCurrentGroupSlot();
    void editCurrentGroupSlot();
    void clearCurrentGroupSlot();
    void dealMsg();
    void showDetailPcInfo();
    void showDetailGroupInfoSlot();
    void unavailable();

    void on_pushButtonAddGroup_clicked();
    void on_listWidgetGroups_clicked(const QModelIndex &index);
    void on_listWidgetStaff_customContextMenuRequested(const QPoint &pos);
    void on_listWidgetGroups_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_clicked();
    void on_toolButton_clicked();

    void on_toolButtonPC_1_customContextMenuRequested(const QPoint &pos);

    void on_toolButtonPC_2_customContextMenuRequested(const QPoint &pos);

    void on_toolButtonPC_3_customContextMenuRequested(const QPoint &pos);

    void on_toolButtonPC_4_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;//Qt设计师
    LoginDialog *loginDialog;//登陆窗口
    NewGroup *newGroupFirstStep;//新建分组窗口第一步
    NewGroupSecondStep *newGroupSecondStep;//新建分组窗口第二步
    QList<QToolButton*> *pcList;//保存ui上的电脑实体，方便管理
    QUdpSocket *udpSocket;

};

#endif // MAINWINDOW_H
