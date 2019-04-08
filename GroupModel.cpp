#include "GroupModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
/*  ************************************
class Computer
************************************  */
//
/*  ************************************
class ComputerModel
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
    groups.push_back(group);
    return true;
}

bool GroupModel::rmOneGroup(int index){
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
    sqlQueryGroup.prepare( "select group_id, group_name from group" );
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
        addOneGroup(temp);
    }
    return true;
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
