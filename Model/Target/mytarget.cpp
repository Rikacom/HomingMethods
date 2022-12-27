#include "MyTarget.h"
#include "Global.h"
using namespace GLOBAL;
CMyTarget::CMyTarget(int li_Level, int li_Number, std::wstring lc_String) : CDynamicsBase(li_Level, li_Number, lc_String)
{
    char buffer[80];
    sprintf(buffer, "%d", li_Number+1);
    bc_Name = r("Моя цель ") + r(buffer);;
    bc_TypeName = bc_Name;
}
CMyTarget::~CMyTarget()
{
}
void CMyTarget::init_struct()
{
    // Для динамической отрисовки траекторий цели в процессе полета, для обмена с другими модулями и тд
    gpc_Task->gc_STargetList[bi_Number].bpc_Xg  = &vc_Xg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Vg  = &vc_Vg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Atg = &vc_Atg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Ntg = &vc_Ntg;
}
void CMyTarget::edit()
{
    std::wstring s1,s2,s3,s4,s5,s6;
    s1=r("Xo начальные координаты, м");
    s2=r("Yo начальные координаты, м");
    s3=r("Zo начальные координаты, м");
    s4=r("Vx начальная скорость, м/с");
    s5=r("Vy начальная скорость, м/с");
    s6=r("Vz начальная скорость, м/с");
    add(vc_Xg(1), s1, "400", "", "");
    add(vc_Xg(2), s2, "1500", "", "");
    add(vc_Xg(3), s3, "300", "", "");
    add(vc_Vg(1), s4, "200", "", "");
    add(vc_Vg(2), s5, "100", "", "");
    add(vc_Vg(3), s6, "300", "", "");
}
void CMyTarget::graf()
{
    std::wstring s1,s2,s3,s4,s5,s6;
    s1=r("X координата, м");
    s2=r("Y координата, м");
    s3=r("Z координата, м");
    s4=r("Vx скорость, м/с");
    s5=r("Vy скорость, м/с");
    s6=r("Vz скорость, м/с");
    add(vc_Xg(1),"vc_Xg(1)",s1);
    add(vc_Xg(2),"vc_Xg(2)",s2);
    add(vc_Xg(3),"vc_Xg(3)",s3);
    add(vc_Vg(1),"vc_Vg(1)",s4);
    add(vc_Vg(2),"vc_Vg(2)",s5);
    add(vc_Vg(3),"vc_Vg(3)",s6);
}
void CMyTarget::pre_initiate()
{
}
void CMyTarget::initiate()
{
    vc_Atg=Matrix(1, 0, 0,
                  0, 1, 0,
                  0, 0, 1);
    vc_Ntg=Vector(0,0,0);
}
void CMyTarget::calculate()
{
}
void CMyTarget::integrate()
{
    vc_Xg(1) += vc_Vg(1)*(gpc_Task->bd_dT);   // x+=vx*∆t
    vc_Xg(2) += vc_Vg(2)*(gpc_Task->bd_dT);   // y+=vy*∆t
    vc_Xg(3) += vc_Vg(3)*(gpc_Task->bd_dT);   // z+=vz*∆t
}
void CMyTarget::finalize()
{
}
