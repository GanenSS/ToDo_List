#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "listdb.h"
#include "workingwidget.h"
#include "styles.h"
#include <QMainWindow>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPainter>
#include <QStyleOption>

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

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void setInterfaceStyle();
    void clickedAddButton();
    void clickedRemoveButon();

    void clickedCompletedButton(const int id);
    void clickedNotCompletedButton(const int id);

    void updateIndex(const int startIndex);

    void taskChenged(const int id);
    void dateChenged(const int id);

    void addWorkingWidget(int id);
    int  addRowInDataBase();
    void starting();
    void validateData(int rowID, QString text);
    void descriptionDialog(const int id);

private:
    Ui::MainWindow *ui;

    listDB *dataBase = new listDB;
    WorkingWidget *workingWidget;

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QSpacerItem* spacer         = new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);

    const QString errorRowMsg             = "Впишите вашу задачу";
    const QString errorLanguageMsg        = "Текст должен быть на русском языке";
    const QString errorDateMsg            = "Дата должна быть формата: дд.мм.гггг";
    const QString defaultTaskMsg          = "Впишите задачу";
    const QString defaultDateMsg          = "дд.мм.гггг";

    const QString progresCompletedText    = "ВЫПОЛНЕНО";
    const QString progresNotCompletedText = "НЕ ВЫПОЛНЕНО";
    const QString progresNormalText       = "В процессе";

    int const taskColumn        = 0;
    int const dateColumn        = 1;
    int const progresColumn     = 2;
    int const descriptionColumn = 3;

    int rowID;

    QVector<WorkingWidget*> widgetList;

};


#endif // MAINWINDOW_H
