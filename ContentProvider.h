/*  *****************************************************
*****************************************************  */
#ifndef CONTENT_H
#define CONTENT_H

#include "StaffModel.h"
#include "ComputerModel.h"
#include "GroupModel.h"
/*  *****************************************************
*****************************************************  */
class ContentProvider{
private:

public:
    StaffModel staff_model;
    ComputerModel computer_model;
    GroupModel group_model;

};

extern ContentProvider contentProvider;
/*  *****************************************************
*****************************************************  */
#endif
