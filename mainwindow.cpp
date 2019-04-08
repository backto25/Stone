#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//加载qt设计师

    pcList = new QList<QToolButton*>;//把PC实体(按钮)放入一个Qlist
    pushPcToList(pcList);

    //    Databox *databox = new Databox();

    initUI();//字面意思

    connect(newGroupDialog, SIGNAL(choosePc()), this, SLOT(choosePc()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pcList;
    //    delete databox;
}

void MainWindow::on_pushButtonAddGroup_clicked()
{
    QSqlQuery sqlQueryGroups;
    QString sqlStr = "select group_id, group_name from group";
    sqlQueryGroups.prepare( sqlStr );
    sqlQueryGroups.exec();
    //        qDebug()<<sqlQueryGroups.size()<<endl;

    newGroupDialog = new NewGroup(NULL);
    newGroupDialog->setWindowTitle(QString("%1组").arg(sqlQueryGroups.size()));//更新title

    newGroupDialog->show();
}

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

bool MainWindow::updateGroupList()
{
    /*  *****************************************************
     * 初始化listWidgetGroups
    *****************************************************  */
    QSqlQuery sqlQueryGroups;
    QString sqlStr = "select group_id, group_name from `group`";
    sqlQueryGroups.prepare( sqlStr );

    if( sqlQueryGroups.exec() )
    {
        //        qDebug()<<"查询groups成功"<<endl;
        //            qDebug()<<sqlQuery.value(1).toString()<<endl;
        while( sqlQueryGroups.next() )
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
            groupName->setText(sqlQueryGroups.value(1).toString());
            switch(sqlQueryGroups.value(0).toInt())
            {
            case 0:break;//未分组的电脑不处理
            case 1:groupName->setStyleSheet("background-color: rgba(255, 0, 0, 100);");break;
            case 2:groupName->setStyleSheet("background-color: rgba(255, 153, 0, 100);");break;
            case 3:groupName->setStyleSheet("background-color: rgba(0, 255, 255, 100);");break;
            case 4:groupName->setStyleSheet("background-color: rgba(0, 255, 0, 100);");break;
            case 5:groupName->setStyleSheet("background-color: rgba(255, 255, 0, 100);");break;
            }
            btnProgressOn->setText(tr("开始训练"));
            widgetGroup->setLayout(layout);

            //插入表项
            QListWidgetItem *aItem = new QListWidgetItem(ui->listWidgetGroups);
            ui->listWidgetGroups->addItem(aItem);
            ui->listWidgetGroups->setItemWidget(aItem, widgetGroup);
            aItem->setSizeHint(QSize(0,50));
        }
    }
    return true;
}

bool MainWindow::updatePcView()
{
    GroupModel &groupModel =contentProvider->group_model;
   ComputerModel &computerModel =contentProvider->computer_model;

    for(int i = 0; i < groupModel.size(); ++i)
    {
        QVector<int> temp = groupModel.getGroupByIndex(i).computers;
        qDebug()<<"temp.size()"<<temp.size();
        Computer pcTemp;
        for(int j = 0; j < temp.size(); ++j){
            if(computerModel.findIndexById(temp[j]) != -1) {
                pcTemp=computerModel.getComputerByIndex(computerModel.findIndexById(temp[j]));
                pcList->at(pcTemp.computer_id-1)->setStyleSheet(ColorSetA[i%5]);
           }
        }


    }



//    if( 0 )
//    {
//        //        qDebug()<<"查询pc成功"<<endl;
//        while( 0 )
//        {
//            switch(sqlQueryPc.value(2).toInt())
//            {
//            case 0:break;//未分组的电脑不处理
//            case 1:pcList->at(indexOfPc)->setStyleSheet("background-color: rgba(255, 0, 0, 100);");break;
//            case 2:pcList->at(indexOfPc)->setStyleSheet("background-color: rgba(255, 153, 0, 100);");break;
//            case 3:pcList->at(indexOfPc)->setStyleSheet("background-color: rgba(0, 255, 255, 100);");break;
//            case 4:pcList->at(indexOfPc)->setStyleSheet("background-color: rgba(0, 255, 0, 100);");break;
//            case 5:pcList->at(indexOfPc)->setStyleSheet("background-color: rgba(255, 255, 0, 100);");break;
//            }
//        }
//    }
}

bool MainWindow::initUI()
{
    this->updateGroupList();
    this->updatePcView();
}

bool MainWindow::choosePc()
{

}
