#ifndef MYMISSILE_H
#define MYMISSILE_H

#include "Cp_types.h"
#include "ChuLib.h"

using namespace ChuLib;

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
    void final();                                // Метод определения момента остановки математического моделирования
    void methodTardetingAnInstantMeetingPoint(); // Метод - наведение в мгновенную точку встречи - параллельное сближение
    void methodChase();                          // Метод погони
    void methodProportionalConvergence();        // Метод пропорционального сближения
    void limitOnTheSpeedOfAngleChange();         // Метод ограничений на предельную угловую скорость разворота ракеты

private:
    Vector Vg;           // вектор скоростей ракеты (Vx скорость,  Vy скорость,  Vz скорость)

    Vector Xg;           // вектор координат ракеты (X координата, Y координата, Z координата)
    Matrix AarFromDrive; // матрица перехода в антенную систему координат из связанной системы координат
    Matrix Arg;          // матрица перехода в связанную систему координат из земной системы координат
    Matrix Aag;          // матрица перехода из земной системы координат в антенную систему координат
    double Tet05;        // ширина главного лепестка диаграммы направленности антенны
    int Satt;            // признак захвата цели

    Vector Xg_t;         // вектор координат цели (X координата, Y координата, Z координата)
    Vector Vg_t;         // вектор скоростей цели (Vx скорость,  Vy скорость,  Vz скорость)

    double theta_0;      // Угол θ (theta) - начальный, вводим через интерфейс
    double psi_0;        // Угол ψ (psi) - начальный, вводим через интерфейс
    double theta_method; // Угол θ (theta) - рассчитывает метод
    double psi_method;   // Угол ψ (psi) - рассчитывает метод
    double theta;        // Угол θ (theta) - текущий угол азимута между вектором скорости ракеты и вертикальной плоскостью
    double psi;          // Угол ψ (psi) - текущий угол места между вектором скорости ракеты и горизонтальной плоскостью
    double alpha;        // Угол α (alpha) - проекция угла линии визирования на горизонтальную плоскость
    double beta;         // Угол β (beta) - проекция угла линии визирования на вертикальную плоскость
    double alpha_old;
    double beta_old;
    double alpha_pr;     // Производная угла линии визирования на горизонтальную плоскость
    double beta_pr;      // Производная угла линии визирования на вертикальную плоскость
    double lambda_lim;   // Ограничение на предельную угловую скорость разворота ракеты
    double v_mod;        // |V| модуль скорости
    double distance;     // Дистанция / дальность
    int methodNumber;    // Номер метода наведения
    double k;            // Коэффициент пропорциональности
    double T_turn;       // Время на разворот
    int signFirstCount;  // (признак) в initiate() вычисляется первоначальная дистанция, далее вызывается первый раз
                         // calculate()->final(). В final() вычисляется новая дистанция между ракетой и целью. Вычисленные значения
                         // дистанций совпадут, поэтому программа прекратит моделирование (тк дистанция не уменьшилась).
                         // Чтобы этого избежать был создан признак.
                         // Пусть в initiate() signFirstCount=1
    int signFirstCountForMPC; // (признак) в методе пропорционального сближения нужно вычислить первоначальные значения
                              // Пусть в initiate() signFirstCountForMPC=1
};

#endif // MYMISSILE_H
