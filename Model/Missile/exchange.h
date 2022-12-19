#ifndef EXCHANGE_H
#define EXCHANGE_H

struct SMyTarget
{
    double* x_t;
    double* y_t;
    double* vx_t;
    double* vy_t;
    SMyTarget()
    {
        x_t=0;
        y_t=0;
        vx_t=0;
        vy_t=0;
    };
};

#endif // EXCHANGE_H
