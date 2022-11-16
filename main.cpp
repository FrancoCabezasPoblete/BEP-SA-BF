#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Instance{
    int B, E, P, R;

    int capacidadBuses; 
    vector<int> busesEstacion;

    int personasTotalPE;
    vector<int> personasPE;

    int capacidadTotalR;
    vector<int> capacidadRefugio;

    vector<vector<int>> dist_estacion_PtoEncuentro;
    vector<vector<int>> dist_PtoEncuentro_Refugio;
};

Instance initInstance(string file){
    string instanceLine, instanceParsed;
    stringstream instanceParsedStream;
    ifstream instanceFile(file);
    Instance instance;
    int delimeterPos;

    // Bus
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instance.B = stoi(instanceLine.substr(0 , delimeterPos));
    instance.capacidadBuses = stoi(instanceLine.substr(delimeterPos + 2));

    // Estaciones
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instance.E = stoi(instanceLine.substr(0 , delimeterPos));

    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instance.busesEstacion.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();

    // Puntos de Encuentro
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instance.P = stoi(instanceLine.substr(0 , delimeterPos));

    instanceLine = instanceLine.substr(delimeterPos + 2);
    delimeterPos = instanceLine.find(":");
    instance.personasTotalPE = stoi(instanceLine.substr(0 , delimeterPos));

    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instance.personasPE.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();


    // Refugios
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instance.R = stoi(instanceLine.substr(0 , delimeterPos));

    instanceLine = instanceLine.substr(delimeterPos + 2);
    delimeterPos = instanceLine.find(":");
    instance.capacidadTotalR = stoi(instanceLine.substr(0 , delimeterPos));
    
    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instance.capacidadRefugio.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();

    getline(instanceFile, instanceLine);

    // Matriz (Estaciones -> Puntos de encuentro) 
    for(int i = 0; i < instance.E; i++){
        getline(instanceFile, instanceLine);
        instanceParsedStream.str(instanceLine.substr(instanceLine.find(":") + 2));
        instance.dist_estacion_PtoEncuentro.push_back(vector<int> {});
        for(int j = 0; getline(instanceParsedStream, instanceParsed, ' ') && (j < instance.P); j++)
            instance.dist_estacion_PtoEncuentro[i].push_back(stoi(instanceParsed));
        instanceParsedStream.clear();
    }

    getline(instanceFile, instanceLine);

    // Matriz (Puntos de encuentro -> Refugio)
    for(int i = 0; i < instance.P; i++){
        getline(instanceFile, instanceLine);
        instanceParsedStream.str(instanceLine.substr(instanceLine.find(":") + 2));
        instance.dist_PtoEncuentro_Refugio.push_back(vector<int> {});
        for(int j = 0; getline(instanceParsedStream, instanceParsed, ' ') && (j < instance.R); j++)
            instance.dist_PtoEncuentro_Refugio[i].push_back(stoi(instanceParsed));
        instanceParsedStream.clear();
    }
    instanceFile.close();

    /* Print
    cout << "B: " << instance.B << " E: " << instance.E << " P: " << instance.P << " R: " << instance.R << endl; 
    cout << "CapacidadBuses: " << instance.capacidadBuses << " PersonasTotalPE: " << instance.personasTotalPE << " CapacidadTotalR: " << instance.capacidadTotalR << endl; 
    cout << "BusesEstacion: ";
    for(int i = 0; i<instance.E; i++)
        cout << instance.busesEstacion[i] << "[" << i+1 << "] ";
    cout << endl;
    cout << "PersonasPE: ";
    for(int i = 0; i<instance.P; i++)
        cout << instance.personasPE[i] << "[" << i+1 << "] ";
    cout << endl;
    cout << "CapacidadRefugio: ";
    for(int i = 0; i<instance.R; i++)
        cout << instance.capacidadRefugio[i] << "[" << i+1 << "] ";
    cout << endl;
    cout << "Distancias Estación a Puntos de encuentro: " << endl;
    for(int i = 0; i < instance.E; i++){
        cout << "Estación[" << i+1 << "]: ";
        for(int j = 0; j < instance.P; j++)
            cout << instance.dist_estacion_PtoEncuentro[i][j] << " ";
        cout << endl;
    }
    cout << "Distancias Puntos de encuentro a Refugio: " << endl;
    for(int i = 0; i < instance.P; i++){
        cout << "Punto de encuentro[" << i+1 << "]: ";
        for(int j = 0; j < instance.R; j++)
            cout << instance.dist_PtoEncuentro_Refugio[i][j] << " ";
        cout << endl;
    }
    */

    return instance;
}

int main(int argc, char **argv){
    Instance instance = initInstance(argv[1]);

    // Lista de buses con lista de viajes(origen,destino)
    vector<vector<pair<int,int>>> solution;
    // Lista de buses ordenada crecientemente respecto a la cantidad de viajes y su distancia total
    vector<int> busByTrips;
    int nearestTrip;
    int currPos;
    vector<pair<int,int>> currBus;
    for(int i = 0; i < instance.B; i++){
        solution.push_back(vector<pair<int,int>> {});
        busByTrips.push_back(i);
    }

    // Solucion Inicial Factible
    currBus = solution[busByTrips[0]];
    if(currBus.size() != 0){ // Viaje (PtoEncuentro -> Refugio) más cercano
        if(currBus.size() > 2){ // Viaje de retorno (Refugio -> Refugio) más cercano

        }

        currPos = currBus[currBus.size()-1].second;

        for(int r = 0; r < instance.R; r++){
            if(instance.capacidadRefugio[r] >= instance.capacidadBuses)
                    nearestTrip = r;
            break;
        }
        for(int r = nearestTrip+1; r < instance.R; r++)
            if(instance.dist_PtoEncuentro_Refugio[currPos][r] < instance.dist_PtoEncuentro_Refugio[currPos][nearestTrip])
                nearestTrip = r;

        instance.capacidadRefugio[nearestTrip] -= instance.capacidadBuses;
        currBus.push_back(make_pair(currPos,nearestTrip));
    } else { // Viaje incial (Estación -> PtoEncuentro) más cercano

    }

    return 0;
}
