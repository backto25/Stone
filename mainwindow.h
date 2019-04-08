#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newgroup.h"
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

    bool initUI();//初始化页面
    bool updateGroupList();//更新listWidgetGroups
    bool updatePcView();//更新台位视图
    bool pushPcToList(QList<QToolButton*> *pList);


private slots:
    void on_pushButtonAddGroup_clicked();
    bool choosePc();

private:
    Ui::MainWindow *ui;
    NewGroup *newGroupDialog;
    QList<QToolButton*> *pcList;
    //    Databox *databox;
};

#endif // MAINWINDOW_H
