#ifndef DATABOX_H
#define DATABOX_H

#include <QObject>
#include "structbox.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QToolButton>


class Databox : public QObject
{
    Q_OBJECT
public:
    explicit Databox(QObject *parent = 0);

signals:

public slots:

private:
    Staff_stc staffList[NUMOFSTAFF];
    Pc pcList[NUMOFPC];
    Group *groupList;
    Group *newGroup;

};

#endif // DATABOX_H
