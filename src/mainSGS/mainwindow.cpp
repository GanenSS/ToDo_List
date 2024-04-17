#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
    verticalLayout->addSpacerItem(spacer);
    verticalLayout->setSpacing(10);
    verticalLayout->setContentsMargins(43, 10, 15, 10);

    //Соеденения
    connect(ui->addButton, &QPushButton::clicked,      this, &MainWindow::clickedAddButton);
    connect(ui->removeButton, &QPushButton::clicked,   this, &MainWindow::clickedRemoveButon);

    starting();
    setInterfaceStyle();

    QFontDatabase::addApplicationFont(":/src/resourses/fonts/Roboto-Medium.ttf");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete verticalLayout;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void MainWindow::setInterfaceStyle()
{
    ui->addButton->setStyleSheet(Styles::getButtonStyle());
    ui->removeButton->setStyleSheet(Styles::getButtonStyle());
    this->setStyleSheet(Styles::getMainWidgetStyle());
}

void MainWindow::clickedAddButton()
{
    QModelIndex index = dataBase->model->index(dataBase->model->rowCount()-1, taskColumn);

    if(dataBase->model->data(index) != defaultTaskMsg)
    {
        addWorkingWidget(addRowInDataBase());
    }
    else
    {
        QMessageBox::information(this, "Information", errorRowMsg);
    }
}

//Удаление строки
void MainWindow::clickedRemoveButon()
{
    for (int i = widgetList.size() - 1; i >= 0; --i)
    {
        if(widgetList[i]->checkChekBox())
        {
            rowID = widgetList[i]->getRowIDww();
            dataBase->removeRow(rowID);
            delete widgetList[i];
            widgetList.remove(i);
            updateIndex(rowID);
        }
    }
}

void MainWindow::clickedCompletedButton(const int id)
{
    QModelIndex index = dataBase->model->index(id, progresColumn);

    if(dataBase->model->data(index) == progresNormalText | dataBase->model->data(index) == progresNotCompletedText)
    {
        dataBase->model->setData(index, progresCompletedText);
    }
    else if(dataBase->model->data(index) == progresCompletedText)
    {
        dataBase->model->setData(index, progresNormalText);
        widgetList[id]->setNormalWidgetStyle();
    }

    dataBase->model->submitAll();
}

void MainWindow::clickedNotCompletedButton(const int id)
{
    QModelIndex index = dataBase->model->index(id, progresColumn);

    if(dataBase->model->data(index) == progresNormalText | dataBase->model->data(index) == progresCompletedText)
    {
        dataBase->model->setData(index, progresNotCompletedText);
    }
    else if(dataBase->model->data(index) == progresNotCompletedText)
    {
        dataBase->model->setData(index, progresNormalText);
        widgetList[id]->setNormalWidgetStyle();
    }

    dataBase->model->submitAll();
}

void MainWindow::updateIndex(const int startIndex)
{
    for (int i = startIndex; i < widgetList.size(); ++i)
    {
        widgetList[i]->setRowIDww(i);
    }
}

void MainWindow::taskChenged(const int id)
{
    validateData(id, widgetList[id]->getTaskData());

    QModelIndex index = dataBase->model->index(id, taskColumn);
    dataBase->model->setData(index, widgetList[id]->getTaskData());

    dataBase->model->submitAll();
}

void MainWindow::dateChenged(const int id)
{
    validateData(id, widgetList[id]->getDateData());

    QModelIndex index = dataBase->model->index(id, dateColumn);
    dataBase->model->setData(index, widgetList[id]->getDateData());

    dataBase->model->submitAll();
}

void MainWindow::addWorkingWidget(int id)
{
    verticalLayout->removeItem(spacer);

    rowID = id;

    workingWidget = new WorkingWidget(this);
    workingWidget->setRowIDww(rowID);

    workingWidget->setTaskData(dataBase->getData(rowID, taskColumn));
    workingWidget->setDateData(dataBase->getData(rowID, dateColumn));

    widgetList.push_back(workingWidget);

    verticalLayout->addWidget(workingWidget);
    verticalLayout->addSpacerItem(spacer);
    verticalLayout->update();

    dataBase->model->submitAll();

    connect(workingWidget, &WorkingWidget::clickedCompletedButtonSignal,    this, &MainWindow::clickedCompletedButton);
    connect(workingWidget, &WorkingWidget::clickedNotCompletedButtonSignal, this, &MainWindow::clickedNotCompletedButton);
    connect(workingWidget, &WorkingWidget::taskChangedSignal,               this, &MainWindow::taskChenged);
    connect(workingWidget, &WorkingWidget::dateChangedSignal,               this, &MainWindow::dateChenged);
    connect(workingWidget, &WorkingWidget::clickedDescriptionButtonSignal,  this, &MainWindow::descriptionDialog);

    if(dataBase->model->rowCount()-1 == 8)
    {
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
}

int MainWindow::addRowInDataBase()
{
    dataBase->addRow();
    return rowID = dataBase->getRowIDdb();
}

void MainWindow::starting()
{
    QModelIndex index;

    if(dataBase->model->rowCount() > 0)
    {
        for (int i = 0; i < dataBase->model->rowCount(); ++i)
        {
            addWorkingWidget(i);

            index = dataBase->model->index(i, progresColumn);
            if(dataBase->model->data(index) == progresCompletedText)
            {
                widgetList[i]->clickedCompletedButton();
            }
            else if(dataBase->model->data(index) == progresNotCompletedText)
            {
                widgetList[i]->clickedNotCompletedButton();
            }
        }
    }
}

void MainWindow::validateData(int rowID, QString text)
{
    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    static QRegularExpression regLanguage("^[А-Яа-я0-9\\s,.-]*$");

    if (widgetList[rowID]->getTaskData() != defaultTaskMsg && !regLanguage.match(text).hasMatch())
    {
        widgetList[rowID]->setTaskData(defaultTaskMsg);
        QMessageBox::information(this, "Information", errorLanguageMsg);
    }else if (widgetList[rowID]->getDateData() != defaultDateMsg && !regLanguage.match(text).hasMatch())
    {
        widgetList[rowID]->setDateData(defaultDateMsg);
        QMessageBox::information(this, "Information", errorDateMsg);
    }

}

void MainWindow::descriptionDialog(const int id)
{
    InputDialog* pInputDialog = new InputDialog;
    QModelIndex index = dataBase->model->index(id, descriptionColumn);

    //Присвоение "Описание" из бд в TextEdit в диалоговом окне
    pInputDialog->setDescription(dataBase->model->data(index).toString());

    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    static QRegularExpression regLanguage("^[А-Яа-я0-9\\s,.-]*$");

    int result = pInputDialog->exec();

    //Если нажали кнопку saveButton(Сохранить)
    if(result == QDialog::Accepted)
    {
        QString text = pInputDialog->getDescription();
        // Проверяем, что текст содержит только русские символы, цифры или пустоту
        if(!regLanguage.match(text).hasMatch()) {
            // Очищаем ячейку, если текст не соответствует формату
            pInputDialog->descriptionClear();
            //Сообщение о причине очищения строки
            QMessageBox::information(this, "Information", errorLanguageMsg);
            // Опционально: очищаем текст переменной text
            text = "";
        }
        else
        {
            //Присвоение написанного текста в бд
            dataBase->model->setData(index, text);
            dataBase->model->submitAll();

            delete pInputDialog;
        }
    }

    //Если нажали кнопку m_pcmdCansel(Отмена)
    if(result == QDialog::Rejected)
    {
        delete pInputDialog;
    }
}
