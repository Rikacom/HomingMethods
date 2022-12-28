# HomingMethods
Для демонстрации работы были созданы математические модели движения ракеты и аэродинамической цели. Решена задача встречи ракеты с целью для неуправляемого полета ракеты. Пограммно реализованы 3 метода самонаведения ракеты: метод самонаведения в мгновенную точку встречи, метод погони и метод пропорциональной навигации. Так же введено программное ограничение на предельную угловую скорость разворота ракеты и написан метод определения момента остановки математического моделирования.

**Для запуска математической модели HomingMethods, нужно её подключить к графическому интерфейсу QInterface.**
## Модель аэродинамической цели – MyTarget
Аэродинамическая цель – это объект, обладающий вектором координат (X координата, Y координата, Z координата) и вектором скоростей (Vx скорость, Vy скорость, Vz скорость) в пространстве, начальные координаты задаются через графический интерфейс.

Реализация движения цели:
``` c++
void CMyTarget::integrate()
{
    vc_Xg(1) += vc_Vg(1)*(gpc_Task->bd_dT);   // x+=vx*∆t
    vc_Xg(2) += vc_Vg(2)*(gpc_Task->bd_dT);   // y+=vy*∆t
    vc_Xg(3) += vc_Vg(3)*(gpc_Task->bd_dT);   // z+=vz*∆t
}
```

Для динамической отрисовки траекторий цели в процессе полета, для обмена с другими модулями и тд, реализован программный код:

``` c++
    gpc_Task->gc_STargetList[bi_Number].bpc_Xg  = &vc_Xg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Vg  = &vc_Vg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Atg = &vc_Atg;
    gpc_Task->gc_STargetList[bi_Number].bpc_Ntg = &vc_Ntg;
```
## Модель ракеты – MyMissile
Ракета – это объект, обладающий вектором координат (X координата, Y координата, Z координата) и модулем скорости |v| в пространстве (направление определяется алгоритмом), начальные координаты задаются через графический интерфейс. Ракета стремится попасть в цель, направление движение ракеты, определяется методом самонаведения. 

Реализация движения ракеты:
``` c++
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
```
![Система координат x, y, z](https://user-images.githubusercontent.com/94229700/209860390-babe468f-0040-4bc6-8e72-dab1006a38da.png)

Для динамической отрисовки траекторий ракеты в процессе полета необходимо, реализовать программный код:
``` c++
	gpc_Task->pOuterParams->missileData.Xg=&Xg;
	gpc_Task->pOuterParams->missileData.AarFromDrive=&AarFromDrive;
	gpc_Task->pOuterParams->missileData.Arg=&Arg;
	gpc_Task->pOuterParams->missileData.Aag=&Aag;
	gpc_Task->pOuterParams->missileData.Tet05=&Tet05;
	gpc_Task->pOuterParams->missileData.Satt=&Satt;
```
## Реализация 3 методов наведения :rocket:
### Метод - наведение в мгновенную точку встречи - параллельное сближение
В общем случае, был построен треугольник по 3 точкам (координаты цели, координаты ракеты, точка встречи ракеты с целью). Используя теоремы и формулы о треугольниках. Были найдены желаемые углы psi_method и theta_method.
![Метод параллельного сближения (общий случай)](https://user-images.githubusercontent.com/94229700/209862243-256f0328-0229-4172-aa73-d624919ab3a5.png)
Также были рассмотрены частные случаи, когда 
+ Цель не двигалась
+ Цель летела навстречу ракете
+ Цель отдалялась от ракеты
![параллельное сближение](https://user-images.githubusercontent.com/94229700/209852697-4a0514ae-c05c-469b-9145-49e26d1f40f2.png)
### Метод погони
Метод погони заключается в том, что вектор скорости летательного аппарата непрерывно направлен на цель. 
![Метод погони](https://user-images.githubusercontent.com/94229700/209862387-a184f59f-43ab-4324-9cea-d439606c9f00.png)
![метод погони](https://user-images.githubusercontent.com/94229700/209852667-2c9e85d2-a732-4e6f-a687-4d0983516c0b.png)
### Метод пропорционального сближения
![метод пропорционального сближения](https://user-images.githubusercontent.com/94229700/209852685-051b5f9a-8fa1-4726-aae4-71892d5d1b85.png)
