

#include <QApplication>
#include "CreateTask.h"
#include "Target.h"
//#include "executeControl.h"
#include "Global.h"


//---------------------------------------------------------------------------------------------------------

#ifdef USEGUI

#include "mainwindow.h"

extern MainWindow * fm_window;

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
    gc_AppPath = AppPath.toStdWString();
//#endif
    //QMessageBox::warning(fm_window, QString("FilePath"), QString("File ") + AppPath);
    fm_window = new MainWindow((AppPath), CreateTask, CreateTarget, DestroyTarget, gac_Task_Array, gac_Target_Array);
    fm_window->setAttribute(Qt::WA_DeleteOnClose);
    fm_window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, fm_window->size(),
        QApplication::desktop()->availableGeometry()));
    fm_window->show();
    fm_window->loadLast();
    int result = qapp.exec();
    return result;
}

#else
#define DEBUG_INFO
int auto_run(QString fileName);     //запуск на счет
int main(int argc, char *argv[])
{

    QApplication capp(argc, argv);
    setlocale(LC_ALL,"ru_RU.UTF-8");
    setlocale(LC_NUMERIC,"C");

#ifdef DEBUG_INFO
    cout<<"Please enter arguments separated by spaces"<<endl;

    std::cout<<"argc = "<<argc<<"\n";

    for (int i = 0; i<argc; i++)
    {
        std::cout<<"argv["<<i<<"] = "<<argv[i]<<"\n";
    }
#endif
    if (argc < 2)
    {
        control.write_error(ERROR_COUNT_ARG);
        return ERROR_COUNT_ARG;
    }
    QString fileName = argv[1];
    //CurFile = fileName;

    if(argc >= 3)
    {
        QString flag1 = argv[2];
        int flag = flag1.toInt();

        if(flag==1)
            control.nominal = true;
    }

    QString AppPath = QApplication::applicationDirPath();
    AppPath += "/";
    gc_AppPath = AppPath.toStdWString();
    AppPath.truncate(AppPath.lastIndexOf('/')+1);
#ifdef Q_OS_WIN
    AppPath.truncate(AppPath.lastIndexOf('/'));
    AppPath.truncate(AppPath.lastIndexOf('/')+1);
#endif
    //AppPath += rq("../");


    //  Запуск на счет

    return auto_run(fileName);

    return 0;
}

int auto_run(QString fileName)
{
    int result = 0;
    control.setCreateTask(CreateTask);//Даем классу указатели на функции создания задачи и цели
    control.setCreateTarget(CreateTarget);
    //  Загрузка варианта из файла
    if (control.LoadFromFile(fileName))
    {
        control.write_error(ERROR_READ_FILE);
        return ERROR_READ_FILE;
    }
    control.ReadGrafSettingsFromFile(fileName);
#ifdef DEBUG_INFO
    cout<<"Calculating starts"<<endl;
#endif
    //  Cчет
    if(control.nominal)
    {
        ChuLib::zero_urand = true; //сбросить счетчики случайных чисел;
    }
    result = control.on_actionRun_triggered();

#ifdef DEBUG_INFO
    cout<<"Calculating finished. Saving to xml-file"<<endl;
#endif
    //  Запись результата в xml-файл
    if (!control.WriteXml(fileName, 0))
    {
        control.write_error(ERROR_SAVE_FILE);
        return ERROR_SAVE_FILE;
    }

    if(!control.Closed)
    {
        control.CloseVariant();  //закрыть вариант
#ifdef DEBUG_INFO
        cout<<"Closing Variant"<<endl;
#endif
    }
    return result;
}
#endif
