#ifndef MYTARGET_H
#define MYTARGET_H
#include "Cp_types.h"
#include "Exchange.h"

class CMyTarget : public CDynamicObject
{
public:
    CMyTarget(int li_Level, std::wstring lc_String,CDialogObject* ParentPtr = 0, CTaskBase* BasePtr =0);
    virtual ~CMyTarget();
    void init_struct();
    void edit();
    void graf();
    void pre_initiate();
    void initiate();
    void calculate();
    void integrate();
    void finalize();
    SMyTarget* getData();   //функция выдачи указателя на выходные данные цели

private:
    double x;
    double y;
    double vx;
    double vy;
    SMyTarget source_Target;  //структура выходных данных цели
};

#endif // MYTARGET_H
