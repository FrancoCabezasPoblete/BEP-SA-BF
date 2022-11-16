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

    vector<vector<int>> dist_estacion_PtoEncuentro;
    vector<vector<int>> dist_PtoEncuentro_Refugio;
};

struct Solution{
    // Lista de buses con lista de viajes(origen,destino)
    vector<vector<pair<int,int>>> sol;
    // Lista de buses ordenada crecientemente respecto a la cantidad de viajes y su distancia total
    vector<int> busByTrips;
};

Instance initInstance(string file);
int routeDist(vector<pair<int,int>> currBus, Instance instance);
Solution initFeasibleSolution(Instance instance);

#endif