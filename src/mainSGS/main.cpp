#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("ToDo List");

    QPalette m_pal;

    m_pal.setColor(QPalette::Active, QPalette::Window, QColor(65, 65, 65));

    w.setPalette(m_pal);
    w.setAutoFillBackground(true);


    w.show();
    return a.exec();
}
