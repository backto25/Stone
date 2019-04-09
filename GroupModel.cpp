#include "GroupModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
/*  ************************************
class Group
************************************  */
bool Group::isStaffIncluded(int staffId){
    return staffs.contains(staffId);
}

bool Group::isComputerIncluded(int computerId){
    return computers.contains(computerId);
}

/*  ************************************
class GroupModel
************************************  */
int GroupModel::findIndexById(int id){
    QVector<Group>::iterator it;
    bool find = false;
    int i = 0;
    for( it=groups.begin(); it != groups.end(); ++it){
        if( it->group_id == id){
            find = true;
            break;
        }
        ++i;
    }
    if(find)
        return i;
    return -1;
}

Group GroupModel::getGroupByIndex(int index)const{
    return groups[index];
}

QVector<int> GroupModel::findByType(int type){
    QVector<int> ret;
    QVector<Group>::iterator it;
    int i = 0;
    for( it=groups.begin(); it != groups.end(); ++it){
        if( it->group_type == type){
            ret.push_back(i);
        }
        ++i;
    }
    return ret;
}

bool GroupModel::addOneGroup(Group group){
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("select * from `group` where group_id = %1").arg(group.group_id));
    if(sqlQuery.size()!=0){
      qDebug()<<"group have"<<group.group_id;
      return false;
    }

    if(!sqlQuery.exec(QString("insert into `group` values ('%1', '%2') ")
                      .arg(group.group_id).arg(group.group_name))){
        qDebug()<<QString("insert into `group` values ('%1', '%2') ").arg(group.group_id).arg(group.group_name);
        return false;
    }

    for(int i = 0; i < group.staffs.size(); ++i)
    {
        if(!sqlQuery.exec(QString("insert into group_staff values ('%1', '%2') ")
                          .arg(group.group_id).arg(group.staffs[i]))){
            qDebug()<<QString("insert into group_staff values ('%1', '%2') ").arg(group.group_id).arg(group.staffs[i]);
            return false;
        }
    }

    for(int i = 0; i < group.computers.size(); ++i)
    {
        if(!sqlQuery.exec(QString("insert into group_pc values ('%1', '%2') ")
                          .arg(group.group_id).arg(group.computers[i]))){
            qDebug()<<QString("insert into group_pc values ('%1', '%2') ");
            return false;
        }
    }

    groups.push_back(group);
    return true;
}

bool GroupModel::rmOneGroup(int index){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("delete from 'group' where group_id = '%1' ")
                      .arg(groups[index].group_id)))
        return false;
    groups.remove(index);
    return true;
}

int GroupModel::size() const
{ return groups.size();}

bool GroupModel::flashBySQL(){
    groups.clear();
    QSqlQuery sqlQueryGroup;
    QSqlQuery sqlQueryGroupStaff;
    QSqlQuery sqlQueryGroupPC;

    Group temp;
    sqlQueryGroup.prepare( "select group_id, group_name from `group`" );
    if(!sqlQueryGroup.exec())
        return false;

    for(int i = 0; i < sqlQueryGroup.size(); i++){
        sqlQueryGroup.next();
        temp.group_id = sqlQueryGroup.value(0).toInt();
        temp.group_name = sqlQueryGroup.value(1).toString();

        sqlQueryGroupStaff.prepare(QString( "select staff_id from group_staff where group_id = %1" ).arg(temp.group_id));
        if(!sqlQueryGroupStaff.exec())
            return false;
        for(int i = 0; i < sqlQueryGroupStaff.size(); i++){
            sqlQueryGroupStaff.next();
            temp.staffs.push_back(sqlQueryGroupStaff.value(0).toInt());
        }

        sqlQueryGroupPC.prepare(QString( "select pc_id from group_pc where group_id = %1" ).arg(temp.group_id));
        if(!sqlQueryGroupPC.exec())
            return false;
        for(int i = 0; i < sqlQueryGroupPC.size(); i++){
            sqlQueryGroupPC.next();
            temp.computers.push_back(sqlQueryGroupPC.value(0).toInt());
        }
        groups.push_back(temp);
    }
    return true;
}

bool GroupModel::updateOne(int id){
    QSqlQuery sqlQuery;
    int index = this->findIndexById(id);
    if(!sqlQuery.exec(QString("UPDATE `poi`.`group` SET `group_name`='%1' WHERE  `group_id`='%2'; ")
                      .arg(groups[index].group_name).arg(groups[index].group_id)))
        return false;
    for(int i = 0; i < groups[index].staffs.size(); ++i)
    {
        if(!sqlQuery.exec(QString("insert into group_staff value ('%1', '%2') ")
                          .arg(groups[index].group_id).arg(groups[index].staffs[i])))
            return false;
    }
    for(int i = 0; i < groups[index].computers.size(); ++i)
    {
        if(!sqlQuery.exec(QString("insert into group_pc value ('%1', '%2') ")
                          .arg(groups[index].group_id).arg(groups[index].computers[i])))
            return false;
    }
    return true;
}

bool GroupModel::isStaffIncluded(int staffId){
    QVector<Group>::iterator it;
    bool find = false;
    for( it=groups.begin(); it != groups.end(); ++it){
        if( it->isStaffIncluded(staffId)){
            find = true;
            break;
        }
    }
    return find;
}

bool GroupModel::isComputerIncluded(int computerId){
    QVector<Group>::iterator it;
    bool find = false;
    for( it=groups.begin(); it != groups.end(); ++it){
        if( it->isComputerIncluded(computerId)){
            find = true;
            break;
        }
    }
    return find;
}


/*  ************************************
class ComputerModel for QAbstractTableModel
************************************  */
GroupModel::GroupModel(QObject *parent) :QAbstractTableModel(parent){
    // set users from content ContentProvider
    groups.clear();
}

GroupModel::~GroupModel(){
    // set users from content ContentProvider
    groups.clear();
}

int	GroupModel::rowCount(const QModelIndex & paren) const{
    return this->size();
}

int	GroupModel::columnCount(const QModelIndex & parent) const{
    return this->DIM;
}
QVariant GroupModel::data(const QModelIndex & index, int role) const{

    if (!index.isValid()) return QVariant();

    int nRow = index.row();
    int nCol = index.column();
    Group group = this->getGroupByIndex(nRow);

    if (Qt::DisplayRole == role){
        switch (nCol) {
        case 1:
            return group.group_id;
        case 2:
            return group.group_name;
        default:
            return QVariant();
        }
    }

    return QVariant();
}
