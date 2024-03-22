#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Присвоение tableView модели
    ui->tableView->setModel(db.model);

    ui->tableView->hideColumn(3);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    //Соеденения
    connect(ui->addButton, &QPushButton::clicked,      this, &MainWindow::clickedAddButton);
    connect(ui->removeButton, &QPushButton::clicked,   this, &MainWindow::clickedRemoveButon);
    connect(ui->acceptButton, &QPushButton::clicked,   this, &MainWindow::clickedAcceptButton);
    connect(ui->tableView, &QTableView::clicked,       this, &MainWindow::clickedTable);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::doubleClickedTable);
    connect(db.model, &QSqlTableModel::dataChanged,    this, &MainWindow::tableDataChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedAddButton()
{
    //Добовление строки
    int row = db.model->rowCount();
    db.model->insertRow(row);

    //Присвоение в столбцы текста
    QModelIndex index = db.model->index(row, taskColumn);
    db.model->setData(index, "Впишите задачу");

    index = db.model->index(row, progresColumn);
    db.model->setData(index, "В процессе");

    index = db.model->index(row, descriptionColumn);
    db.model->setData(index, "Напишите описание задачи");

    db.model->submitAll();
}

//Удаление строки
void MainWindow::clickedRemoveButon()
{
    db.model->removeRow(rowID);
}

void MainWindow::clickedAcceptButton()
{
    QModelIndex index = db.model->index(rowID, progresColumn); // Индекс поля Прогресс
    db.model->setData(index, "ВЫПОЛНЕНО"); // Устанавливаем значение ВЫПОЛНЕНО
    db.model->submitAll();
}

void MainWindow::clickedTable(const QModelIndex &index)
{
    //Получаем номер строки и колонки
    rowID = index.row();
}

void MainWindow::tableDataChanged(const QModelIndex &index)
{
    text = db.model->data(index).toString(); // Получаем текст из ячейки

    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    static QRegularExpression regLanguage("^[А-Яа-я0-9\\s]*$");
    static QRegularExpression regDate("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{4}$");

    if (index.column() == taskColumn && !regLanguage.match(text).hasMatch())
    {
        db.model->setData(index, QVariant(defaultMsg)); // Очищаем ячейку, если текст не на русском
        QMessageBox::information(this, "Information", errorLanguageMsg);
    }
    else if (index.column() == dateColumn && !regDate.match(text).hasMatch())
    {
        db.model->setData(index, QVariant("")); // Очищаем ячейку, если дата не соответствует формату
        QMessageBox::information(this, "Information", errorDateMsg);
    }
}

void MainWindow::doubleClickedTable(const QModelIndex &index)
{
    InputDialog* pInputDialog = new InputDialog;

    //Присвоение "Описание" из бд в TextEdit в диалоговом окне
    pInputDialog->setDescription(db.model->data(db.model->index(rowID, descriptionColumn)).toString());

    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    static QRegularExpression regLanguage("^[А-Яа-я0-9\\s]*$");

    int result = pInputDialog->exec();

    //Если нажали кнопку saveButton(Сохранить)
    if(result == QDialog::Accepted)
    {
        text = pInputDialog->getDescription();
        // Проверяем, что текст содержит только русские символы, цифры или пустоту
        if(!regLanguage.match(text).hasMatch()) {
            pInputDialog->descClear(); // Очищаем ячейку, если текст не соответствует формату
            //Сообщение о причине очищения строки
            QMessageBox::information(this, "Information", "Текст должен быть на русском языке");
            text = ""; // Опционально: очищаем текст переменной text
        }
        else
        {
            //Присвоение написанного текста в бд
            db.model->setData(db.model->index(rowID, descriptionColumn), text);
            db.model->submitAll();

            delete pInputDialog;
        }
    }

    //Если нажали кнопку m_pcmdCansel(Отмена)
    if(result == QDialog::Rejected)
    {
        delete pInputDialog;
    }
}



