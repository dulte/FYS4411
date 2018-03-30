#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "system.h"
#include "Parameters/parameters.h"
#include "DataDump/datadump.h"
//#include "MTLS.h"


class Simulation
{
public:
    Simulation(System *m_system);
    void initiate();
    void run(int rank);

    double conjugate_gradient(double alpha_0, double b);
    double compute_local_energy_derivative(double alpha);
    void data_for_derivated();
    void oneBodyDensity(double optimal_alpha, double r_step, double r_min, double r_max);
private:
    System *system;
    double alpha_step;
    double alpha_min;
    double alpha_max;

    double total_energy;

    int MC_cycles;
    int N;

    double energy;


};

#endif // SIMULATION_H
