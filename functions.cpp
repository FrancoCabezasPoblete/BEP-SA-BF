#include "functions.h"
#include <fstream>
#include <sstream>
using namespace std;

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
    for(int e = 0; getline(instanceParsedStream, instanceParsed, ' '); e++)
        for(int b = 0; b < stoi(instanceParsed); b++)
            instance.busesEstacion.push_back(e);
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

    /* Print */
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
    cout << "PtoEncuentro:\t";
    for(int i = 0; i < instance.P; i++)
            cout << "[" << i+1 << "]\t";
    cout << endl;
    for(int i = 0; i < instance.E; i++){
        cout << "Estación[" << i+1 << "]:\t";
        for(int j = 0; j < instance.P; j++)
            cout << instance.dist_estacion_PtoEncuentro[i][j] << "\t";
        cout << endl;
    }
    cout << "Distancias Puntos de encuentro a Refugio: " << endl;
    cout << "Refugio:\t\t";
    for(int i = 0; i < instance.R; i++)
            cout << "[" << i+1 << "]\t";
    cout << endl;
    for(int i = 0; i < instance.P; i++){
        cout << "PtoEncuentro[" << i+1 << "]:\t";
        for(int j = 0; j < instance.R; j++)
            cout << instance.dist_PtoEncuentro_Refugio[i][j] << "\t";
        cout << endl;
    }
    /**/

    return instance;
}

int routeDist(vector<pair<int,int>> currBus, Instance instance){
    int sumDist = 0;
    // Viaje incial (Estación -> PtoEncuentro)
    if(int(currBus.size()) > 0)
        sumDist += instance.dist_estacion_PtoEncuentro[currBus[0].first][currBus[0].second];
    // Segundo Viaje (PtoEncuentro -> Refugio)
    if(int(currBus.size()) > 1)
        sumDist += instance.dist_PtoEncuentro_Refugio[currBus[1].first][currBus[1].second];
    
    for(int i = 2; i < int(currBus.size()); i++){
        // i Viaje de retorno (Refugio -> PtoEncuentro)
        sumDist += instance.dist_PtoEncuentro_Refugio[currBus[i].first][currBus[i-1].second];

        // i Viaje (PtoEncuentro -> Refugio)
        sumDist += instance.dist_PtoEncuentro_Refugio[currBus[i].first][currBus[i].second];
    }

    return sumDist;
}

Solution initFeasibleSolution(Instance instance){
    Solution solution;
    int nearestTrip;
    int currPos;
    vector<pair<int,int>> currBus {};
    for(int i = 0; i < instance.B; i++){
        solution.sol.push_back(vector<pair<int,int>> {});
        solution.busByTrips.push_back(i);
    }

    while(instance.personasTotalPE > 0){
        currBus = solution.sol[solution.busByTrips[0]];
        if(currBus.size() != 0){ // Viaje (PtoEncuentro -> Refugio) más cercano
            currPos = currBus[currBus.size()-1].second;
            
            if(currBus.size() > 1){ // Viaje de retorno (Refugio -> PtoEncuentro) más cercano
                for(int pe = 0; pe < instance.P; pe++){
                    if(instance.personasPE[pe] > 0){
                        nearestTrip = pe;
                        break;
                    }
                }
                for(int pe = nearestTrip+1; pe < instance.P; pe++)
                    if((instance.dist_PtoEncuentro_Refugio[pe][currPos] < instance.dist_PtoEncuentro_Refugio[nearestTrip][currPos]) && (instance.personasPE[pe] > 0))
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
                if((instance.dist_PtoEncuentro_Refugio[currPos][r] < instance.dist_PtoEncuentro_Refugio[currPos][nearestTrip]) && (instance.capacidadRefugio[r] >= instance.capacidadBuses))
                    nearestTrip = r;

            instance.capacidadRefugio[nearestTrip] -= instance.capacidadBuses;
            instance.capacidadTotalR -= instance.capacidadBuses;
            currBus.push_back(make_pair(currPos,nearestTrip));
        } else { // Viaje incial (Estación -> PtoEncuentro) más cercano
            currPos = instance.busesEstacion[solution.busByTrips[0]];

            for(int pe = 0; pe < instance.P; pe++){
                if(instance.personasPE[pe] > 0){
                    nearestTrip = pe;
                    break;
                }
            }
            for(int pe = nearestTrip+1; pe < instance.P; pe++)
                if((instance.dist_estacion_PtoEncuentro[currPos][pe] < instance.dist_estacion_PtoEncuentro[currPos][nearestTrip]) && instance.personasPE[pe] > 0)
                    nearestTrip = pe;
            
            instance.personasPE[nearestTrip] -= instance.capacidadBuses;
            instance.personasTotalPE -= instance.capacidadBuses;
            currBus.push_back(make_pair(currPos,nearestTrip));
        }
        solution.sol[solution.busByTrips[0]] = currBus;
        // Actualizar orden de buses
        for(int b = instance.B-1, distCurrBus, distBusB; b > 0; b--){
            distCurrBus = routeDist(currBus, instance);
            distBusB = routeDist(solution.sol[solution.busByTrips[b]], instance);
            if(distCurrBus > distBusB){
                solution.busByTrips.insert(solution.busByTrips.begin()+b+1, solution.busByTrips[0]);
                solution.busByTrips.erase(solution.busByTrips.begin());
                break;
            } else if(distCurrBus == distBusB){
                if(currBus.size() > solution.sol[solution.busByTrips[b]].size()) 
                    solution.busByTrips.insert(solution.busByTrips.begin()+b+1, solution.busByTrips[0]);
                else
                    solution.busByTrips.insert(solution.busByTrips.begin()+b, solution.busByTrips[0]);
                solution.busByTrips.erase(solution.busByTrips.begin());
                break;
            }
        }
    }

    /* Print 
    cout << "Solución:\n";
    for(int i = 0; i < instance.B; i++){
        cout << "Bus[" << i+1 << "]: ";
        for(int j = 0; j < int(solution.sol[i].size()); j++){
            cout << "(" << solution.sol[i][j].first+1 << ", " << solution.sol[i][j].second+1 << ")";
            if(j+1 < int(solution.sol[i].size())){
                cout << "->";
            }
        }
        cout << endl;
    }
    cout << "Bus con mayor ruta: " << solution.busByTrips[instance.B-1]+1 << endl;
    cout << "Mayor ruta: " << routeDist(solution.sol[solution.busByTrips[instance.B-1]], instance) << endl;
    for(int i = 0; i < instance.B; i++)
        cout << "Distancia ruta bus[" << i+1 <<"]: " << routeDist(solution.sol[i], instance) << endl;
    */

    return solution;
}