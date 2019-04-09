#include "newgroupsecondstep.h"
#include "ui_newgroupsecondstep.h"
#include <QDebug>
#include <QMessageBox>

NewGroupSecondStep::NewGroupSecondStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGroupSecondStep)
{
    ui->setupUi(this);
}
/*  *****************************************************
*****************************************************  */

NewGroupSecondStep::~NewGroupSecondStep()
{
    delete ui;
}

/*  *****************************************************
*****************************************************  */

bool NewGroupSecondStep::chooseComputerView(){
    GroupModel &groupModel = contentProvider->group_model;
    ComputerModel &computerModel =contentProvider->computer_model;
    Group &tempGroup = contentProvider->group_model.tempGroup;
    this->setWindowTitle(QString("%1组").arg(tempGroup.group_id) + 1);//更新title
    ui->label_3->setText(tempGroup.group_name);
    ui->listWidget->clear();
    for(int i=0;i<computerModel.size();++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString("电脑（编号：00%1）")
                      .arg(computerModel.getComputerByIndex(i).computer_id));
        ui->listWidget->addItem(item);
        if(groupModel.isComputerIncluded(computerModel.getComputerByIndex(i).computer_id))
            ui->listWidget->setItemHidden(
                        ui->listWidget->item(computerModel.getComputerByIndex(i).computer_id - 1), true);
    }
    return true;
}

/*  *****************************************************
*****************************************************  */

void NewGroupSecondStep::on_pushButtonLastStep_clicked()
{
    this->hide();
    emit backTo_addGroup_firstStep();
}

void NewGroupSecondStep::on_pushButtonSave_clicked()
{
    GroupModel &groupModel = contentProvider->group_model;
    Group &tempGroup = contentProvider->group_model.tempGroup;

    QItemSelectionModel *selections = ui->listWidget->selectionModel(); //返回当前的选择模式
    QModelIndexList selectedsList = selections->selectedIndexes(); //返回所有选定的模型项目索引列表

    if(selectedsList.count() == 0)
        QMessageBox::warning(this, tr("警告"), tr("您未选择电脑呢！"));
    else if(selectedsList.count() != tempGroup.staffs.size())
        QMessageBox::warning(this, tr("警告"), tr("电脑与人数不匹配！"));
    else
    {
        tempGroup.computers.clear();
        for (int i = 0; i < selectedsList.count(); i++){
            tempGroup.computers.push_back((selectedsList.at(i).row() + 1));
        }
        groupModel.addOneGroup(tempGroup);
        emit shutDown_firstStep();
        this->close();
    }
}

/*  *****************************************************
*****************************************************  */
