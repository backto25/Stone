#include "ComputerModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
/*  ************************************
class Computer
************************************  */

/*
    *                *               *               *               *
                                                                */


/*  ************************************
class ComputerModel
************************************  */
int ComputerModel::findIndexById(int id){
    QVector<Computer>::iterator it;
    bool find = false;
    int i = 0;
    for( it=computers.begin(); it != computers.end(); ++it){
        if( it->computer_id == id){
            find = true;
            break;
        }
        ++i;
    }
    if(find)
        return i;
    return -1;
}

Computer ComputerModel::getComputerByIndex(int index)const{
    return computers[index];
}

bool ComputerModel::addOneComputer(Computer computer){
    computers.push_back(computer);
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("insert into pc value ('%1') ").arg(computer.computer_id)))
        return false;
    return true;
}

bool ComputerModel::rmOneComputer(int index){
    computers.remove(index);
    return true;
}

int ComputerModel::size() const
{ return computers.size();}

bool ComputerModel::flashBySQL(){
    computers.clear();
    QSqlQuery sqlQuery;
    sqlQuery.prepare( "select pc_id from pc" );
    Computer temp;

    if(!sqlQuery.exec())
        return false;

    for(int i = 0; i < sqlQuery.size(); i++){
        sqlQuery.next();
        temp.computer_id = sqlQuery.value(0).toInt();
        addOneComputer(temp);
    }
    return true;
}

/*  ************************************
class ComputerModel for QAbstractTableModel
************************************  */

ComputerModel::ComputerModel(QObject *parent) :QAbstractTableModel(parent){
    // set users from content ContentProvider
    computers.clear();
}
ComputerModel::~ComputerModel(){
    // set users from content ContentProvider
    computers.clear();
}
int	ComputerModel::rowCount(const QModelIndex & paren) const{
    return this->size();
}
int	ComputerModel::columnCount(const QModelIndex & parent) const{
    return this->DIM;
}
QVariant ComputerModel::data(const QModelIndex & index, int role) const{

    if (!index.isValid()) return QVariant();

    int nRow = index.row();
    int nCol = index.column();
    Computer computer = this->getComputerByIndex(nRow);

    if (Qt::DisplayRole == role){
        switch (nCol) {
        case 1:
            return computer.computer_id;
        case 2:
            return computer.computer_name;
        default:
            return QVariant();
        }
    }

    return QVariant();
}
bool ComputerModel::saveToDB(){
    return true;
}
