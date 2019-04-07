#ifndef NEWGROUP_H
#define NEWGROUP_H

#include "databox.h"

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
    Databox *databox;
};

#endif // NEWGROUP_H
