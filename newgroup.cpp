#include "newgroup.h"
#include "ui_newgroup.h"

NewGroup::NewGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGroup)
{
    ui->setupUi(this);
    initStaffList();
}

NewGroup::~NewGroup()
{
    delete ui;
}
bool NewGroup::initStaffList()
{
    StaffModel &staffModel =contentProvider->staff_model;
    staffModel.flashBySQL();
    for(int i=0;i<staffModel.size();++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(staffModel.getStaffByIndex(i).staff_name);
        ui->listWidgetStaffs->addItem(item);
    }
}
bool NewGroup::on_pushButtonOK_clicked()
{
    QItemSelectionModel *selections = ui->listWidgetStaffs->selectionModel(); //返回当前的选择模式
    QModelIndexList selectedsList = selections->selectedIndexes(); //返回所有选定的模型项目索引列表
    //    qDebug()<<selectedsList.count()<<endl;

    std::vector<int> vecItemIndex;//保存选中行的索引
    for (int i = 0; i < selectedsList.count(); i++)
    {
        vecItemIndex.push_back((selectedsList.at(i).row() + 1));
        //        qDebug()<<(selectedsList.at(i).row() + 1)<<endl;
    }
    if(ui->lineEditInputGroupName->text() == "")
        QMessageBox::warning(this, tr("警告"), tr("组名不能为空！"));
    else if(selectedsList.count() == 0)
        QMessageBox::warning(this, tr("警告"), tr("您未选择组员呢！"));
    else
    {
        QSqlQuery sqlQueryGroups;
        QString sqlStr = "select group_id, group_name from groups";
        sqlQueryGroups.prepare( sqlStr );
        sqlQueryGroups.exec();
        int  tempGroupId = sqlQueryGroups.size() + 1;
        for(int i=0 ;i<vecItemIndex.size();i++)
        {
            //        usedStaffId.push_back(vecItemIndex[i]);
            QSqlQuery sqlQuery;
            QString sqlStr = QString("update staff set staff_group_id =  '%1'  where staff_id = '%2' ")
                    .arg(tempGroupId).arg(vecItemIndex[i]);
            sqlQuery.prepare( sqlStr );
            sqlQuery.exec();

            QSqlQuery sqlQuery02;
            QString sqlStr02 = QString("insert into groups (group_id, group_name) values ('%1', '%2')")
                    .arg(tempGroupId).arg(ui->lineEditInputGroupName->text());
            sqlQuery02.prepare( sqlStr02 );
            sqlQuery02.exec();
        }
        emit choosePc();
        this->close();
    }

}
void NewGroup::on_pushButtonCancel_clicked()
{
    this->hide();
}
