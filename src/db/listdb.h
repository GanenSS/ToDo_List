#ifndef LISTDB_H
#define LISTDB_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QFile>
#include <QDebug>

class listDB : public QObject
{
    Q_OBJECT
public:
    explicit listDB(QObject *parent = nullptr);
    ~listDB();

    QSqlDatabase    db;
    QSqlQuery       *query;
    QSqlTableModel  *model;

public slots:
    void    addRow();
    void    removeRow(const int rowID);
    int     getRowIDdb();
    QString getData(int rowID, int column);

private:
    const QString dbType        = "QSQLITE";
    const QString dbName        = "./ListDB.db";
    const QString dbTable       = "CREATE TABLE task(Task TEXT, Date TEXT, Progres TEXT, Descriptin TEXT);";
    const QString dbTableName   = "task";

    const int taskColumn        = 0;
    const int dateColumn        = 1;
    const int progresColumn     = 2;
    const int descriptionColumn = 3;

};

#endif // LISTDB_H
