#include "styles.h"



QString Styles::getNormalWorckingWidgetStyle()
{
    return "QWidget#WorkingWidget {"
           "    background-image: url(:/src/resourses/image/bgWW.png);"
           "    border-radius: 8px;"
           "    padding: 5px;"
           "}";
}

QString Styles::getAcceptStyle()
{
    return "QWidget#WorkingWidget {"
           "    background-image: url(:/src/resourses/image/bgCompleted.png);"
           "    border-radius: 8px;"
           "    padding: 5px;"
           "}";
}

QString Styles::getNotCompletedStyle()
{
    return "QWidget#WorkingWidget {"
           "    background-image: url(:/src/resourses/image/bgNotCompleted.png);"
           "    border-radius: 8px;"
           "    padding: 5px;"
           "}";
}

QString Styles::getLineEditStyle()
{

    return "QLineEdit {"
           "    background-color: #333333;"
           "    border: 2px solid #999999;"
           "    border-radius: 4px;"
           "    font-family: 'Roboto Medium';"
           "    font-size: 12px;"
           "    color: #ffffff;"
           "}"
           "QLineEdit:focus {"
           "    border: 2px solid #0078d7;"
           "}"
           "QLineEdit:disabled {"
           "    background-color: #666666;"
           "    color: #999999;"
           "}";
}

QString Styles::getMainWidgetStyle()
{
    return ".QWidget{"
           "background-image: url(:/src/resourses/image/bg.png);"
           "}";
}

QString Styles::getButtonStyle()
{
    return "QPushButton{"
           "    color: #fff;"
           "    border: none;"
           "    border-radius:15px;"
           "    background: none;"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(89, 156, 208, 255), stop:1 rgba(65, 118, 184, 255));"
           "    font-family: 'Roboto Medium';"
           "    font-size:16px;"
           "}"
           "QPushButton::hover{"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(103, 180, 240, 255), stop:1 rgba(80, 145, 227, 255));"
           "}"
           "QPushButton::pressed{"
           "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(89, 156, 208, 255), stop:1 rgba(65, 118, 184, 255));"
           "}";
}

QString Styles::getDialogButtonStyle()
{
    return "QPushButton{"
           "    color: #fff;"
           "    border: none;"
           "    border-radius:10px;"
           "    background: none;"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(89, 156, 208, 255), stop:1 rgba(65, 118, 184, 255));"
           "    font-family: 'Roboto Medium';"
           "    font-size:16px;"
           "}"
           "QPushButton::hover{"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(103, 180, 240, 255), stop:1 rgba(80, 145, 227, 255));"
           "}"
           "QPushButton::pressed{"
           "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(89, 156, 208, 255), stop:1 rgba(65, 118, 184, 255));"
           "}";
}

QString Styles::getTextEditStyle()
{
    return "QTextEdit {"
           "    background-color: #333333;"
           "    border: 2px solid #999999;"
           "    border-radius: 4px;"
           "    font-family: 'Roboto Medium';"
           "    font-size: 14px;"
           "    color: #ffffff;"
           "}"
           "QLineEdit:focus {"
           "    border: 2px solid #0078d7;"
           "}"
           "QLineEdit:disabled {"
           "    background-color: #666666;"
           "    color: #999999;"
           "}";
}

QString Styles::getDialogWidgetStyle()
{
    return "QDialog {"
           "    background-image: url(:/src/resourses/image/bg.png);"
           "}";
}

QString Styles::getDialogLabelStyle()
{
    return "QLabel {"
           "    font-family: 'Roboto Medium';"
           "    font-size: 14px;"
           "    color: #ffffff;"
           "}";
}

QString Styles::getCompletedButtonStyle()
{
    return "QPushButton{"
           "    border-radius:10px;"
           "    border-image: url(:/src/resourses/image/Yes.png);"
           "}"
           "QPushButton::hover{"
           "    border: 2px;"
           "}"
           "QPushButton::pressed{"
           "    border: 2px;"
           "}";
}

QString Styles::getNotCompletedButtonStyle()
{
    return "QPushButton{"
           "    border-radius:10px;"
           "    border-image: url(:/src/resourses/image/No.png);"
           "}"
           "QPushButton::hover{"
           "    border: 2px;"
           "}"
           "QPushButton::pressed{"
           "    border: 2px;"
           "}";

}

QString Styles::getDescriptionButtonStyle()
{
    return "QPushButton{"
           "    background-color: rgb(255, 255, 255);"
           "    border-radius:10px;"
           "}"
           "QPushButton::hover{"
           "    background-color: rgb(171, 171, 171);"
           "    border: 2px;"
           "}"
           "QPushButton::pressed{"
           "    background-color: rgb(171, 171, 171);"
           "    border: 2px;"
           "}";
}

