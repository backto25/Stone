#include "ContentProvider.h"

QMutex ContentProvider::m_Mutex;
QSharedPointer<ContentProvider> ContentProvider::Qptr_contentProvider;

StaffModel ContentProvider::staff_model;
ComputerModel ContentProvider::computer_model;
GroupModel ContentProvider::group_model;

QSharedPointer<ContentProvider> contentProvider = ContentProvider::getContentProvider();
