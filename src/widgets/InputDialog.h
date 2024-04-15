#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <styles.h>


class QTextEdit;

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    InputDialog(QWidget* pwgt = 0);
    ~InputDialog();

public slots:
    QString getDescription();

    void descriptionClear();

    void setDescription(const QString &str);

    void clickedDescriptionEdit();

    void setInterfaceStyle();
private:
    QLabel      *descriptionLable;
    QTextEdit   *descriptionEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontLayout;

    const QString descriptionText = "Напишите описание задачи";

};

#endif // INPUTDIALOG_H
