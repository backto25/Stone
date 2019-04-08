#include "mainwindow.h"
#include <QApplication>

bool connectDB();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if( connectDB() )
    {
        contentProvider->flashAllBySQL();
        MainWindow w;
        w.show();


        return a.exec();
    }
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

