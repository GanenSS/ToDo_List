#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "InputDialog.h"
#include "listdb.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMouseEvent>





QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clickedAddButton();
    void clickedRemoveButon();
    void clickedTable(const QModelIndex &index);
    void clickedAcceptButton();
    void tableDataChanged(const QModelIndex &index);
    void doubleClickedTable(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    listDB db;

    QString text;

    const QString errorLanguageMsg = "Текст должен быть на русском языке";
    const QString errorDateMsg = "Дата должна быть формата: дд.мм.гггг";
    const QString defaultMsg = "Впишите задачу";

    int const taskColumn        = 0;
    int const dateColumn        = 1;
    int const progresColumn     = 2;
    int const descriptionColumn = 3;

    int rowID;
};


#endif // MAINWINDOW_H
