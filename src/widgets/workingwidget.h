#ifndef WORKINGWIDGET_H
#define WORKINGWIDGET_H

#include "styles.h"
#include "InputDialog.h"
#include <QWidget>
#include <QLineEdit>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPainter>
#include <QStyleOption>

QT_BEGIN_NAMESPACE
namespace Ui {
class WorkingWidget;
}
QT_END_NAMESPACE

class WorkingWidget : public QWidget
{
    Q_OBJECT

public:
    WorkingWidget(QWidget *parent = nullptr);
    ~WorkingWidget();

signals:
    void taskChangedSignal(int ID);
    void dateChangedSignal(int ID);

    void clickedCompletedButtonSignal(int ID);
    void clickedNotCompletedButtonSignal(int ID);

    void clickedDescriptionButtonSignal(int ID);

public slots:
    void    setInterfaceStyle();

    int     getRowIDww();
    void    setRowIDww(const int &ID);

    bool    checkChekBox();

    QString getTaskData();
    void    setTaskData(const QString text);

    QString getDateData();
    void    setDateData(const QString text);

    void    clickedCompletedButton();
    void    clickedNotCompletedButton();

    void    setNormalWidgetStyle();

    void    clickedCompletedButtonSlot();
    void    clickedNotCompletedButtonSlot();

    void clickedDescriptionButtonSlot();

    void    taskChangedSlot();
    void    dateChangedSlot();

    void    clickedTaskEdit();
    void    clickedDateEdit();

    void    finishedTaskEdit();
    void    finishedDateEdit();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    void paintEvent(QPaintEvent *event);

private:
    Ui::WorkingWidget *ui;

    int rowID;

    const QString taskEditText = "Впишите задачу";
    const QString dateEditText = "дд.мм.гггг";

};

#endif // WORKINGWIDGET_H
