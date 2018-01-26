#include "randomsystem.h"

RandomSystem::RandomSystem()
{
    dimension = 1;
    trial_function = TrialFunction();
}

void RandomSystem::grid_setup(int m_size, double start_alpha)
{
    alpha = start_alpha;
    size = m_size;
    vec3 r;
    r = vec3(1,0,0);

    for(int i = 0; i<size; i++){
        phi_values.push_back(trial_function.phi(r,start_alpha,beta));
        particles.push_back(Particle(r,start_alpha,1));
    }

}

void RandomSystem::propose_step(){
    vec3 step;

    for(int i = 0; i< size; i++){
        step = vec3(rand(),rand(),rand());
        particles[i].next_r = particles[i].r + step_size*step;
    }
}

double RandomSystem::check_acceptance_and_return_energy(){

    double delta_energi = 0;
    double r = rand();
    double acceptance_probability = 0;

    trial_function.get_probability(particles,size,alpha,beta);

    for(int i = 0; i< size; i++){
        r = rand();
        acceptance_probability = trial_function.get_probability_ratio(particles,size,i,alpha,beta);
        if(acceptance_probability >= r){

        }
    }
}

