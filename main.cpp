#include "mainwindow.h"
#include "about.h"
#include "plotter.h"
// #include <QTranslator>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <exception>
#include "CreateTask.h"
#include "Target.h"

extern MainWindow * fm_window;
// bool statistic = 0;

int main(int argc, char *argv[])
{
    QString AppPath;
    gi_Language = 0;
    QApplication qapp(argc, argv);
    setlocale(LC_NUMERIC,"C");
    AppPath = QApplication::applicationDirPath();
//#ifndef __unix__
//    AppPath.truncate(AppPath.lastIndexOf('/')+1);
//#else
    AppPath += "/";
//#endif
    //QMessageBox::warning(fm_window, QString("FilePath"), QString("File ") + AppPath);
    fm_window = new MainWindow((AppPath), CreateTask, CreateTarget, DestroyTarget, gac_Task_Array, gac_Target_Array);
    fm_window->setAttribute(Qt::WA_DeleteOnClose);
    fm_window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, fm_window->size(),
        QApplication::desktop()->availableGeometry()));
    fm_window->show();
    fm_window->loadLast();
    int rezult = qapp.exec();
    return rezult;
}
