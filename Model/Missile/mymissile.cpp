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
    // Для динамической отрисовки траекторий ракеты в процессе полета
    gpc_Task->pOuterParams->missileData.Xg=&Xg;
    gpc_Task->pOuterParams->missileData.AarFromDrive=&AarFromDrive;
    gpc_Task->pOuterParams->missileData.Arg=&Arg;
    gpc_Task->pOuterParams->missileData.Aag=&Aag;
    gpc_Task->pOuterParams->missileData.Tet05=&Tet05;
    gpc_Task->pOuterParams->missileData.Satt=&Satt;
}
void CMyMissile::edit()
{
    std::wstring s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
    s5=r("Номер метода наведения\n 1 - Наведение в мгновенную точку встречи - параллельное сближение\n 2 - Метод погони\n 3 - Метод пропорционального сближения");
    s1=r("Xo начальные координаты, м");
    s2=r("Yo начальные координаты, м");
    s3=r("Zo начальные координаты, м");
    s4=r("|V| модуль скорости, м/с");
    s6=r("θ начальный угол азимута вектора скорости ракеты, град");
    s7=r("ψ начальный угол места вектора скорости ракеты, град");
    s8=r("k коэффициент пропорциональности");
    s9=r("λ_lim ограничение на предельную угловую скорость разворота ракеты, град/с");
    s10=r("T_turn время на разворот");
    add(methodNumber, s5, "1", "", "");
    add("1"); // разрешаю methodNumber присвоить значение 1 - Наведение в мгновенную точку встречи - параллельное сближение
    add("2"); // разрешаю methodNumber присвоить значение 2 - Метод погони
    add("3"); // разрешаю methodNumber присвоить значение 3 - Метод пропорционального сближения
    add(Xg(1), s1, "2000", "", "");
    add(Xg(2), s2, "3000", "", "");
    add(Xg(3), s3, "500", "", "");
    add(v_mod, s4, "600", "", "");
    add(theta_0, s6, "-60", "-180", "180");
    add(psi_0, s7, "180", "-180", "180");
    add(k, s8, "4", "", ""); // от 0, но лучше от 3 до 4
    add(lambda_lim, s9, "5", "", "");
    add(T_turn, s10, "90", "", "");
}
void CMyMissile::graf()
{
    std::wstring s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17;
    s1=r("X координата, м");
    s2=r("Y координата, м");
    s3=r("Z координата, м");
    s4=r("Vx скорость, м/с");
    s5=r("Vy скорость, м/с");
    s6=r("Vz скорость, м/с");
    s7=r("Угол θ (theta) угол азимута между вектором скорости ракеты и вертикальной плоскостью, град");
    s8=r("Угол ψ (psi) угол места между вектором скорости ракеты и горизонтальной плоскостью, град");
    s16=r("Угол θ по методу (theta_method) угол азимута между вектором скорости ракеты и вертикальной плоскостью, град");
    s17=r("Угол ψ по методу (psi_method) угол места между вектором скорости ракеты и горизонтальной плоскостью, град");
    s9=r("|V| модуль скорости, м/с");
    s10=r("Дистанция / дальность, м");
    s11=r("Коэффициент пропорциональности");
    s12=r("α (alpha) угол линии визирования на горизонтальную плоскость");
    s13=r("β (beta) угол линии визирования на вертикальную плоскость");
    s14=r("α' производная угла линии визирования на горизонтальную плоскость");
    s15=r("β' производная угла линии визирования на вертикальную плоскость");
    add(Xg(1),"Xg(1)",s1);
    add(Xg(2),"Xg(2)",s2);
    add(Xg(3),"Xg(3)",s3);
    add(Vg(1),"Vg(1)",s4);
    add(Vg(2),"Vg(2)",s5);
    add(Vg(3),"Vg(3)",s6);
    add(theta,"theta",s7,gd_DEG);
    add(psi,"psi",s8,gd_DEG);
    add(theta_method,"theta_method",s16,gd_DEG);
    add(psi_method,"psi_method",s17,gd_DEG);
    add(v_mod,"v_mod",s9);
    add(distance,"distance",s10);
    add(k,"k",s11);
    add(alpha,"alpha",s12,gd_DEG);
    add(beta,"beta",s13,gd_DEG);
    add(alpha_pr,"alpha_pr",s14,gd_DEG);
    add(beta_pr,"beta_pr",s15,gd_DEG);
}
void CMyMissile::pre_initiate()
{
}
void CMyMissile::initiate()
{
    // Получаю информацию о цели
    Xg_t=*gpc_Task->gc_STargetList[0].bpc_Xg;
    Vg_t=*gpc_Task->gc_STargetList[0].bpc_Vg;

    signFirstCount = 1;
    signFirstCountForMPC = 1;

    lambda_lim=lambda_lim*gd_RAD*(Base->bd_dT); // Перевод градусов в радианы + считаем ограничение за такт
    theta_0=theta_0*gd_RAD;                     // Перевод градусов в радианы
    psi_0=psi_0*gd_RAD;                         // Перевод градусов в радианы
    theta=theta_0;                              // theta (текущий угол) присваиваем начальное значение (theta_0)
    psi=psi_0;                                  // psi (текущий угол) присваиваем начальное значение (psi_0)

    // Вычисляем дистанцию между ракетой и целью
    distance=sqrt((Xg(1)-Xg_t(1))*(Xg(1)-Xg_t(1))+(Xg(2)-Xg_t(2))*(Xg(2)-Xg_t(2))+(Xg(3)-Xg_t(3))*(Xg(3)-Xg_t(3)));

    AarFromDrive=Matrix(1, 0, 0,
                        0, 1, 0,
                        0, 0, 1);
    Arg=Matrix(1, 0, 0,
               0, 1, 0,
               0, 0, 1);
    Aag=Matrix(1, 0, 0,
               0, 1, 0,
               0, 0, 1);
    Tet05=3;
    Satt=0;
}
void CMyMissile::calculate()
{
    // Получаю информацию о цели
    Xg_t=*gpc_Task->gc_STargetList[0].bpc_Xg;
    Vg_t=*gpc_Task->gc_STargetList[0].bpc_Vg;

    switch (methodNumber) {       // methodNumber - номер метода наведения
    case 1:                       // 1 - Наведение в мгновенную точку встречи - параллельное сближение
        {
        methodTardetingAnInstantMeetingPoint();
        break;
        }
    case 2:                       // 2 - Метод погони
        {
        methodChase();
        break;
        }
    case 3:                       // 3 - Метод пропорционального сближения
        {
        methodProportionalConvergence();
        break;
        }
    default:
        break;
    }
    // theta_method и psi_method желаемые углы

    limitOnTheSpeedOfAngleChange(); // Метод ограничений на предельную угловую скорость разворота ракеты

    Vg(1)=v_mod*cos(theta)*cos(psi);
    Vg(2)=v_mod*sin(theta);
    Vg(3)=v_mod*cos(theta)*sin(psi);

    final();                        // Метод определения момента остановки математического моделирования
}
void CMyMissile::integrate()
{
    Xg(1) += Vg(1)*(Base->bd_dT);          // x+=vx*∆t
    Xg(2) += Vg(2)*(Base->bd_dT);          // y+=vy*∆t
    Xg(3) += Vg(3)*(Base->bd_dT);          // z+=vz*∆t
}
void CMyMissile::finalize()
{
}
void CMyMissile::final()
{
    // Вычисляем newдистанцию между ракетой и целью
    double newdistance;
    newdistance=sqrt((Xg(1)-Xg_t(1))*(Xg(1)-Xg_t(1))+(Xg(2)-Xg_t(2))*(Xg(2)-Xg_t(2))+(Xg(3)-Xg_t(3))*(Xg(3)-Xg_t(3)));

    if((signFirstCount==1)||(newdistance<distance)) // Ракета стремиться попасть в цель, поэтому дистанция будет уменьшаться
    {
       distance=newdistance;
       signFirstCount=0;
    }
    else                                           // Когда ракета начинает отдаляется от цели
    {
        if (Base->bd_T<=T_turn)                    // Разрешаю ракете развернуться за время T_turn
        {
            distance=newdistance;
        }
        else
        {
           gpc_Task->bo_FinishFlag = true;        // Прекращаем текущую реализацию задачи
        }
    }
}
void CMyMissile::methodTardetingAnInstantMeetingPoint()
{
    // Вычисляем углы θ (theta) и ψ (psi)>>

        // цель (x01,yo1,zo1,vx1,vy1,vz1) или (*targetData->x_t,*targetData->y_t,*targetData->z_t,*targetData->vx_t,*targetData->vy_t,*targetData->vz_t)
        //  Ta          B
        //   *__>________________* O точка встречи
        //     -gamma        %  -
        //      -       h %    -
        //     A  -    %      -  C
        //          -       ^
        //            -beta/
        //              *    θ (theta) и ψ (psi)
        //              M ракета (x02=x,y02=y,z02=z,vmod2=v_mod)

        double T; // Время

        // v_mod1=√(vx1*vx1+vy1*vy1+vz1*vz1) - модуль скорости цели
        double v_mod1=sqrt(Vg_t(1)*Vg_t(1)+Vg_t(2)*Vg_t(2)+Vg_t(3)*Vg_t(3));

        // Вычисляем расстояние A между точками Ta и M
        // A=sqrt((x01-x02)*(x01-x02)+(y01-y02)*(y01-y02)+(z01-z02)*(z01-z02))
        double A=sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(2)-Xg(2))*(Xg_t(2)-Xg(2))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3)));

        if(v_mod1==0) // Если цель не летит
            {
            // A=v_mod2*T
            T=A/v_mod;

            // M=(x02,y02,z02)
            // Ta=(x01,y01,z01)
            // Вектор MTa перемещаем в начало координат (будет вектор M1Ta1)
            // M=(0,0,0)
            // Ta1=(x01-x02,y01-y02,z01-z02)=(Ta1_x,Ta1_y,Ta1_z)
            // ψ (psi) = atan(Ta1_z/Ta1_x)
            // θ (theta) = atan(Ta1_y/(sqrt(Ta1_x*Ta1_x+Ta1_z*Ta1_z)));
            psi_method=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
            theta_method=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
            }
        else
            {
            // Единичный вектор TaO* = {vx1,vy1,vz1}
            // Вектор TaM = {x02-x01,y02-y01,z02-z01}
            // Зная два вектора, можем вычислить угол gamma
            double gamma=acos(
                              ((Xg(1)-Xg_t(1))*Vg_t(1)+(Xg(2)-Xg_t(2))*Vg_t(2)+(Xg(3)-Xg_t(3))*Vg_t(3))
                              /
                              (sqrt((Xg(1)-Xg_t(1))*(Xg(1)-Xg_t(1))+(Xg(2)-Xg_t(2))*(Xg(2)-Xg_t(2))+(Xg(3)-Xg_t(3))*(Xg(3)-Xg_t(3)))
                               *sqrt(Vg_t(1)*Vg_t(1)+Vg_t(2)*Vg_t(2)+Vg_t(3)*Vg_t(3)))
                             );

            if(gamma==(180*gd_RAD)) // Если цель будет отдаляться от ракеты
                {
                if(v_mod<v_mod1) // Если v_modракеты<v_modцели, то ракета не долетит
                    {
                    gpc_Task->bo_FinishFlag = true;   // Прекращаем текущую реализацию задачи
                    }
                else
                    {
                    //  * O точка встречи
                    //    ---
                    //        -<-           C
                    //   B         * Ta цель (x01,yo1,zo1,vx1,vy1,vz1)
                    //                 ---
                    //                     -<-      θ (theta) и ψ (psi)
                    //            A             *
                    //                          M ракета (x02=x,y02=y,z02=z,vmod2=v_mod)

                    // B=v_mod1*T
                    // C=v_mod2*T=B+A=v_mod1*T+A
                    // Выражаем T и вычисляем
                    T=A/(v_mod-v_mod1);

                    // M=(x02,y02,z02)
                    // Ta=(x01,y01,z01)
                    // Вектор MTa перемещаем в начало координат (будет вектор M1Ta1)
                    // M=(0,0,0)
                    // Ta1=(x01-x02,y01-y02,z01-z02)=(Ta1_x,Ta1_y,Ta1_z)
                    // ψ (psi) = atan(Ta1_z/Ta1_x)
                    // θ (theta) = atan(Ta1_y/(sqrt(Ta1_x*Ta1_x+Ta1_z*Ta1_z)));
                    psi_method=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
                    theta_method=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
                    }
                }
            else
                {
                if(!gamma) // Если цель будет лететь на встречу ракете
                    {
                    //  * Ta цель (x01,yo1,zo1,vx1,vy1,vz1)
                    //    ->-
                    //        ---  B
                    //             *  O точка встречи
                    //       A         ---
                    //                     -<- C    θ (theta) и ψ (psi)
                    //                          *
                    //                          M ракета (x02=x,y02=y,z02=z,vmod2=v_mod)

                    // B=v_mod1*T
                    // C=v_mod2*T=A-B=A-v_mod1*T
                    // Выражаем T и вычисляем
                    T=A/(v_mod+v_mod1);

                    // M=(x02,y02,z02)
                    // Ta=(x01,y01,z01)
                    // Вектор MTa перемещаем в начало координат (будет вектор M1Ta1)
                    // M=(0,0,0)
                    // Ta1=(x01-x02,y01-y02,z01-z02)=(Ta1_x,Ta1_y,Ta1_z)
                    // ψ (psi) = atan(Ta1_z/Ta1_x)
                    // θ (theta) = atan(Ta1_y/(sqrt(Ta1_x*Ta1_x+Ta1_z*Ta1_z)));
                    psi_method=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
                    theta_method=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
                    }
                else // получается треугольник
                    {
                    // Из точки O проводим высоту h
                    // sin(gamma)=h/B     ->     h=B*sin(gamma)
                    // sin(beta)=h/C=B*sin(gamma)/C
                    // B=v_mod1*T, где T-время
                    // C=v_mod2*T
                    // sin(beta)=v_mod1*sin(gamma)/v_mod2
                    // Если нарисовать дугой треугольник, то может возникнуть ситуация sin(180-beta)=v_mod1*sin(gamma)/v_mod2
                    // Но sin(beta)=sin(180-beta)=v_mod1*sin(gamma)/v_mod
                    // *Были рассмотрены все виды треугольников и sin(угла)=v_mod1*sin(gamma)/v_mod2
                    //
                    // Получается два угла beta (beta1 и beta2):
                    // beta1=asin(v_mod1*sin(gamma)/v_mod)        - острый
                    // beta2=M_PI-asin(v_mod1*sin(gamma)/v_mod)   - тупой
                    //
                    // Существование beta2 объясняется тем, что gamma - может быть острым углом
                    // Но мы все равно должны проверить, что сумма 2ух углов меньше 180     ->     (gamma+beta2)<180
                    //
                    // Для всех вариантов подойдет острый угол beta=beta1=asin(v_mod1*sin(gamma)/v_mod);
                    // if((gamma+beta2)<(180*gd_RAD)) beta=beta2=M_PI-asin(v_mod1*sin(gamma)/v_mod); // для случая gamma-острый и сумма (gamma+beta2)<180 есть два варианта решения
                    //
                    //
                    // Но пример -> если цель летит слишком быстро, а ракета слишком медленно -> угол бессмысленно выбирать, тк ракета не долетит
                    // Этот момент можно отследить:
                    // beta=asin(v_mod1*sin(gamma)/v_mod)   ->   если |(v_mod1*sin(gamma)/v_mod)|<=1, то угол beta существует
                    //                                           иначе нет (ракета не долетит)
                    if(fabs(v_mod1*sin(gamma)/v_mod)<=1)
                        {
                            double beta=asin(v_mod1*sin(gamma)/v_mod);

                            // TaO=B=v_mod1*T=[формула нахождения стороны через два угла и сторону]=A*sin(beta)/sin(gamma+beta)
                            // Выражаем T и вычисляем
                            T=A*sin(beta)/(sin(gamma+beta)*v_mod1);

                            // M=(x02,y02,z02)
                            // O=(x01+vx1*T,y01+vy1*T,z01+vz1*T)
                            // Вектор MO перемещаем в начало координат (будет вектор M1O1)
                            // M=(0,0,0)
                            // O=(x01+vx1*T-x02,y01+vy1*T-y02,z01+vz1*T-z02)=(O_x,O_y,O_z)
                            // ψ (psi) = atan(O_z/O_x)
                            // θ (theta) = atan(O_y/(sqrt(O_x*O_x+O_z*O_z)));
                            psi_method=atan2(Xg_t(3)+Vg_t(3)*T-Xg(3),Xg_t(1)+Vg_t(1)*T-Xg(1));
                            theta_method=atan2(Xg_t(2)+Vg_t(2)*T-Xg(2), sqrt((Xg_t(1)+Vg_t(1)*T-Xg(1))*(Xg_t(1)+Vg_t(1)*T-Xg(1))
                                                                            +(Xg_t(3)+Vg_t(3)*T-Xg(3))*(Xg_t(3)+Vg_t(3)*T-Xg(3))));
                        }
                    else
                        {
                        gpc_Task->bo_FinishFlag = true;   // Прекращаем текущую реализацию задачи
                        }
                    }
                }
            }
    // Заканчиваем вычислять углы θ (theta) и ψ (psi)<<
}
void CMyMissile::methodChase()
{
    //  * Ta цель (x01,yo1,zo1,vx1,vy1,vz1)
    //    ---
    //        ---
    //            ---
    //                ---
    //                    -<-     θ (theta) и ψ (psi)
    //                        *
    //                        M ракета (x02=x,y02=y,z02=z,vmod2=v_mod)

    // M=(x02,y02,z02)
    // Ta=(x01,y01,z01)
    // Вектор MTa перемещаем в начало координат (будет вектор M1Ta1)
    // M=(0,0,0)
    // Ta1=(x01-x02,y01-y02,z01-z02)=(Ta1_x,Ta1_y,Ta1_z)
    // ψ (psi) = atan(Ta1_z/Ta1_x)
    // θ (theta) = atan(Ta1_y/(sqrt(Ta1_x*Ta1_x+Ta1_z*Ta1_z)));
    psi_method=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
    theta_method=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
}
void CMyMissile::methodProportionalConvergence()
{
    // Для метода нужно знать значения α и β на предыдущем шаге - alpha_old и beta_old
    if(signFirstCountForMPC==1) // Если это первый запуск метода...
        {
            // При первом запуске метода достаточно вычислить, чему равны α и β. Они же будут alpha_old и beta_old при следующем запуске
            alpha=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
            beta=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
            alpha_old=alpha;
            beta_old=beta;
            signFirstCountForMPC=0;
            // psi_method и theta_method первоначально заполняются через интерфейс
            psi_method=psi_0;
            theta_method=theta_0;
        }
    else
        {
            // Вычисляем α и β в текущей такт времени
            alpha=atan2(Xg_t(3)-Xg(3),Xg_t(1)-Xg(1));
            beta=atan2(Xg_t(2)-Xg(2),sqrt((Xg_t(1)-Xg(1))*(Xg_t(1)-Xg(1))+(Xg_t(3)-Xg(3))*(Xg_t(3)-Xg(3))));
            alpha_pr=(alpha-alpha_old)/(Base->bd_dT); // Вычисляем производную угла линии визирования на горизонтальную плоскость
            beta_pr=(beta-beta_old)/(Base->bd_dT);    // Вычисляем производную угла линии визирования на вертикальную плоскость
            psi_method=psi_method+k*alpha_pr*(Base->bd_dT);         // ψ{i+1}=ψ{i}+k*α'{i}*∆t
            theta_method=theta_method+k*beta_pr*(Base->bd_dT);      // θ{i+1}=θ{i}+k*β'{i}*∆t
            alpha_old=alpha;                          // Запоминаем α (будет alpha_old на следующем шаге)
            beta_old=beta;                            // Запоминаем β (будет beta_old на следующем шаге)
            // Корректируем углы psi и theta от [-180°, + 180°]
            psi_method=atan2(sin(psi_method),cos(psi_method));
            theta_method=atan2(sin(theta_method),cos(theta_method));
        }
}
void CMyMissile::limitOnTheSpeedOfAngleChange()
{
    // theta_method и psi_method желаемые углы

    // Углы psi, theta, psi_method и theta_method от [-180°, + 180°]
    // При этом мы хотим получить разницу, к примеру, между углами 170° и +170° в 20°, для этого корректируем угол
    if(fabs(theta-theta_method)>(180*gd_RAD))
    {
        if(theta>0)
        {
            theta_method=theta_method+360*gd_RAD;
        }
        else
        {
            theta=theta+360*gd_RAD;
        }
    }

    if(fabs(psi-psi_method)>(180*gd_RAD))
    {
        if(psi>0)
        {
            psi_method=psi_method+360*gd_RAD;
        }
        else
        {
            psi=psi+360*gd_RAD;
        }
    }

    // Вектор скорости от текущих углов (psi и theta)                = ( cos(theta)*cos(psi),                sin(theta),         cos(theta)*sin(psi)               )
    // Вектор скорости от желаемых углов (psi_method и theta_method) = ( cos(theta_method)*cos(psi_method),  sin(theta_method),  cos(theta_method)*sin(psi_method) )
    // Найдем угол lambda_method между векторами
    double lambda_method;
    double lambda_method_cos;
    lambda_method_cos=(cos(theta)*cos(psi)*cos(theta_method)*cos(psi_method)+sin(theta)*sin(theta_method)+cos(theta)*sin(psi)*cos(theta_method)*sin(psi_method))
                      /
                      (sqrt(cos(theta)*cos(psi)*cos(theta)*cos(psi)+sin(theta)*sin(theta)+cos(theta)*sin(psi)*cos(theta)*sin(psi))
                       *sqrt(cos(theta_method)*cos(psi_method)*cos(theta_method)*cos(psi_method)+sin(theta_method)*sin(theta_method)+cos(theta_method)*sin(psi_method)*cos(theta_method)*sin(psi_method)));
    if(lambda_method_cos>1)    // Было замечено, что lambda_method_cos мог быть чуть больше 1. Это недопустимо.
        lambda_method_cos=1;
    if(lambda_method_cos<-1)   // На всякий случай
        lambda_method_cos=-1;
    lambda_method=acos(lambda_method_cos);

    if(lambda_method<lambda_lim)
    {
        psi=psi_method;
        theta=theta_method;
    }
    else
    {
        double k=lambda_lim/lambda_method;
        psi=psi+(psi_method-psi)*k;
        theta=theta+(theta_method-theta)*k;
    }

    // Корректируем углы psi, theta и psi_method, theta_method от [-180°, + 180°]
    psi=atan2(sin(psi),cos(psi));
    theta=atan2(sin(theta),cos(theta));
    psi_method=atan2(sin(psi_method),cos(psi_method));
    theta_method=atan2(sin(theta_method),cos(theta_method));
}
