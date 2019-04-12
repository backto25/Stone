#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newGroupSecondStep = new NewGroupSecondStep();
    newGroupFirstStep = new NewGroup();
    pcList = new QList<QToolButton*>;

    pushPcToList(pcList);

    updateView();

    connect(newGroupFirstStep, SIGNAL(askFor_addGroup_secondStep()), this, SLOT(addGroup_secondStep_choosePc()));
    connect(newGroupSecondStep, SIGNAL(backTo_addGroup_firstStep()), this, SLOT(backTo_firstStep_chooseStaff()));
    connect(newGroupSecondStep, SIGNAL(shutDown_firstStep()), this, SLOT(shutDown_firstStep()));
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
    this->updateGroupBoxView();
    this->updatePcBoxView();
    this->updateStaffBoxView();
}
bool MainWindow::updateGroupBoxView()
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
bool MainWindow::updateStaffBoxView(){
    StaffModel &staffModel =contentProvider->staff_model;
    GroupModel &groupModel = contentProvider->group_model;
    ui->listWidgetStaff->clear();

    for(int i = staffModel.size() - 1; i >= 0; --i){

        QWidget *widget = new QWidget();
        widget->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        QHBoxLayout *layout = new QHBoxLayout(widget);
        QLabel *staffName = new QLabel();
        QPushButton *sex = new QPushButton();
        sex->setStyleSheet("background-color: rgba(235, 235, 235, 150);");
        layout->addWidget(staffName);
        layout->addWidget(sex);
        staffName->setText(staffModel.getStaffByIndex(i).staff_name);
        sex->setText(tr("性别"));
        widget->setLayout(layout);

        for(int j = 0; j < groupModel.size(); ++j){
            if(groupModel.getGroupByIndex(j) .isStaffIncluded(staffModel.getStaffByIndex(i).staff_id))
                staffName->setStyleSheet(ColorSetA[groupModel.getGroupByIndex(j).group_id%5]);
        }

        QListWidgetItem *aItem = new QListWidgetItem(ui->listWidgetStaff);
        ui->listWidgetStaff->addItem(aItem);
        ui->listWidgetStaff->setItemWidget(aItem, widget);
        aItem->setSizeHint(QSize(0,50));
    }
    return true;
}
void MainWindow::screen_full(){
    this->showFullScreen();
}
void MainWindow::screen_normal(){
    this->showNormal();
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

/*  *****************************************************
*****************************************************  */
void MainWindow::keyPressEvent(QKeyEvent *event){
    //空格键进入全屏，esc键退出全屏
    switch (event->key()){
    case Qt::Key_F1:
        screen_full();
        break;
    case Qt::Key_Escape:
        screen_normal();
        break;
    }
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
void MainWindow::on_listWidgetStaff_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* curItem = ui->listWidgetStaff->itemAt( pos );
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    QAction *editSeed = new QAction(tr("编辑当前人员"), this);
    QAction *deleteSeed = new QAction(tr("删除当前人员"), this);
    QAction *clearSeeds = new QAction(tr("清空所有人员"), this);
    popMenu->addAction( editSeed );
    popMenu->addAction( deleteSeed );
    popMenu->addAction( clearSeeds );
//    connect( deleteSeed, SIGNAL(triggered() ), this, SLOT( deleteSeedSlot()) );
//    connect( clearSeeds, SIGNAL(triggered() ), this, SLOT( clearSeedsSlot()) );
    popMenu->exec( QCursor::pos() );
    delete popMenu;
    delete editSeed;
    delete deleteSeed;
    delete clearSeeds;
}
void MainWindow::on_listWidgetGroups_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* curItem = ui->listWidgetGroups->itemAt( pos );
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    QAction *editSeed = new QAction(tr("编辑当前组"), this);
    QAction *deleteSeed = new QAction(tr("删除当前组"), this);
    QAction *clearSeeds = new QAction(tr("清空所有组"), this);
    popMenu->addAction( editSeed );
    popMenu->addAction( deleteSeed );
    popMenu->addAction( clearSeeds );
//    connect( deleteSeed, SIGNAL(triggered() ), this, SLOT( deleteSeedSlot()) );
//    connect( clearSeeds, SIGNAL(triggered() ), this, SLOT( clearSeedsSlot()) );
    popMenu->exec( QCursor::pos() );
    delete popMenu;
    delete editSeed;
    delete deleteSeed;
    delete clearSeeds;
}

