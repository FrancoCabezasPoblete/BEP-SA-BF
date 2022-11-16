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

int routeDist(vector<pair<int,int>> currBus, Instance instance){
    // Viaje incial (Estación -> PtoEncuentro)
    int sumDist = instance.dist_estacion_PtoEncuentro[currBus[0].first][currBus[0].second];
    // Segundo Viaje (PtoEncuentro -> Refugio)
    sumDist += instance.dist_PtoEncuentro_Refugio[currBus[1].first][currBus[1].second];
    
    for(int i = 2; i < int(currBus.size()); i++){
        // i Viaje de retorno (Refugio -> PtoEncuentro)
        sumDist += instance.dist_PtoEncuentro_Refugio[currBus[i].first][currBus[i-1].second];
        // i Viaje (PtoEncuentro -> Refugio)
        sumDist += instance.dist_PtoEncuentro_Refugio[currBus[i].first][currBus[i].second];
    }

    return sumDist;
}

int main(int argc, char **argv){
    //Instance instance = initInstance(argv[1]);
    Instance instance = initInstance("instancias/InstanceBEP-1-4-2-4.txt");

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
    while(instance.personasTotalPE > 0){
        currBus = solution[busByTrips[0]];
        if(currBus.size() != 0){ // Viaje (PtoEncuentro -> Refugio) más cercano
            currPos = currBus[currBus.size()-1].second;
            
            if(currBus.size() > 2){ // Viaje de retorno (Refugio -> Refugio) más cercano
                for(int pe = 0; pe < instance.P; pe++){
                    if(instance.personasPE[pe] > 0){
                        nearestTrip = pe;
                        break;
                    }
                }
                for(int pe = nearestTrip+1; pe < instance.P; pe++)
                    if(instance.dist_PtoEncuentro_Refugio[pe][currPos] < instance.dist_PtoEncuentro_Refugio[nearestTrip][currPos])
                        nearestTrip = pe;
                
                instance.personasPE[nearestTrip] -= instance.capacidadBuses;
                instance.personasTotalPE -= instance.capacidadBuses;
                currPos = nearestTrip;
            }
            
            for(int r = 0; r < instance.R; r++){
                if(instance.capacidadRefugio[r] >= instance.capacidadBuses){
                    nearestTrip = r;
                    break;
                }
            }
            for(int r = nearestTrip+1; r < instance.R; r++)
                if(instance.dist_PtoEncuentro_Refugio[currPos][r] < instance.dist_PtoEncuentro_Refugio[currPos][nearestTrip])
                    nearestTrip = r;

            instance.capacidadRefugio[nearestTrip] -= instance.capacidadBuses;
            instance.capacidadTotalR -= instance.capacidadBuses;
            currBus.push_back(make_pair(currPos,nearestTrip));
            cout << currBus.size() << endl;

        } else { // Viaje incial (Estación -> PtoEncuentro) más cercano
            currPos = 0; // TODO: Definir estaciones para los buses

            for(int pe = 0; pe < instance.P; pe++){
                if(instance.personasPE[pe] > 0){
                    nearestTrip = pe;
                    break;
                }
            }
            for(int pe = nearestTrip+1; pe < instance.P; pe++)
                if(instance.dist_estacion_PtoEncuentro[currPos][pe] < instance.dist_estacion_PtoEncuentro[currPos][nearestTrip])
                    nearestTrip = pe;
            
            instance.personasPE[nearestTrip] -= instance.capacidadBuses;
            instance.personasTotalPE -= instance.capacidadBuses;
            currBus.push_back(make_pair(currPos,nearestTrip));
        }
        solution[busByTrips[0]] = currBus;
        // Actualizar orden de buses
        for(int b = instance.B-1; b > 0; b--){
            if(currBus.size() > solution[busByTrips[b]].size()){
                busByTrips.insert(busByTrips.begin()+b+1,busByTrips[0]);
                busByTrips.erase(busByTrips.begin());
                break;
            } else if(currBus.size() == solution[busByTrips[b]].size()){
                if(routeDist(currBus, instance) > routeDist(solution[busByTrips[b]], instance)) 
                    busByTrips.insert(busByTrips.begin()+b+1,busByTrips[0]);
                else
                    busByTrips.insert(busByTrips.begin()+b,busByTrips[0]);
                busByTrips.erase(busByTrips.begin());
                break;
            }
        }
    }

    cout << "Solución:\n";
    for(int i = 0; i < instance.B; i++){
        cout << "Bus[" << i+1 << "]: ";
        for(int j = 0; j < int(solution[i].size()); j++)
            cout << "(" << solution[i][j].first << ", " << solution[i][j].second << ")->";
        cout << endl;
    }

    return 0;
}
