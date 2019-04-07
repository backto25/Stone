#ifndef STRUCTBOX_H
#define STRUCTBOX_H

#define NUMOFSTAFF 12
#define NUMOFPC 12

#include<QString>

typedef struct Staff_struct{
    int staff_id;
    QString staff_name;
    int staff_group_id;
    int staff_role;
}Staff_stc;

typedef struct Pc_struct{
    int pc_id;
    int pc_staff_id;
    int pc_group_id;
}Pc;

typedef struct Group_struct{
    int group_id;
    QString group_name;
    Staff_stc *staffMemberList;
    Pc *pcMemberList;
}Group;

#endif // STRUCTBOX_H
