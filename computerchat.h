#ifndef COMPUTERCHAT_H
#define COMPUTERCHAT_H

#include <QThread>
#include "ComputerModel.h"



class ComputerChat: public QThread
{
public:
    ComputerChat();
    virtual void run();
    bool getComputerInfo();

};

#endif // COMPUTERCHAT_H
