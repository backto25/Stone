/*  *****************************************************
*****************************************************  */
#ifndef STAFFMODEL_H
#define STAFFMODEL_H

#include <QVector>
#include <QAbstractTableModel>
#include <QString>
/*  *****************************************************
*****************************************************  */
class Staff{
public:
    int staff_id;
    QString staff_name;
};
/*  ************************************
************************************  */
class StaffModel : public QAbstractTableModel{
    Q_OBJECT
private:
    QVector<Staff> staffs;

public:
    static const int DIM = 2;

    StaffModel(QObject *parent = 0);
    ~StaffModel();

    int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    int findIndexById(int id);
    Staff getStaffByIndex(int index) const;
    bool addOneStaff(Staff staff);
    bool rmOneStaff(int index);
    int size()const;

    bool flashBySQL();
    bool updateOne(int id);

};
/*  ************************************
************************************  */
#endif
