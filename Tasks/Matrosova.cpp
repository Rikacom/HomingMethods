//---------------------------------------------------------------------------
#include "Matrosova.h"
#include "Global.h"
//---------------------------------------------------------------------------
//Конструктор класса CMatrosova
//Входные переменные:
//int li_Level - уровень иерархии объекта в структуре  задачи
//string lc_String - порядковый номер объекта среди объектов одного типа
CMatrosova::CMatrosova(int li_Level, std::wstring lc_String) :
         CTaskBase(li_Level, lc_String)
{
    bc_Name = r("Матросова");
     bc_TypeName=bc_Name;
   // Сформировать структуру задачи
   //Цели по списку

    target = new CMyTarget (li_Level,r("1"),this,this); //цель

    missile = new CMyMissile (li_Level,r("1"),this,this); //ракета


    // Управление режимом видимости окон-закладок
    go_VisibleTrajectory = true;
    go_VisibleSpectr     = false;
    go_VisibleMiss       = false;

}
//---------------------------------------------------------------------------
//Деструктор класса
CMatrosova::~CMatrosova()
{
}

 void CMatrosova::set_inputs()
 {
     missile->setTargetData(target->getData());
 }



