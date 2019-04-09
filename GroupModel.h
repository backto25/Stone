/*  *****************************************************
*****************************************************  */
#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QVector>
#include <QAbstractTableModel>
#include <QString>

#include "ComputerModel.h"
#include "StaffModel.h"
/*  *****************************************************
*****************************************************  */
class Group{
public:

    int group_id;
    int group_type;
    QString group_name;

    QVector<int> staffs;
    QVector<int> computers;

public:

    bool isStaffIncluded(int staffId);
    bool isComputerIncluded(int computerId);
};
/*  ************************************
************************************  */
class GroupModel : public QAbstractTableModel{
    Q_OBJECT
private:
    QVector<Group> groups;

public:
    static const int DIM = 5;
    Group tempGroup;

    GroupModel(QObject *parent = 0);
    ~GroupModel();

    int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    int findIndexById(int id);
    QVector<int> findByType(int type);
    Group getGroupByIndex(int index) const;
    bool addOneGroup(Group group);
    bool rmOneGroup(int index);
    int size()const;
    bool isStaffIncluded(int staffId);
    bool isComputerIncluded(int computerId);

    bool flashBySQL();
    bool updateOne(int id);
};
/*  ************************************
************************************  */
#endif
