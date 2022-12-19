#include "MyMissile.h"
#include "Global.h"

using namespace GLOBAL;
CMyMissile::CMyMissile(int li_Level, std::wstring lc_String,CDialogObject* ParentPtr, CTaskBase* BasePtr) : CDynamicObject(li_Level, lc_String, ParentPtr, BasePtr)
{
        bc_Name = r("Моя ракета");
        bc_TypeName = bc_Name;
}
CMyMissile::~CMyMissile()
{
}
void CMyMissile::init_struct()
{
}
void CMyMissile::edit()
{
    std::wstring s1,s2,s3,s4;
    s1=r("Xo начальные кординаты, м");
    s2=r("Yo начальные кординаты, м");
    s3=r("|V| модуль скорости, м/с");
    s4=r("fi угол, град");
    add(x, s1, "1000", "", "");
    add(y, s2, "300", "", "");
    add(v_mod, s3, "223.60", "", "");
    add(fi,  s4, "63.43", "", "");
}
void CMyMissile::graf()
{
    std::wstring s1,s2,s3,s4,s5,s6,s7;
    s1=r("X координата, м");
    s2=r("Y координата, м");
    s3=r("Скорость Vx, м/с");
    s4=r("Скорость Vy, м/с");
    s5=r("Угол fi, град");
    s6=r("|V| модуль скорости, м/с");
    s7=r("Дистанция / дальность, м");
    add(x,"x",s1);
    add(y,"y",s2);
    add(vx,"vx",s3);
    add(vy,"vy",s4);
    add(fi,"fi",s5);
    add(v_mod,"v_mod",s6);
    add(distance,"distance",s7);
}
void CMyMissile::pre_initiate()
{  
}
void CMyMissile::initiate()
{
    fi=fi*gd_RAD; //перевод градусов в радианы
    vx=v_mod*cos(fi);
    vy=v_mod*sin(fi);
    distance=sqrt((x-*targetData->x_t)*(x-*targetData->x_t)+
                  (y-*targetData->y_t)*(y-*targetData->y_t));
                  //вычисляем дистанцию между ракетой и целью







    //v_mod1=√(vx1*vx1+vy1*vy1)
    double v_mod1=sqrt((*targetData->vx_t)*(*targetData->vx_t)+(*targetData->vy_t)*(*targetData->vy_t));

    double gamma=acos(
                ((x-*targetData->x_t)*(*targetData->vx_t)+(y-*targetData->y_t)*(*targetData->vy_t))
                /
                (sqrt((x-*targetData->x_t)*(x-*targetData->x_t)+(y-*targetData->y_t)*(y-*targetData->y_t))
                 *sqrt((*targetData->vx_t)*(*targetData->vx_t)+(*targetData->vy_t)*(*targetData->vy_t)))
                );
    //sin(betta)=[sin(180-betta)]=v_mod1*sin(gamma)/v_mod;
    //betta=asin(v_mod1*sin(gamma)/v_mod);
    //betta=M_PI-asin(v_mod1*sin(gamma)/v_mod);
    double betta1=asin(v_mod1*sin(gamma)/v_mod);
    double betta2=M_PI-asin(v_mod1*sin(gamma)/v_mod);
    betta1=betta1*180/M_PI;
    betta2=betta2*180/M_PI;
    betta2=betta2;
}
void CMyMissile::calculate()
{
    double newdistance;
    x += vx*(Base->bd_dT);   //x=x0+v_mod*cos(fi)*t=x0+vx*t
    y += vy*(Base->bd_dT);   //y=y0+v_mod*sin(fi)*t=y0+vy*t

    newdistance=sqrt((x-*targetData->x_t)*(x-*targetData->x_t)+
                     (y-*targetData->y_t)*(y-*targetData->y_t));
                     //вычисляем newдистанцию между ракетой и целью
    if(newdistance<=distance) //ракета стремиться попасть в цель, поэтому дистанция будет уменьшаться
    {
       distance=newdistance;
    }
    else                      //когда ракета начинает отдаляется от цели
    {
       gpc_Task->bo_FinishFlag = true;   //прекращаем текущую реализацию задачи
    }
}
void CMyMissile::integrate()
{
}
void CMyMissile::finalize()
{
}
void CMyMissile::setTargetData(SMyTarget* data)
{
    targetData=data;
}
