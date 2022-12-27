#ifndef MYTARGET_H
#define MYTARGET_H

#include "Cp_types.h"
#include "ChuLib.h"

using namespace ChuLib;

class CMyTarget : public CDynamicsBase
{
public:
    CMyTarget(int li_Level, int li_Number, std::wstring lc_String);
    virtual ~CMyTarget();
    void init_struct();
    void edit();
    void graf();
    void pre_initiate();
    void initiate();
    void calculate();
    void integrate();
    void finalize();

private:
    Vector vc_Xg;  // вектор координат (X координата, Y координата, Z координата)
    Vector vc_Vg;  // вектор скоростей (Vx скорость,  Vy скорость,  Vz скорость)
    Matrix vc_Atg; // матрица переходов из земной системы в систему координат цели
    Vector vc_Ntg; // вектор ускорений
};

#endif // MYTARGET_H
