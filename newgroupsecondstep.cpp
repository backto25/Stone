#include "newgroupsecondstep.h"
#include "ui_newgroupsecondstep.h"
#include <QDebug>

NewGroupSecondStep::NewGroupSecondStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGroupSecondStep)
{
    ui->setupUi(this);
}

NewGroupSecondStep::~NewGroupSecondStep()
{
    delete ui;
}

bool NewGroupSecondStep::chooseComputerView(){
    GroupModel &groupModel = contentProvider->group_model;
    ComputerModel &computerModel =contentProvider->computer_model;
    Group &tempGroup = contentProvider->group_model.tempGroup;
    this->setWindowTitle(QString("%1组").arg(tempGroup.group_id) + 1);//更新title
    ui->label_3->setText(tempGroup.group_name);
    qDebug()<<tempGroup.group_name;
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

void NewGroupSecondStep::on_pushButtonLastStep_clicked()
{
    this->hide();
    emit backTo_addGroup_firstStep();
}
