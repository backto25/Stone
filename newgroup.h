/*  *****************************************************
*****************************************************  */
#ifndef NEWGROUP_H
#define NEWGROUP_H

#include <QWidget>

#include "ContentProvider.h"
/*  *****************************************************
*****************************************************  */
namespace Ui {
class NewGroup;
}

class NewGroup : public QWidget
{
    Q_OBJECT

public:
    explicit NewGroup(QWidget *parent = 0);
    ~NewGroup();

    bool chooseStaffView();


private slots:
    bool on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();


signals:
    bool askFor_addGroup_secondStep();

private:
    Ui::NewGroup *ui;
};

#endif // NEWGROUP_H
