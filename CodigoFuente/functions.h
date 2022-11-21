#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <vector>
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

Instance initInstance(string file);
int routeDist(vector<pair<int,int>> currBus, Instance instance);
Solution initFeasibleSolution(Instance instance);

#endif