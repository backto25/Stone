#include "ContentProvider.h"

QSharedPointer<ContentProvider>& ContentProvider::getContentProvider(){

    if(Qptr_contentProvider.isNull()){
        QMutexLocker mutexLocker(&m_Mutex);
        if(Qptr_contentProvider.isNull()){
            Qptr_contentProvider = QSharedPointer<ContentProvider>(new ContentProvider());
        }
    }
    return Qptr_contentProvider;
}

bool ContentProvider::flashAllBySQL(){
    staff_model.flashBySQL();
    computer_model.flashBySQL();
    group_model.flashBySQL();
}

QMutex ContentProvider::m_Mutex;
QSharedPointer<ContentProvider> ContentProvider::Qptr_contentProvider;

StaffModel ContentProvider::staff_model;
ComputerModel ContentProvider::computer_model;
GroupModel ContentProvider::group_model;

QSharedPointer<ContentProvider> contentProvider = ContentProvider::getContentProvider();
