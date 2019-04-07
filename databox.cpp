#include "databox.h"

Databox::Databox(QObject *parent) :
    QObject(parent)
{
    QSqlQuery sqlQueryGroup;
    sqlQueryGroup.prepare( "select group_id, group_name from groups" );

    QSqlQuery sqlQueryStaff;
    sqlQueryStaff.prepare( "select staff_id, staff_name, staff_group_id, staff_role from staff" );

    QSqlQuery sqlQueryPc;
    sqlQueryPc.prepare( "select pc_id, pc_staff_id, pc_group_id from pc" );

    if(sqlQueryGroup.exec()&&sqlQueryStaff.exec()&&sqlQueryPc.exec())
    {
      for(int i = 0; i < sqlQueryStaff.size(); i++)
      {
          sqlQueryStaff.next();
          staffList[i].staff_id = sqlQueryStaff.value(0).toInt();
          staffList[i].staff_name = sqlQueryStaff.value(1).toString();
          staffList[i].staff_group_id = sqlQueryStaff.value(2).toInt();
          staffList[i].staff_role = sqlQueryStaff.value(3).toInt();
//          qDebug()<<staffList[i].staff_role;
      }
      for(int i = 0; i < sqlQueryPc.size(); i++)
      {
          sqlQueryPc.next();
          pcList[i].pc_id = sqlQueryPc.value(0).toInt();
          pcList[i].pc_staff_id = sqlQueryPc.value(1).toInt();
          pcList[i].pc_group_id = sqlQueryPc.value(2).toInt();
      }
      groupList = new Group();
      while(sqlQueryGroup.next())
      {
          groupList->group_id = sqlQueryGroup.value(0).toInt();
          groupList->group_name = sqlQueryGroup.value(1).toString();
//          qDebug()<<groupList->group_name;
          groupList->pcMemberList = new Pc();
          for(int i = 0; i < NUMOFPC; i++)
          {
              if(pcList[i].pc_group_id == groupList->group_id)
              {
                  groupList->pcMemberList = &pcList[i];
//                  qDebug()<<groupList->pcMemberList->pc_id;
                  groupList->pcMemberList++;
              }
          }
          groupList->staffMemberList = new Staff_stc();
          for(int i = 0; i < NUMOFSTAFF; i++)
          {
              if(staffList[i].staff_group_id == groupList->group_id)
              {
                  groupList->staffMemberList = &staffList[i];
//                  qDebug()<<groupList->staffMemberList->staff_name;
                  groupList->staffMemberList++;
              }
          }
      }
    }
}
