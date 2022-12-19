//---------------------------------------------------------------------------
#ifndef MatrosovaH
#define MatrosovaH
//---------------------------------------------------------------------------
#include "Cp_types.h"
#include "MyTarget.h"      //цель
#include "MyMissile.h"     //ракета
//------------------Описание класса CMatrosova-------------------------------
//Назначение: демонстрация работы АРГС в составе системы самонаведения
//ракеты
class CMatrosova : public CTaskBase
{
public:
   //-------------------------Методы класса--------------------------------------
   //Конструктор класса
    CMatrosova(int li_Level, std::wstring lc_String);
   //Деструктор класса
    virtual ~CMatrosova();
    void set_inputs(); //передача
private:

    CMyTarget* target; //цель

    CMyMissile* missile; //ракета


//------------------Данные класса--------------------------------------------
};
//---------------------------------------------------------------------------
#endif

