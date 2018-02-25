#include "system.h"


System::System()
{
    r.resize(Parameters::dimension,Parameters::N);
    next_r.resize(Parameters::dimension,Parameters::N);
    distance.resize(Parameters::N,Parameters::N);
    next_distance.resize(Parameters::N,Parameters::N);

    //Temp variables
    temp_r.resize(Parameters::dimension);
    temp_value = 0;
    temp_value2 = 0;

    //Sets the seed of rand() to the current time
    srand(time(NULL));
}

void System::make_grid(double m_alpha){
    alpha = m_alpha;
    //Sets all positions to a random position [-1,1]
    //r = Eigen::MatrixXd::Random(Parameters::dimension,Parameters::N);

    r = Eigen::MatrixXd::Constant(Parameters::dimension,Parameters::N,0.05);
    next_r = r;
    update();
}

//Updates the distances between the particles
void System::update(){
    temp_value = 0;
    for(int i = 0; i<N;i++){
        for(int j = 0;j<i;j++){
            temp_value = (r.col(i)- r.col(j)).norm();
            distance(i,j) = temp_value;
            distance(j,i) = temp_value;
        }
    }
}

void System::make_move_and_update(const int move){
    //Makes a random move
    for(int i = 0; i<dimension; i++){
        next_r(move,i) += dx*((double)rand()/RAND_MAX - 0.5);
    }

    temp_value = 0;
    //Updates the distance matrix after move
    for(int i = 0;i<N;i++){
        if(i != move){
            temp_value = (r.col(move)- r.col(i)).norm();
            next_distance(i,move) = temp_value;
            next_distance(move,i) = temp_value;
        }
    }
}

double System::check_acceptance_and_return_energy(){
    //Random value [0,1]
    temp_value = (double)rand()/RAND_MAX;

    //If r is less than the acceptance prob, r is updated to the new r
    if(temp_value <= get_probability_ratio()){
        r = next_r;
    }
    return get_local_energy();
}


double System::phi_exponant(const Eigen::VectorXd &r){
    temp_value = 0;

    for(int i = 0;i<dimension;i++){
        if(i == 2){
            //Multiplices beta to the z-componant
            temp_value += beta*r(i)*r(i);
        }
        else{
            temp_value += r(i)*r(i);
        }
    }
    return -alpha*temp_value;
}

double System::get_probability_ratio(){
    temp_value = get_probability(); //Stores the probability before move
    temp_value2 = 0; //Stores the probability of move
    for(int i = 0; i<N;i++){
        temp_r = next_r.col(i);
        temp_value2 += phi_exponant(temp_r);
    }
    return exp(2*temp_value2)/temp_value;
}

double System::get_wavefunction(){
    temp_value = 0; //Stores the exponants of phi
    for(int i = 0;i<N;i++){
        temp_r = r.col(i);
        temp_value += phi_exponant(temp_r);
    }
    return exp(temp_value);
}

double System::get_probability(){
    temp_value = get_wavefunction();
    return temp_value*temp_value;
}


double System::get_local_energy(){
    return 0;
}




