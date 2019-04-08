#ifndef NEWGROUP_H
#define NEWGROUP_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QToolButton>
#include "ContentProvider.h"

namespace Ui {
class NewGroup;
}

class NewGroup : public QWidget
{
    Q_OBJECT

public:
    explicit NewGroup(QWidget *parent = 0);
    ~NewGroup();

    bool initStaffList();

private slots:
    bool on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

signals:
    bool choosePc();

private:
    Ui::NewGroup *ui;
};

#endif // NEWGROUP_H
