#include <iostream>
#include <memory>
#include "simulation.h"
#include "system.h"
#include "Systems/randomsystem.h"
#include "trialfunction.h"
#include "potential.h"
#include "Potentials/harmonicoscillator.h"
#include "Parameters/parameters.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    //Read Parameters
    //Parameters params = Parameters::instance();
    Parameters::read_parameters("../input/parameters.txt");
    cout << Parameters::beta << endl;

    //Place all systems, potentials and trialfunctions here
    HarmonicOscillator potential = HarmonicOscillator();
    TrialFunction trial_function = TrialFunction(std::make_shared<HarmonicOscillator>(potential));
    RandomSystem system = RandomSystem(std::make_shared<TrialFunction>(trial_function));
    std::shared_ptr<System> pSystem = std::make_shared<RandomSystem>(system);


    Simulation simulation = Simulation(pSystem);
    simulation.initiate();

    simulation.run(Parameters::MC_cycles);

    cout << "Done!" << endl;

    return 0;
}
