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

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

signals:
};

#endif // LISTDB_H
