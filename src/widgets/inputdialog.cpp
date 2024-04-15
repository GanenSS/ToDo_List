#include "InputDialog.h"

InputDialog::InputDialog(QWidget* pwgt)
    :QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    descriptionEdit = new QTextEdit;

    descriptionLable = new QLabel("Описание вашей задачи");

    descriptionLable->setBuddy(descriptionEdit);

    saveButton = new QPushButton("Сохранить");
    cancelButton = new QPushButton("Отмена");

    //Соединение кнопок
    connect(saveButton, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), SLOT(accept()));

    //Групировка виджетов
    verticalLayout = new QVBoxLayout;
    horizontLayout = new QHBoxLayout;

    verticalLayout->addWidget(descriptionLable);
    verticalLayout->addWidget(descriptionEdit);

    horizontLayout->addWidget(saveButton);
    horizontLayout->addWidget(cancelButton);

    verticalLayout->addLayout(horizontLayout);
    setLayout(verticalLayout);

    setInterfaceStyle();

    this->setMaximumSize(220, 250);
    saveButton->setMinimumWidth(100);
    saveButton->setMaximumWidth(100);
    saveButton->setMinimumHeight(20);
    saveButton->setMaximumHeight(20);

    cancelButton->setMinimumWidth(100);
    cancelButton->setMaximumWidth(100);
    cancelButton->setMinimumHeight(20);
    cancelButton->setMaximumHeight(20);
}

InputDialog::~InputDialog()
{
    delete verticalLayout;
}

//Возвращение строки
QString InputDialog::getDescription()
{
    return descriptionEdit->toPlainText();
}

//Присвоение строки из бд в descriptionEdit
void InputDialog::setDescription(const QString &str)
{
    descriptionEdit->setText(str);
}

void InputDialog::clickedDescriptionEdit()
{
    if(descriptionEdit->toPlainText() == descriptionText)
    {
        descriptionEdit->setText("");
    }
}

void InputDialog::setInterfaceStyle()
{

    this->setStyleSheet(Styles::getDialogWidgetStyle());
    descriptionEdit->setStyleSheet(Styles::getTextEditStyle());
    saveButton->setStyleSheet(Styles::getDialogButtonStyle());
    cancelButton->setStyleSheet(Styles::getDialogButtonStyle());
    descriptionLable->setStyleSheet(Styles::getDialogLabelStyle());
}

//Очищение строки
void InputDialog::descriptionClear()
{
    descriptionEdit->setText("");
}
