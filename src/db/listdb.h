#ifndef LISTDB_H
#define LISTDB_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFile>
#include <QDebug>

class listDB : public QObject
{
    Q_OBJECT
public:
    explicit listDB(QObject *parent = nullptr);
    ~listDB();

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
private:
    QString const dbType = "QSQLITE";
    QString const dbName = "./ListDB.db";
    QString const dbTable = "CREATE TABLE task(Задача TEXT, Срок TEXT, Прогресс TXT, Описание TEXT);";
    QString const dbTableName = "task";

    //MainWindow mainWind;

signals:
};

#endif // LISTDB_H
