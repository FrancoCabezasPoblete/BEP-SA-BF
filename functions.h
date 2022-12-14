#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono>
#include <cmath>
using namespace std;

struct Instance{
    int B, E, P, R;

    int capacidadBuses; 
    // vector de tamaño B con la posición inicial de cada bus
    vector<int> busesEstacion;

    int personasTotalPE;
    vector<int> personasPE;

    int capacidadTotalR;
    vector<int> capacidadRefugio;
    vector<int> personasRefugio;

    vector<vector<int>> dist_estacion_PtoEncuentro;
    vector<vector<int>> dist_PtoEncuentro_Refugio;
};

struct Solution{
    // Lista de buses con lista de viajes(origen,destino)
    vector<vector<pair<int,int>>> sol;
    // Lista de buses ordenada crecientemente respecto a la tiempo de evacuacion total y cantidad de viajes 
    vector<int> busByTrips;
    // Lista de buses, donde el i-esimo elemento contiene el tiempo de evacuacion total del bus i.
    vector<int> busDist;
};

void printSolution(Instance instance, Solution solution, int executionTime);
Instance initInstance(string file);
int routeDist(vector<pair<int,int>> currBus, Instance instance);
pair<Solution,Instance> initFeasibleSolution(Instance instance);
Solution randomSwap(Solution solution, Instance instance, int bus1, int bus2, uniform_real_distribution<double> distributionProb, default_random_engine generator);
Solution simulatedAnnealing(Instance instance, Solution, int q, int tmax, int qt, int qm);

#endif
