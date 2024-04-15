#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setLayout(verticalLayout);
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
    QModelIndex index = db->model->index(db->model->rowCount()-1, taskColumn);

    if(db->model->rowCount()-1 <= 7)
    {
        if(db->model->data(index) != defaultTaskMsg)
        {
            verticalLayout->removeItem(spacer);

            db->addRow();
            rowID = db->getRowIDdb();

            WW = new WorkingWidget(this);
            WW->setRowIDww(rowID);

            WW->setTaskData(db->getData(rowID, taskColumn));
            WW->setDateData(db->getData(rowID, dateColumn));

            widgetList.push_back(WW);

            verticalLayout->addWidget(WW);
            verticalLayout->addSpacerItem(spacer);
            verticalLayout->update();

            db->model->submitAll();

            connect(WW, &WorkingWidget::clickedCompletedButtonSignal,    this, &MainWindow::clickedCompletedButton);
            connect(WW, &WorkingWidget::clickedNotCompletedButtonSignal, this, &MainWindow::clickedNotCompletedButton);
            connect(WW, &WorkingWidget::taskChangedSignal,               this, &MainWindow::taskChenged);
            connect(WW, &WorkingWidget::dateChangedSignal,               this, &MainWindow::dateChenged);
            connect(WW, &WorkingWidget::clickedDescriptionButtonSignal,  this, &MainWindow::descriptionDialog);
        }
        else
        {
            QMessageBox::information(this, "Information", errorRowMsg);
        }
    }
    else
    {
        QMessageBox::information(this, "Information", "Вам пока задач хватит");
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
            db->removeRow(rowID);
            delete widgetList[i];
            widgetList.remove(i);
            updateIndex(rowID);
        }
    }
}

void MainWindow::clickedCompletedButton(const int id)
{
    QModelIndex index = db->model->index(id, progresColumn);

    if(db->model->data(index) == progresNormalText | db->model->data(index) == progresNotCompletedText)
    {
        db->model->setData(index, progresCompletedText);
    }
    else if(db->model->data(index) == progresCompletedText)
    {
        db->model->setData(index, progresNormalText);
        widgetList[id]->setNormalWidgetStyle();
    }

    db->model->submitAll();
}

void MainWindow::clickedNotCompletedButton(const int id)
{
    QModelIndex index = db->model->index(id, progresColumn);

    if(db->model->data(index) == progresNormalText | db->model->data(index) == progresCompletedText)
    {
        db->model->setData(index, progresNotCompletedText);
    }
    else if(db->model->data(index) == progresNotCompletedText)
    {
        db->model->setData(index, progresNormalText);
        widgetList[id]->setNormalWidgetStyle();
    }

    db->model->submitAll();
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

    QModelIndex index = db->model->index(id, taskColumn);
    db->model->setData(index, widgetList[id]->getTaskData());

    db->model->submitAll();
}

void MainWindow::dateChenged(const int id)
{
    validateData(id, widgetList[id]->getDateData());

    QModelIndex index = db->model->index(id, dateColumn);
    db->model->setData(index, widgetList[id]->getDateData());

    db->model->submitAll();
}

void MainWindow::starting()
{
    QModelIndex index;

    if(db->model->rowCount() > 0)
    {
        for (int i = 0; i < db->model->rowCount(); ++i)
        {
            verticalLayout->removeItem(spacer);

            WW = new WorkingWidget;
            WW->setInterfaceStyle();
            WW->setRowIDww(i);
            widgetList.push_back(WW);

            WW->setTaskData(db->getData(i, taskColumn));
            WW->setDateData(db->getData(i, dateColumn));

            verticalLayout->addWidget(WW);
            verticalLayout->addSpacerItem(spacer);
            verticalLayout->update();

            connect(WW, &WorkingWidget::clickedCompletedButtonSignal,    this, &MainWindow::clickedCompletedButton);
            connect(WW, &WorkingWidget::clickedNotCompletedButtonSignal, this, &MainWindow::clickedNotCompletedButton);
            connect(WW, &WorkingWidget::taskChangedSignal,               this, &MainWindow::taskChenged);
            connect(WW, &WorkingWidget::dateChangedSignal,               this, &MainWindow::dateChenged);
            connect(WW, &WorkingWidget::clickedDescriptionButtonSignal,  this, &MainWindow::descriptionDialog);

            index = db->model->index(i, progresColumn);
            if(db->model->data(index) == progresCompletedText)
            {
                widgetList[i]->clickedCompletedButton();
            }
            else if(db->model->data(index) == progresNotCompletedText)
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
    QModelIndex index = db->model->index(id, descriptionColumn);

    //Присвоение "Описание" из бд в TextEdit в диалоговом окне
    pInputDialog->setDescription(db->model->data(index).toString());

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
            db->model->setData(index, text);
            db->model->submitAll();

            delete pInputDialog;
        }
    }

    //Если нажали кнопку m_pcmdCansel(Отмена)
    if(result == QDialog::Rejected)
    {
        delete pInputDialog;
    }
}
