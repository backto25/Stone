#include "StaffModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
/*  ************************************
class User
************************************  */
//
/*  ************************************
class UserModel
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
    return true;
}

bool StaffModel::rmOneStaff(int index){
    staffs.remove(index);
    return true;
}

int StaffModel::size() const
{ return staffs.size();}

bool StaffModel::flashBySQL(){
  staffs.clear();
  QSqlQuery sqlQueryStaff;
  sqlQueryStaff.prepare( "select staff_id, staff_name, staff_group_id, staff_role from staff" );
  Staff temp;

  if(!sqlQueryStaff.exec())
      return false;

  for(int i = 0; i < sqlQueryStaff.size(); i++){

      temp.staff_id = sqlQueryStaff.value(0).toInt();
      temp.staff_name = sqlQueryStaff.value(1).toString();
      addOneStaff(temp);

      sqlQueryStaff.next();
  }
  return true;
}
/*  ************************************
class UserModel for QAbstractTableModel
************************************  */
StaffModel::StaffModel(QObject *parent) :QAbstractTableModel(parent){
  // set users from content ContentProvider
  staffs.clear();
}

StaffModel::~StaffModel(){
  // set users from content ContentProvider
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
