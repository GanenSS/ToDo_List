#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>

class QTextEdit;

class InputDialog : public QDialog
{
    Q_OBJECT
private:
    QTextEdit* descriptionEdit;

public:
    InputDialog(QWidget* pwgt = 0);

    QString getDescription() const;

    void descClear();

    void setDescription(const QString &str);

};

#endif // INPUTDIALOG_H
