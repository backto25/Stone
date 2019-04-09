#include "newgroup.h"
#include "ui_newgroup.h"
#include <QMessageBox>
#include<QDebug>




NewGroup::NewGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGroup)
{
    ui->setupUi(this);
}

NewGroup::~NewGroup()
{
    delete ui;
}

/*  *****************************************************
*****************************************************  */

bool NewGroup::chooseStaffView(){
    GroupModel &groupModel = contentProvider->group_model;
    StaffModel &staffModel =contentProvider->staff_model;

    this->setWindowTitle(QString("%1组").arg(groupModel.size() + 1 ));//更新title
    ui->listWidgetStaffs->clear();
    for(int i=0;i<staffModel.size();++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(staffModel.getStaffByIndex(i).staff_name);
        ui->listWidgetStaffs->addItem(item);
        if(groupModel.isStaffIncluded(staffModel.getStaffByIndex(i).staff_id))
            ui->listWidgetStaffs->setItemHidden(
                        ui->listWidgetStaffs->item(staffModel.getStaffByIndex(i).staff_id - 1), true);
    }
    return true;
}

/*  *****************************************************
*****************************************************  */

bool NewGroup::on_pushButtonOK_clicked()
{
    QItemSelectionModel *selections = ui->listWidgetStaffs->selectionModel(); //返回当前的选择模式
    QModelIndexList selectedsList = selections->selectedIndexes(); //返回所有选定的模型项目索引列表

    if(ui->lineEditInputGroupName->text() == "")
        QMessageBox::warning(this, tr("警告"), tr("组名不能为空！"));
    else if(selectedsList.count() == 0)
        QMessageBox::warning(this, tr("警告"), tr("您未选择组员呢！"));
    else
    {
        GroupModel &groupModel = contentProvider->group_model;
        Group &tempGroup = contentProvider->group_model.tempGroup;
        tempGroup.group_id = groupModel.size() + 1;
        tempGroup.group_name = ui->lineEditInputGroupName->text();
        tempGroup.staffs.clear();
        for (int i = 0; i < selectedsList.count(); i++){
            tempGroup.staffs.push_back((selectedsList.at(i).row() + 1));
        }
        emit askFor_addGroup_secondStep();
        this->hide();
        return true;
    }
}

void NewGroup::on_pushButtonCancel_clicked()
{
    this->close();
}

/*  *****************************************************
*****************************************************  */
