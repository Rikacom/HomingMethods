#ifndef MYMISSILE_H
#define MYMISSILE_H
#include "Cp_types.h"
#include "Exchange.h"

class CMyMissile : public CDynamicObject
{
public:
    CMyMissile(int li_Level, std::wstring lc_String,CDialogObject* ParentPtr = 0, CTaskBase* BasePtr =0);
    virtual ~CMyMissile();
    void init_struct();
    void edit();
    void graf();
    void pre_initiate();
    void initiate();
    void calculate();
    void integrate();
    void finalize();
    void setTargetData(SMyTarget* data); // получение указателя структуры с выходными данными цели

private:
    double x;
    double y;
    double vx;
    double vy;
    double fi;
    double v_mod;
    double distance; // дистанция / дальность
    SMyTarget* targetData;
};

#endif // MYMISSILE_H
