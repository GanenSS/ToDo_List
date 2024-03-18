#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "InputDialog.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
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
    void on_m_pcmdAdd_clicked();

    void on_m_cmdRemove_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_m_pcmdAccept_clicked();

    void on_tableView_DataChanged(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlQuery* query;
    QSqlTableModel* model;

    QString text;
    QString txtdescription;

    int rowID;
    int colum;
    int pos;

};


#endif // MAINWINDOW_H
