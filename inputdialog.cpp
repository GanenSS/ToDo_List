#include "InputDialog.h"

InputDialog::InputDialog(QWidget* pwgt/* = 0*/)
    :QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    //Создание виджетов
    m_ptxtDiscription = new QTextEdit;

    QLabel* plblDiscription = new QLabel("Описание");

    plblDiscription->setBuddy(m_ptxtDiscription);

    QPushButton* m_pcmdSave = new QPushButton("Сохранить");
    QPushButton* m_pcmdCancel = new QPushButton("Отмена");

    //Соединение кнопок
    connect(m_pcmdSave, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(m_pcmdCancel, SIGNAL(clicked(bool)), SLOT(accept()));

    //Групировка виджетов
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;
    pvbxLayout->addWidget(plblDiscription);
    pvbxLayout->addWidget(m_ptxtDiscription);

    phbxLayout->addWidget(m_pcmdSave);
    phbxLayout->addWidget(m_pcmdCancel);

    pvbxLayout->addLayout(phbxLayout);
    setLayout(pvbxLayout);
}

//Возвращение строки
QString InputDialog::discription() const
{
    return m_ptxtDiscription->toPlainText();
}

//Очищение строки
void InputDialog::disc0()
{
    m_ptxtDiscription->setText("");
}

//Присвоение строки из бд в m
void InputDialog::txtDataChanged(const QString &str)
{
    m_ptxtDiscription->setText(str);
}
