#include "listdb.h"


listDB::listDB(QObject *parent)
    : QObject{parent}
{

    if(!QFile::exists(dbName))
    {
        qDebug() << "База данных не существует. Создание новой базы данных...";

        db = QSqlDatabase :: addDatabase(dbType);
        db.setDatabaseName(dbName);

        if(!db.open())
        {
            qWarning() << "Не удалось открыть базу данных";
        }

    }
    else
    {
        qDebug() << "База данных уже существует. Открытие существующей";
        db = QSqlDatabase :: addDatabase(dbType);
        db.setDatabaseName(dbName);

        if(!db.open())
        {
            qWarning() << "Не удалось открыть базу данных";
        }
    }

    //Создание столбцов в бд task
    query = new QSqlQuery(db);
    query->exec(dbTable);

    //Создание табличной модели QSqlTableModel для бд task
    model = new QSqlTableModel(this, db);
    model->setTable(dbTableName);
    model->select();


}
listDB::~listDB()
{
    db.close();
    delete query;
    delete model;
}
