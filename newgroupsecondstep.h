#ifndef NEWGROUPSECONDSTEP_H
#define NEWGROUPSECONDSTEP_H

#include <QWidget>

#include "ContentProvider.h"

namespace Ui {
class NewGroupSecondStep;
}

class NewGroupSecondStep : public QWidget
{
    Q_OBJECT

public:
    explicit NewGroupSecondStep(QWidget *parent = 0);
    ~NewGroupSecondStep();

     bool chooseComputerView();

private slots:
    void on_pushButtonLastStep_clicked();

    void on_pushButtonSave_clicked();

signals:
    bool backTo_addGroup_firstStep();

    bool shutDown_firstStep();

private:
    Ui::NewGroupSecondStep *ui;
};

#endif // NEWGROUPSECONDSTEP_H
