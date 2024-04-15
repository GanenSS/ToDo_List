#include "listdb.h"

listDB::listDB(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase(dbType);
    db.setDatabaseName(dbName);

    bool dbExists = QFile::exists(dbName); // Проверка существования файла базы данных

    if (!db.open()) {
        qWarning() << "Не удалось открыть базу данных";
    }

    if (!dbExists) {
        qDebug() << "База данных не существует. Создание новой базы данных...";

        query = new QSqlQuery(db);
        query->exec(dbTable);

        model = new QSqlTableModel(this, db);
        model->setTable(dbTableName);
        model->select();
    }
    else
    {
        qDebug() << "База данных уже существует. Открытие существующей";

        model = new QSqlTableModel(this, db);
        model->setTable(dbTableName);
        model->select();
    }

}

listDB::~listDB()
{

    delete query;
    delete model;
    db.close();
}

void listDB::addRow()
{
    int row = model->rowCount();
    model->insertRow(row);

    qDebug() << "Добавленная строка " << row;

    // Присвоение значений в столбцы
    QModelIndex index = model->index(row, taskColumn);
    model->setData(index, "Впишите задачу");

    index = model->index(row, dateColumn);
    model->setData(index, "дд.мм.гггг");

    index = model->index(row, progresColumn);
    model->setData(index, "В процессе");

    model->submitAll();
}

void listDB::removeRow(const int rowID)
{
    db.transaction();

    model->removeRow(rowID);
    model->submitAll();
    db.commit();
    model->select();

}

int listDB::getRowIDdb()
{
    int rowID = model->rowCount() - 1;

    qDebug() << "rowId" << rowID;

    return rowID;
}

QString listDB::getData(int rowID, int column)
{
    QModelIndex index = model->index(rowID, column);

    return model->data(index).toString();
}


