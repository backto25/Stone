#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QEvent>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newGroupSecondStep = new NewGroupSecondStep();
    newGroupFirstStep = new NewGroup();
    pcList = new QList<QToolButton*>;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(23333);
    pushPcToList(pcList);

    updateView();

    connect(newGroupFirstStep, SIGNAL(askFor_addGroup_secondStep()), this, SLOT(addGroup_secondStep_choosePc()));
    connect(newGroupSecondStep, SIGNAL(backTo_addGroup_firstStep()), this, SLOT(backTo_firstStep_chooseStaff()));
    connect(newGroupSecondStep, SIGNAL(shutDown_firstStep()), this, SLOT(shutDown_firstStep()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(dealMsg()));
    for(int i = 0; i <pcList->size(); ++i){
        connect(pcList->at(i), SIGNAL(clicked()), this, SLOT(showDetailPcInfo()));
    }

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
    this->updatePcAnotherHalfInfo();
    //groupdetailinfo手动控制更新
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
bool MainWindow::updatePcHalfInfo(){


    char buf[32] = {0};
    QHostAddress cliAddr; //对方地址
    quint16 port;    //对方端口
    qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &cliAddr, &port);
    if(len <= 0)
        return false;
    for(int i = 0; i < pcList->size(); ++i){
        if(ui->label_taiwei->text() == QString("台位%1").arg(i+1)){
            //格式化 [192.68.2.2:8888]
            QString str = QString("[%1:%2]").arg(cliAddr.toString()) .arg(port);
            QString info = QString("%1").arg(buf);
            QStringList list = info.split(" ");
            if(list[0].toInt() == (i+1)){
                ui->progressBar_mem->setValue(list[1].toInt());
                ui->progressBar_cpu->setValue(list[2].toDouble());
                ui->progressBar_netspeed->setValue(list[3].toDouble());
            }

        }
    }
}
bool MainWindow::updatePcAnotherHalfInfo(){
    GroupModel &groupModel = contentProvider->group_model;
    StaffModel &staffModel =contentProvider->staff_model;

    for(int i = 0; i < pcList->size(); ++i){
        if(ui->label_taiwei->text() == QString("台位%1").arg(i+1)){
            int groupId = groupModel.whichGroupIsComputerIncluded(i+1);
            if(groupId != 0){
                QString groupName = groupModel.getGroupById(groupId).group_name;
                ui->label_xiaozu->setText(groupName);
                int insideIndex = groupModel.getGroupById(groupId).computerIndexInsideGroup(i+1);
                int staffId = groupModel.getGroupById(groupId).staffs[insideIndex];
                int staffIndex = staffModel.findIndexById(staffId);
                ui->label_renyuan->setText(staffModel.getStaffByIndex(staffIndex).staff_name);
            }
            else{
                ui->label_xiaozu->setText("未分组");
                ui->label_renyuan->setText("暂无人员");
            }
        }
    }
}
bool MainWindow::updateDetailGroupInfo(){
    QListWidgetItem * item = ui->listWidgetGroups->currentItem();
//    qDebug()<<ui->listWidgetGroups->row(item);
//    qDebug()<<item;
    if( item == NULL ){
        ui->label_zuhao->setText("No relevant information");
        ui->label_zuming->setText("No relevant information");
        ui->label_zuse->setText("No relevant information");
        ui->label_zuse->setStyleSheet("background-color: rgba(255, 255, 0, 0);");
        ui->tableWidget->setRowCount(0);
        return false;
    }
    GroupModel &groupModel = contentProvider->group_model;
    StaffModel &staffModel =contentProvider->staff_model;
    int curIndex = ui->listWidgetGroups->row(item);
    ui->label_zuhao->setText(QString("%1").arg(curIndex + 1));
    ui->label_zuming->setText(groupModel.getGroupByIndex(curIndex).group_name);
    ui->label_zuse->setText("                      ");
    ui->label_zuse->setStyleSheet(ColorSetA[groupModel.getGroupByIndex(curIndex).group_id%5]);
    ui->tableWidget->setRowCount( groupModel.getGroupByIndex(curIndex).staffs.size());
    for(int i =0; i < groupModel.getGroupByIndex(curIndex).staffs.size(); ++i){
        int staffId = groupModel.getGroupByIndex(curIndex).staffs[i];
        QString staffName = staffModel.getStaffByIndex(staffModel.findIndexById(staffId)).staff_name;
        qDebug()<<staffName;
        QTableWidgetItem * sItem = new QTableWidgetItem();
        sItem->setText(staffName);
//        sItem->setFlags(Qt::NoItemFlags)
        ui->tableWidget->setItem(i, 0, sItem);
    }
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
    pList->append(ui->toolButtonPC_13);
    pList->append(ui->toolButtonPC_14);
    pList->append(ui->toolButtonPC_15);
    pList->append(ui->toolButtonPC_16);
    pList->append(ui->toolButtonPC_17);
    pList->append(ui->toolButtonPC_18);
    pList->append(ui->toolButtonPC_19);
    pList->append(ui->toolButtonPC_20);

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
    QAction *showSeed = new QAction(tr("查看详情"), this);
    QAction *editSeed = new QAction(tr("编辑当前组"), this);
    QAction *deleteSeed = new QAction(tr("删除当前组"), this);
    QAction *clearSeeds = new QAction(tr("清空所有组"), this);
    popMenu->addAction( showSeed );
    popMenu->addAction( editSeed );
    popMenu->addAction( deleteSeed );
    popMenu->addAction( clearSeeds );
    connect( deleteSeed, SIGNAL(triggered() ), this, SLOT( deleteCurrentGroupSlot()) );
    connect( showSeed, SIGNAL(triggered() ), this, SLOT( showDetailGroupInfo()) );
    //    connect( clearSeeds, SIGNAL(triggered() ), this, SLOT( clearSeedsSlot()) );
    popMenu->exec( QCursor::pos() );
    delete popMenu;
    delete showSeed;
    delete editSeed;
    delete deleteSeed;
    delete clearSeeds;
}
void MainWindow::deleteCurrentGroupSlot()
{
    int ch = QMessageBox::warning(NULL, "警告",
                                  "您确定要删除所选组 ?",
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if ( ch != QMessageBox::Yes )
        return;

    QListWidgetItem * item = ui->listWidgetGroups->currentItem();
    if( item == NULL )
        return;

    GroupModel &groupModel = contentProvider->group_model;
    int curIndex = ui->listWidgetGroups->row(item);
    if(groupModel.rmOneGroup(curIndex)){
        QMessageBox::about(NULL, "提示", "删除成功");
        for(int i = 0; i <pcList->size(); ++i){
            pcList->at(i)->setStyleSheet("QPushButton{background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));border: 1px solid rgb(124, 124, 124);border-radius:2px;}"
                                         "QPushButton:pressed{background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(206, 234, 248, 255));border-radius:2px;border: 1px solid #5F92B2;}"
                                         "QPushButton:hover{background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));border-radius:2px;border: 1px solid #3C80B1;}"
                                         );
        }
        this->updateView();
        this->updateDetailGroupInfo();
    }
    else
        QMessageBox::about(NULL, "提示", "删除失败");
}
void MainWindow::dealMsg(){
    this->updatePcHalfInfo();
}
void MainWindow::showDetailPcInfo(){
    QToolButton *btn  = qobject_cast<QToolButton*>(sender());
    for(int i =0; i < pcList->size(); ++i){
        if(QString("toolButtonPC_%1").arg(i+1) == btn->objectName()){
            ui->label_taiwei->setText(QString("台位%1").arg(i+1));
            this->updatePcAnotherHalfInfo();
        }
    }
    ui->progressBar_mem->setValue(0);
    ui->progressBar_cpu->setValue(0);
    ui->progressBar_netspeed->setValue(0);
}
void MainWindow::showDetailGroupInfo(){

    this->updateDetailGroupInfo();
}

void MainWindow::on_listWidgetGroups_clicked(const QModelIndex &index)
{
    this->updateDetailGroupInfo();
}
