#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>

class QTextEdit;

class InputDialog : public QDialog
{
    Q_OBJECT
private:
    QTextEdit* m_ptxtDiscription;

public:
    InputDialog(QWidget* pwgt = 0);

    QString discription() const;

    void disc0();

    void txtDataChanged(const QString &str);

};

#endif // INPUTDIALOG_H
