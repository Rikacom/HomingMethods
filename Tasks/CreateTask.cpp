#include "CreateTask.h"
#include "Global.h"


#include "Task_Include.hpp"


using namespace GLOBAL;

void CreateTask(int li_TaskIndex)
{
    ZeroFillStructs();
    if (gpc_Task) {
        delete gpc_Task;
        gpc_Task = 0;
    }
    int ind=0;

#include "Task_New.hpp"

    //To Insert new Task initiate before this comment ******************************
    if (gpc_Task)
    {
        for (unsigned int i=0; i<CDialogObject::bc__DialogObjectList.size();++i)
        {
            CDialogObject& dial = *CDialogObject::bc__DialogObjectList[i];
            std::wstring lc_ClassName = dial.bc_Name;
            CDialogObject::bc__DialogObjectList[i]->init_string(lc_ClassName);
            CDialogObject::bc__DialogObjectList[i]->edit();
            CDialogObject::bc__DialogObjectList[i]->graf();
            CDialogObject::bc__DialogObjectList[i]->init_struct();
        }
        //Установить адреса входных переменных для модуля
        CDialogObject::bc__DialogObjectList[0]->set_inputs();
    }
}

//Список наименований задач
QString gac_Task_Array[100] =
{
    #include "Task_List.hpp"
    rq("Конец списка задач")
};
