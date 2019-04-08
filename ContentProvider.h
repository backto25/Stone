/*  *****************************************************
*****************************************************  */
#ifndef CONTENT_H
#define CONTENT_H

#include <QMutex>
#include <QSharedPointer>

#include "StaffModel.h"
#include "ComputerModel.h"
#include "GroupModel.h"
/*  *****************************************************
*****************************************************  */
class ContentProvider{
private:
    ContentProvider(){}
    ContentProvider(const ContentProvider &){}
    ContentProvider& operator=(const ContentProvider&){}

    static QMutex m_Mutex;
    static QSharedPointer<ContentProvider> Qptr_contentProvider;

public:
    static StaffModel staff_model;
    static ComputerModel computer_model;
    static GroupModel group_model;

    static QSharedPointer<ContentProvider>& getContentProvider();
    static bool flashAllBySQL();

};
/*  *****************************************************
*****************************************************  */
extern QSharedPointer<ContentProvider> contentProvider;
/*  *****************************************************
*****************************************************  */
static QString ColorSetA[5] = {
    "background-color: rgba(255, 0, 0, 100);",
    "background-color: rgba(0, 255, 0, 100);",
    "background-color: rgba(0, 0, 255, 100);",
    "background-color: rgba(255, 0, 0, 100);",
    "background-color: rgba(255, 0, 0, 100);",
}    ;
#endif
