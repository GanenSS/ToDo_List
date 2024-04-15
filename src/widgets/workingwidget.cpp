#include "workingwidget.h"
#include "ui_workingwidget.h"

WorkingWidget::WorkingWidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::WorkingWidget)
{
    ui->setupUi(this);

    connect(ui->taskEdit,           &QLineEdit::textChanged, this, &WorkingWidget::taskChangedSlot);
    connect(ui->dateEdit,           &QLineEdit::textChanged, this, &WorkingWidget::dateChangedSlot);

    connect(ui->completedButton,    &QPushButton::clicked,   this, &WorkingWidget::clickedCompletedButton);
    connect(ui->completedButton,    &QPushButton::clicked,   this, &WorkingWidget::clickedCompletedButtonSlot);
    connect(ui->notCompletedButton, &QPushButton::clicked,   this, &WorkingWidget::clickedNotCompletedButton);
    connect(ui->notCompletedButton, &QPushButton::clicked,   this, &WorkingWidget::clickedNotCompletedButtonSlot);

    connect(ui->descriptinButton,   &QPushButton::clicked,   this, &WorkingWidget::clickedDescriptionButtonSlot);

    connect(ui->taskEdit, &QLineEdit::editingFinished,       this, &WorkingWidget::finishedTaskEdit);
    connect(ui->dateEdit, &QLineEdit::editingFinished,       this, &WorkingWidget::finishedDateEdit);


    ui->taskEdit->installEventFilter(this);
    ui->dateEdit->installEventFilter(this);

    setInterfaceStyle();

}

WorkingWidget::~WorkingWidget()
{
    delete ui;
}

void WorkingWidget::setInterfaceStyle()
{
    this->setStyleSheet(Styles::getNormalWorckingWidgetStyle());
    this->update();
    ui->dateEdit->setStyleSheet(Styles::getLineEditStyle());
    ui->dateEdit->update();
    ui->taskEdit->setStyleSheet(Styles::getLineEditStyle());
    ui->taskEdit->update();
    ui->completedButton->setStyleSheet(Styles::getCompletedButtonStyle());
    ui->completedButton->update();
    ui->notCompletedButton->setStyleSheet(Styles::getNotCompletedButtonStyle());
    ui->notCompletedButton->update();
    ui->descriptinButton->setStyleSheet(Styles::getDescriptionButtonStyle());
    ui->descriptinButton->update();

    QWidget::repaint();
}
//-------------------------------------------------
int WorkingWidget::getRowIDww()
{
    return rowID;
}
void WorkingWidget::setRowIDww(const int &ID)
{
    rowID = ID;
}
//-------------------------------------------------
bool WorkingWidget::checkChekBox()
{
    if (ui->deleteCheckBox) {
        return ui->deleteCheckBox->isChecked();
    }
    return false;
}
//-------------------------------------------------
QString WorkingWidget::getTaskData()
{
    return ui->taskEdit->text();
}

void WorkingWidget::setTaskData(const QString text)
{
    ui->taskEdit->setText(text);
}
//-------------------------------------------------
QString WorkingWidget::getDateData()
{
    return ui->dateEdit->text();
}

void WorkingWidget::setDateData(const QString text)
{
    ui->dateEdit->setText(text);
}
//-------------------------------------------------
void WorkingWidget::clickedCompletedButton()
{
    this->setStyleSheet(Styles::getAcceptStyle());
    this->update();
}

void WorkingWidget::clickedNotCompletedButton()
{
    this->setStyleSheet(Styles::getNotCompletedStyle());
    this->update();
}

void WorkingWidget::setNormalWidgetStyle()
{
    this->setStyleSheet(Styles::getNormalWorckingWidgetStyle());
    this->update();
}
//-------------------------------------------------
void WorkingWidget::clickedCompletedButtonSlot()
{
    emit clickedCompletedButtonSignal(rowID);
}

void WorkingWidget::clickedNotCompletedButtonSlot()
{
    emit clickedNotCompletedButtonSignal(rowID);
}

void WorkingWidget::clickedDescriptionButtonSlot()
{
    emit clickedDescriptionButtonSignal(rowID);
}
//-------------------------------------------------
void WorkingWidget::taskChangedSlot()
{
    emit taskChangedSignal(rowID);
}

void WorkingWidget::dateChangedSlot()
{
    emit dateChangedSignal(rowID);
}

void WorkingWidget::clickedTaskEdit()
{
    if(ui->taskEdit->text() == taskEditText)
    {
        ui->taskEdit->setText("");
    }
}

void WorkingWidget::clickedDateEdit()
{
    if(ui->dateEdit->text() == dateEditText)
    {
        ui->dateEdit->setText("");
    }
}

void WorkingWidget::finishedTaskEdit()
{
    if(ui->taskEdit->text() == "")
    {
        ui->taskEdit->setText(taskEditText);
    }
}

void WorkingWidget::finishedDateEdit()
{
    if(ui->dateEdit->text() == "")
    {
        ui->dateEdit->setText(dateEditText);
    }
}


bool WorkingWidget::eventFilter(QObject *obj, QEvent *event)
{
    if ( event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            if(obj == ui->taskEdit)
            {
                clickedTaskEdit();
            }
            else if(obj == ui->dateEdit)
            {
                clickedDateEdit();
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void WorkingWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}
