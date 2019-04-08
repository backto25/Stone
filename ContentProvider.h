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

    static QSharedPointer<ContentProvider>& getContentProvider(){

        if(Qptr_contentProvider.isNull()){
            QMutexLocker mutexLocker(&m_Mutex);
            if(Qptr_contentProvider.isNull()){
                Qptr_contentProvider = QSharedPointer<ContentProvider>(new ContentProvider());
            }
        }
        return Qptr_contentProvider;
    }

};
/*  *****************************************************
*****************************************************  */
extern QSharedPointer<ContentProvider> contentProvider;
/*  *****************************************************
*****************************************************  */
#endif
