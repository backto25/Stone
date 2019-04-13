#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSharedMemory>

bool connectDB();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MM");

    //创建共享内存,判断是否已经运行程序
    QSharedMemory mem("VM");
    if (!mem.create(1)) {
        QMessageBox::warning(NULL, "警告", "程序已运行,软件将自动关闭!");
        return 1;
    }

    if( !connectDB() )
        return 1;


    contentProvider->flashAllBySQL();

    MainWindow w;
    w.show();
    return a.exec();

    return 0;
}

bool connectDB()
{
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("localhost");
    dataBase.setUserName("root");
    dataBase.setPassword("root");
    dataBase.setDatabaseName("poi");
    dataBase.open();

    if(!dataBase.open())
    {
        QMessageBox::warning(NULL, "错误", dataBase.lastError().text());
        return false;
    }
    return true;
}

