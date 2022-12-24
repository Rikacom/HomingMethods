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
//угол    s4=r("fi угол, град");
    add(x, s1, "1000", "", "");
    add(y, s2, "300", "", "");
    add(v_mod, s3, "223.60", "", "");
//угол    add(fi,  s4, "63.43", "", "");
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
//угол  fi=fi*gd_RAD; //перевод градусов в радианы

//вычисляем угол fi>>

    // цель (x01,yo1,vx1,vy1) или (*targetData->x_t,*targetData->y_t,*targetData->vx_t,*targetData->vy_t)
    //  Ta          B
    //   *__>________________* O точка встречи
    //     -gamma        %  -
    //      -       h %    -
    //     A  -    %      -  C
    //          -       ^
    //            -beta/
    //              *    fi
    //              M ракета (x02=x,y02=y,vmod2=v_mod)


    //v_mod1=√(vx1*vx1+vy1*vy1) - модуль скорости цели
    double v_mod1=sqrt((*targetData->vx_t)*(*targetData->vx_t)+(*targetData->vy_t)*(*targetData->vy_t));

    //единичный вектор TaO* = {vx1,vy1}
    //вектор TaM = {x02-x01,y02-y01}
    //зная два вектора можем вычислить угол gamma
    double gamma=acos(
                ((x-*targetData->x_t)*(*targetData->vx_t)+(y-*targetData->y_t)*(*targetData->vy_t))
                /
                (sqrt((x-*targetData->x_t)*(x-*targetData->x_t)+(y-*targetData->y_t)*(y-*targetData->y_t))
                 *sqrt((*targetData->vx_t)*(*targetData->vx_t)+(*targetData->vy_t)*(*targetData->vy_t)))
                );

    //из точки O проводим высоту h
    //sin(gamma)=h/B     ->     h=B*sin(gamma)
    //sin(beta)=h/C=B*sin(gamma)/C
    //B=v_mod1*T ,где T-время
    //C=v_mod2*T
    //sin(beta)=v_mod1*sin(gamma)/v_mod2
    //если нарисовать дугой треугольник, то может возникнуть ситуация sin(180-beta)=v_mod1*sin(gamma)/v_mod2
    //но sin(beta)=sin(180-beta)=v_mod1*sin(gamma)/v_mod
    //*были рассмотренеы все виды треуголников и sin(угла)=v_mod1*sin(gamma)/v_mod2
    //
    //получается два угла beta (beta1 и beta2):
    //beta1=asin(v_mod1*sin(gamma)/v_mod);       - острый
    //beta2=M_PI-asin(v_mod1*sin(gamma)/v_mod);  - тупой
    //
    //существование beta2 объясняется тем, что gamma - может быть острым углом
    //но мы все равно должны проверить, что сумма 2ух углов меньше 180     ->     (gamma+beta2)<180
    double beta1=asin(v_mod1*sin(gamma)/v_mod);
    double beta2=M_PI-asin(v_mod1*sin(gamma)/v_mod);
    double beta=beta1; //для всех вариантов подойдет острый угол
    if((gamma+beta2)<(180*gd_RAD)) beta=beta2; //для случая gamma-острый и сумма (gamma+beta2)<180 есть два варианта решения

    //вычисляем расстояние A между точками Ta и M
    //A=sqrt((x01-x02)*(x01-x02)+(y01-y02)*(y01-y02))
    double A=sqrt((*targetData->x_t-x)*(*targetData->x_t-x)+(*targetData->y_t-y)*(*targetData->y_t-y));

    //TaO=B=v_mod1*T=[формула нахождения стороны через два угла и сторону]=A*sin(beta)/sin(gamma+beta)
    //выражаем T и вычисляем
    double T=A*sin(beta)/(sin(gamma+beta)*v_mod1);

    //M=(x02,y02)
    //O=(x01+vx1*T,y01+vy1*T)
    //вектор MO перемещаем в начало координат (будет вектор M1O1)
    //M=(0,0)
    //O=(x01+vx1*T-x02,y01+vy1*T-y02)=(O_x,O_y)
    //tan(fi)=O_y/O_x
    //fi=atan(O_y/O_x)
    fi=atan2((*targetData->y_t+(*targetData->vy_t)*T-y),(*targetData->x_t+(*targetData->vx_t)*T-x));
//заканчиваем вычислять угол fi<<

    vx=v_mod*cos(fi);
    vy=v_mod*sin(fi);
    distance=sqrt((x-*targetData->x_t)*(x-*targetData->x_t)+
                  (y-*targetData->y_t)*(y-*targetData->y_t));
                  //вычисляем дистанцию между ракетой и целью
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
