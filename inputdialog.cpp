#include "InputDialog.h"

InputDialog::InputDialog(QWidget* pwgt/* = 0*/)
    :QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    //Создание виджетов
    descriptionEdit = new QTextEdit;

    QLabel* descriptionLable = new QLabel("Описание");

    descriptionLable->setBuddy(descriptionEdit);

    QPushButton* saveButton = new QPushButton("Сохранить");
    QPushButton* cancelButton = new QPushButton("Отмена");

    //Соединение кнопок
    connect(saveButton, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), SLOT(accept()));

    //Групировка виджетов
    QVBoxLayout* verticalLayout = new QVBoxLayout;
    QHBoxLayout* horizontLayout = new QHBoxLayout;
    verticalLayout->addWidget(descriptionLable);
    verticalLayout->addWidget(descriptionEdit);

    horizontLayout->addWidget(saveButton);
    horizontLayout->addWidget(cancelButton);

    verticalLayout->addLayout(horizontLayout);
    setLayout(verticalLayout);
}

//Возвращение строки
QString InputDialog::getDescription() const
{
    return descriptionEdit->toPlainText();
}

//Присвоение строки из бд в descriptionEdit
void InputDialog::setDescription(const QString &str)
{
    descriptionEdit->setText(str);
}

//Очищение строки
void InputDialog::descClear()
{
    descriptionEdit->setText("");
}

