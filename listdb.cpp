#include "listdb.h"

QString const dbType = "QSQLITE";
QString const dbName = "./ListDB.db";
QString const dbTable = "CREATE TABLE task(Задача TEXT, Срок TEXT, Прогресс TXT, Описание TEXT);";
QString const dbTableName = "task";

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
        qDebug() << "База данных уже существует. Открыте существующей";
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
