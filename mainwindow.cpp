#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pcList = new QList<QToolButton*>;
    newGroupDialog = new NewGroup();

    pushPcToList(pcList);

    initUI();

    connect(newGroupDialog, SIGNAL(askFor_addGroup_secondStep(Group)), this, SLOT(addGroup_secondStep_choosePc(Group)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pcList;
    delete newGroupDialog;
}
/*  *****************************************************
视图更新
*****************************************************  */
bool MainWindow::initUI()
{
    this->updateGroupManegeView();
    this->updatePcBoxView();
}

bool MainWindow::updateGroupManegeView()
{
    GroupModel &groupModel = contentProvider->group_model;

    for(int i = 0; i < groupModel.size(); ++i)
    {
        //自定义控件
        QWidget *widgetGroup = new QWidget();
        widgetGroup->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        QHBoxLayout *layout = new QHBoxLayout(widgetGroup);
        QLabel *groupName = new QLabel();
        QPushButton *btnProgressOn = new QPushButton();
        btnProgressOn->setStyleSheet("background-color: rgba(235, 235, 235, 150);");
        layout->addWidget(groupName);
        layout->addWidget(btnProgressOn);
        groupName->setText(groupModel.getGroupByIndex(i).group_name);
        groupName->setStyleSheet(ColorSetA[groupModel.getGroupByIndex(i).group_id%5]);
        btnProgressOn->setText(tr("开始训练"));
        widgetGroup->setLayout(layout);

        //插入表项
        QListWidgetItem *aItem = new QListWidgetItem(ui->listWidgetGroups);
        ui->listWidgetGroups->addItem(aItem);
        ui->listWidgetGroups->setItemWidget(aItem, widgetGroup);
        aItem->setSizeHint(QSize(0,50));
    }
    return true;
}

bool MainWindow::updatePcBoxView()
{
    GroupModel &groupModel =contentProvider->group_model;
    ComputerModel &computerModel =contentProvider->computer_model;

    for(int i = 0; i < groupModel.size(); ++i)
    {
        QVector<int> temp = groupModel.getGroupByIndex(i).computers;
        Computer pcTemp;
        for(int j = 0; j < temp.size(); ++j){
            if(computerModel.findIndexById(temp[j]) != -1) {
                pcTemp=computerModel.getComputerByIndex(computerModel.findIndexById(temp[j]));
                pcList->at(pcTemp.computer_id-1)->setStyleSheet(
                            ColorSetA[groupModel.getGroupByIndex(i).group_id%5]);
            }
        }
    }
}
/*  *****************************************************
槽函数
*****************************************************  */
//新建分组按钮
void MainWindow::on_pushButtonAddGroup_clicked()
{
    newGroupDialog->show();
}
//？？？
bool MainWindow::addGroup_secondStep_choosePc(Group tempGroup)
{
    qDebug()<<"choosePc槽函数";
    return true;
}
/*  *****************************************************
成员函数
*****************************************************  */
bool MainWindow::pushPcToList(QList<QToolButton*> *pList)
{
    pList->append(ui->toolButtonPC_1);
    pList->append(ui->toolButtonPC_2);
    pList->append(ui->toolButtonPC_3);
    pList->append(ui->toolButtonPC_4);
    pList->append(ui->toolButtonPC_5);
    pList->append(ui->toolButtonPC_6);
    pList->append(ui->toolButtonPC_7);
    pList->append(ui->toolButtonPC_8);
    pList->append(ui->toolButtonPC_9);
    pList->append(ui->toolButtonPC_10);
    pList->append(ui->toolButtonPC_11);
    pList->append(ui->toolButtonPC_12);

    return true;
}
