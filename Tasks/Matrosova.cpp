//#pragma hdrstop
//---------------------------------------------------------------------------
#include "Matrosova.h"
#include "Global.h"

//---------------------------------------------------------------------------
////#pragma package(smart_init)
//---------------------------------------------------------------------------
//Конструктор класса CMatrosova
//Входные переменные:
//int li_Level - уровень иерархии объекта в структуре задачи
//string lc_String - порядковый номер объекта среди объектов одного типа
CMatrosova::CMatrosova(int li_Level, std::wstring lc_String) : CTaskBase(li_Level, lc_String)
{
    bc_Name = r("Матросова");
    bc_TypeName=bc_Name;

    // Сформировать структуру задачи
    int li_ObjectLevel = li_Level+1;
    // Создание объектов
    missile = new CMyMissile (li_Level+1,r("1"),this,this); // Ракета MyMissile

    for (unsigned int i=0; i<gc_IndexList.size(); i++)
    {
        char buffer[80];
        sprintf(buffer, "%d", i+1);
        new CTarget(li_ObjectLevel, r(buffer));
    }

    // Управление режимом видимости окон-закладок
    go_VisibleTrajectory = true;
    go_VisibleMissile = true;
    go_VisibleDNA = true;
    go_VisibleSpectr = false;
    go_VisibleMiss = false;
}
//---------------------------------------------------------------------------
//Деструктор класса
CMatrosova::~CMatrosova()
{
}
//---------------------------------------------------------------------------
void CMatrosova::init_struct()
{
}
//---------------------------------------------------------------------------
void CMatrosova::set_inputs()
{
}
