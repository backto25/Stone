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

    newGroupSecondStep = new NewGroupSecondStep();
    newGroupFirstStep = new NewGroup();
    pcList = new QList<QToolButton*>;

    m_contextMenu = new QMenu;
    m_editAction = new QAction("编辑分组", this);
    m_delAction = new QAction("删除分组", this);
    m_contextMenu->addAction(m_editAction);
    m_contextMenu->addAction(m_delAction);

    pushPcToList(pcList);

    updateView();

    connect(newGroupFirstStep, SIGNAL(askFor_addGroup_secondStep()), this, SLOT(addGroup_secondStep_choosePc()));
    connect(newGroupSecondStep, SIGNAL(backTo_addGroup_firstStep()), this, SLOT(backTo_firstStep_chooseStaff()));
    connect(newGroupSecondStep, SIGNAL(shutDown_firstStep()), this, SLOT(shutDown_firstStep()));
    connect(ui->listWidgetGroups, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showListWidgetMenuSlot(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pcList;
    delete newGroupFirstStep;
    delete newGroupSecondStep;
}

/*  *****************************************************
*****************************************************  */

bool MainWindow::updateView()
{
    this->updateGroupManegeView();
    this->updatePcBoxView();
}

bool MainWindow::updateGroupManegeView()
{
    GroupModel &groupModel = contentProvider->group_model;

    ui->listWidgetGroups->clear();

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
//右键菜单
    ui->listWidgetGroups->setContextMenuPolicy(Qt::CustomContextMenu);

    return true;
}

bool MainWindow::updatePcBoxView()
{
    GroupModel &groupModel = contentProvider->group_model;
    ComputerModel &computerModel = contentProvider->computer_model;
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
    return true;
}

/*  *****************************************************
*****************************************************  */

void MainWindow::on_pushButtonAddGroup_clicked()
{

    newGroupFirstStep->chooseStaffView();
    newGroupFirstStep->show();
}

bool MainWindow::addGroup_secondStep_choosePc()
{
    newGroupSecondStep->chooseComputerView();
    newGroupSecondStep->show();
    return true;
}

bool MainWindow::backTo_firstStep_chooseStaff(){
    newGroupFirstStep->show();
    return true;
}

bool MainWindow::shutDown_firstStep(){
    newGroupFirstStep->close();
    this->updateView();
    return true;
}

void MainWindow::showListWidgetMenuSlot(QPoint pos)
{
    m_contextMenu->exec(QCursor::pos());
}
/*  *****************************************************
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


