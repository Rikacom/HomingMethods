#include "MyTarget.h"
#include "Global.h"
using namespace GLOBAL;
CMyTarget::CMyTarget(int li_Level, std::wstring lc_String,CDialogObject* ParentPtr, CTaskBase* BasePtr) : CDynamicObject(li_Level, lc_String, ParentPtr, BasePtr)
{
        bc_Name = r("Моя цель");
        bc_TypeName = bc_Name;
}
CMyTarget::~CMyTarget()
{
}
void CMyTarget::init_struct()  //настраиваю адреса на выходные данные цели
{
    source_Target.x_t=&x;
    source_Target.y_t=&y;
    source_Target.vx_t=&vx;
    source_Target.vy_t=&vy;
}
void CMyTarget::edit()
{
    std::wstring s1,s2,s3,s4;
    s1=r("Xo начальные кординаты, м");
    s2=r("Yo начальные кординаты, м");
    s3=r("Vx начальная скорость, м/с");
    s4=r("Vy начальная скорость, м/с");
    add(x, s1, "400", "", "");
    add(y, s2, "1500", "", "");
    add(vx, s3, "200", "", "");
    add(vy,  s4, "0", "", "");
}
void CMyTarget::graf()
{
    std::wstring s1,s2,s3,s4;
    s1=r("X координата, м");
    s2=r("Y координата, м");
    s3=r("Скорость Vx, м/с");
    s4=r("Скорость Vy, м/с");
    add(x,"x",s1);
    add(y,"y",s2);
    add(vx,"vx",s3);
    add(vy,"vy",s4);
}
void CMyTarget::pre_initiate()
{
}
void CMyTarget::initiate()
{
}
void CMyTarget::calculate()
{
    x += vx*(Base->bd_dT);   //x=x0+vx*t
    y += vy*(Base->bd_dT);   //y=y0+vy*t
}
void CMyTarget::integrate()
{
}
void CMyTarget::finalize()
{
}
SMyTarget* CMyTarget::getData()
{
    return &source_Target;
}


