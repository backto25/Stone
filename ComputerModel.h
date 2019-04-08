/*  *****************************************************
*****************************************************  */
#ifndef COMPUTERMODEL_H
#define COMPUTERMODEL_H

#include <QVector>
#include <QAbstractTableModel>
#include <QString>
/*  *****************************************************
*****************************************************  */
class Computer{
  public:
    int computer_id;
    QString computer_name;
};
/*  ************************************
************************************  */
class ComputerModel : public QAbstractTableModel{
    Q_OBJECT
  private:
    QVector<Computer> computers;

  public:
    static const int DIM = 2;

    ComputerModel(QObject *parent = 0);
    ~ComputerModel();

    int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    int findIndexById(int id);
    Computer getComputerByIndex(int index) const;
    bool addOneComputer(Computer computer);
    bool rmOneComputer(int index);
    int size()const;

    bool flashBySQL();
};
/*  ************************************
************************************  */
#endif
