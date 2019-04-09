#include "StaffModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
/*  ************************************
class Staff
************************************  */

/*
    *                *               *               *               *
                                                                */


/*  ************************************
class StaffModel
************************************  */
int StaffModel::findIndexById(int id){
    QVector<Staff>::iterator it;
    bool find = false;
    int i = 0;
    for( it=staffs.begin(); it != staffs.end(); ++it){
        if( it->staff_id == id){
            find = true;
            break;
        }
        ++i;
    }
    if(find)
        return i;
    return -1;
}

Staff StaffModel::getStaffByIndex(int index)const{
    return staffs[index];
}

bool StaffModel::addOneStaff(Staff staff){
    staffs.push_back(staff);
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("insert into staff value ('%1', '%2') ").arg(staff.staff_id).arg(staff.staff_name)))
        return false;
    return true;
}

bool StaffModel::rmOneStaff(int index){ 
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("delete from staff where 'staff_id' = %1").arg(staffs[index].staff_id)))
        return false;
    staffs.remove(index);
    return true;
}

bool StaffModel::updateOne(int id){
    QSqlQuery sqlQuery;
    int index = findIndexById(id);
    if(!sqlQuery.exec(QString(" UPDATE `poi`.`staff` SET `staff_name`='%1' WHERE  `staff_id`=%2;")
                      .arg(staffs[index].staff_name).arg(staffs[index].staff_id)))
        return false;
    return true;
}

int StaffModel::size() const
{ return staffs.size();}

bool StaffModel::flashBySQL(){
    staffs.clear();
    QSqlQuery sqlQueryStaff;
    sqlQueryStaff.prepare( "select staff_id, staff_name from staff" );
    Staff temp;

    if(!sqlQueryStaff.exec())
        return false;

    for(int i = 0; i < sqlQueryStaff.size(); i++){
        sqlQueryStaff.next();
        temp.staff_id = sqlQueryStaff.value(0).toInt();
        temp.staff_name = sqlQueryStaff.value(1).toString();
        staffs.push_back(temp);
    }
    return true;
}

/*  ************************************
class StaffModel for QAbstractTableModel
************************************  */

StaffModel::StaffModel(QObject *parent) :QAbstractTableModel(parent){
    // set users from content ContentProvider
    staffs.clear();
}
StaffModel::~StaffModel(){
    // set staffs from content ContentProvider
    staffs.clear();
}
int	StaffModel::rowCount(const QModelIndex & paren) const{
    return this->size();
}
int	StaffModel::columnCount(const QModelIndex & parent) const{
    return this->DIM;
}
QVariant StaffModel::data(const QModelIndex & index, int role) const{

    if (!index.isValid()) return QVariant();

    int nRow = index.row();
    int nCol = index.column();
    Staff staff = this->getStaffByIndex(nRow);

    if (Qt::DisplayRole == role){
        switch (nCol) {
        case 1:
            return staff.staff_id;
        case 2:
            return staff.staff_name;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

