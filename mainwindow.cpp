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

    //Соеденение для валидации строк в бд task
    connect(db.model, &QSqlTableModel::dataChanged, this, &MainWindow::on_tableView_DataChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_pcmdAdd_clicked()
{
    //Добовление строки
    int row = db.model->rowCount();
    db.model->insertRow(row);

    //Присвоение в столбцы текста
    QModelIndex index = db.model->index(row, 2);
    db.model->setData(index, "В процессе");
    index = db.model->index(row, 0);
    db.model->setData(index, "Впишите задачу");
    index = db.model->index(row, 3);
    db.model->setData(index, "Напишите описание задачи");
    db.model->submitAll();
}

//Удаление строки
void MainWindow::on_m_cmdRemove_clicked()
{
    db.model->removeRow(rowID);
}

void MainWindow::on_m_pcmdAccept_clicked()
{
    int row = ui->tableView->currentIndex().row(); // Получаем индекс текущей строки
    QModelIndex index = db.model->index(row, 2); // Индекс поля Прогресс
    db.model->setData(index, "ВЫПОЛНЕНО"); // Устанавливаем значение ВЫПОЛНЕНО
    db.model->submitAll();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //Получаем номер строки и колонки
    rowID = index.row();
    colum = index.column();
}

void MainWindow::on_tableView_DataChanged(const QModelIndex &index)
{
    QString text = db.model->data(index).toString(); // Получаем текст из ячейки

    int pos = 0;

    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    QRegularExpression regLanguage("^[А-Яа-я0-9\\s]*$");
    const QRegularExpressionValidator validator(regLanguage);
    if (index.column() == 0 && validator.validate(text, pos) != QValidator::Acceptable)
    {
        db.model->setData(index, QVariant("Впишите задачу")); // Очищаем ячейку, если текст не на русском
        //Сообщение о причине очищения строки
        QMessageBox::information(0,
                                 "Information",
                                 "Текст должен быть на русском языке");
    }

    // Проверяем, что дата имеет формат дд.мм.гггг
    QRegularExpression regDate("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
    const QRegularExpressionValidator dateValidator(regDate);
    if (index.column() == 1 && dateValidator.validate(text, pos) == QValidator::Invalid)
    {
        db.model->setData(index, QVariant("")); // Очищаем ячейку, если дата не соответствует формату
        //Сообщение о причине очищения строки
        QMessageBox::information(0,
                                 "Information",
                                 "Дата должна быть формата: дд.мм.гггг");

    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    InputDialog* pInputDialog = new InputDialog;

    //Присвоение "Описание" из бд в TextEdit в диалоговом окне
    pInputDialog->txtDataChanged(db.model->data(db.model->index(rowID, 3)).toString());

    // Проверяем, что текст содержит только русские символы, цифры или пустоту
    QRegularExpression regLanguage("^[А-Яа-я0-9\\s]*$");
    const QRegularExpressionValidator validator(regLanguage);

    int pos = 0;

    //Если нажали кнопку m_pcmdSave(Сохранить)
    if(pInputDialog->exec() == QDialog::Accepted)
    {
        txtdescription = pInputDialog->discription();
        // Проверяем, что текст содержит только русские символы, цифры или пустоту
        if(validator.validate(txtdescription, pos) != QValidator::Acceptable)
        {
            pInputDialog->disc0();// Очищаем ячейку, если текст не подходит по формату
            //Сообщение о причине очищения строки
            QMessageBox::information(0,
                                     "Information",
                                     "Текст должен быть на русском языке");

            txtdescription = "";
        }
        else
        {
            //Присвоение написанного текста в бд
            txtdescription = pInputDialog->discription();
            db.model->setData(db.model->index(rowID, 3), txtdescription);

            delete pInputDialog;
        }
    }

    //Если нажали кнопку m_pcmdCansel(Отмена)
    if(pInputDialog->exec() == QDialog::Rejected)
    {
        delete pInputDialog;
    }
}
