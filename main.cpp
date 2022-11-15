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
    Instance instancia;
    int delimeterPos;

    // Inicializar instancia
    // Bus
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instancia.B = stoi(instanceLine.substr(0 , delimeterPos));
    instancia.capacidadBuses = stoi(instanceLine.substr(delimeterPos + 2));

    // Estaciones
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instancia.E = stoi(instanceLine.substr(0 , delimeterPos));

    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instancia.busesEstacion.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();

    // Puntos de Encuentro
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instancia.P = stoi(instanceLine.substr(0 , delimeterPos));

    instanceLine = instanceLine.substr(delimeterPos + 2);
    delimeterPos = instanceLine.find(":");
    instancia.personasTotalPE = stoi(instanceLine.substr(0 , delimeterPos));

    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instancia.personasPE.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();


    // Refugios
    getline(instanceFile, instanceLine);
    delimeterPos = instanceLine.find(":");
    instancia.R = stoi(instanceLine.substr(0 , delimeterPos));

    instanceLine = instanceLine.substr(delimeterPos + 2);
    delimeterPos = instanceLine.find(":");
    instancia.capacidadTotalR = stoi(instanceLine.substr(0 , delimeterPos));
    
    instanceParsedStream.str(instanceLine.substr(delimeterPos + 2));
    while(getline(instanceParsedStream, instanceParsed, ' '))
        instancia.capacidadRefugio.push_back(stoi(instanceParsed));
    instanceParsedStream.clear();

    getline(instanceFile, instanceLine);

    // Matriz (Estaciones -> Puntos de encuentro) 
    for(int i = 0; i < instancia.E; i++){
        getline(instanceFile, instanceLine);
        instanceParsedStream.str(instanceLine.substr(instanceLine.find(":") + 2));
        instancia.dist_estacion_PtoEncuentro.push_back(vector<int> {});
        for(int j = 0; getline(instanceParsedStream, instanceParsed, ' ') && (j < instancia.P); j++)
            instancia.dist_estacion_PtoEncuentro[i].push_back(stoi(instanceParsed));
        instanceParsedStream.clear();
    }

    getline(instanceFile, instanceLine);

    // Matriz (Puntos de encuentro -> Refugio)
    for(int i = 0; i < instancia.P; i++){
        getline(instanceFile, instanceLine);
        instanceParsedStream.str(instanceLine.substr(instanceLine.find(":") + 2));
        instancia.dist_PtoEncuentro_Refugio.push_back(vector<int> {});
        for(int j = 0; getline(instanceParsedStream, instanceParsed, ' ') && (j < instancia.R); j++)
            instancia.dist_PtoEncuentro_Refugio[i].push_back(stoi(instanceParsed));
        instanceParsedStream.clear();
    }
    instanceFile.close();

    /*
    cout << "B: " << instancia.B << " E: " << instancia.E << " P: " << instancia.P << " R: " << instancia.R << endl; 
    cout << "CapacidadBuses: " << instancia.capacidadBuses << " PersonasTotalPE: " << instancia.personasTotalPE << " CapacidadTotalR: " << instancia.capacidadTotalR << endl; 
    cout << "BusesEstacion: ";
    for(int i = 0; i<instancia.E; i++)
        cout << instancia.busesEstacion[i] << "[" << i << "] ";
    cout << endl;
    cout << "PersonasPE: ";
    for(int i = 0; i<instancia.P; i++)
        cout << instancia.personasPE[i] << "[" << i << "] ";
    cout << endl;
    cout << "CapacidadRefugio: ";
    for(int i = 0; i<instancia.R; i++)
        cout << instancia.capacidadRefugio[i] << "[" << i << "] ";
    cout << endl;
    cout << "Distancias Estación a Puntos de encuentro: " << endl;
    for(int i = 0; i < instancia.E; i++){
        cout << "Estación[" << i << "]: ";
        for(int j = 0; j < instancia.P; j++)
            cout << instancia.dist_estacion_PtoEncuentro[i][j] << " ";
        cout << endl;
    }
    cout << "Distancias Puntos de encuentro a Refugio: " << endl;
    for(int i = 0; i < instancia.P; i++){
        cout << "Punto de encuentro[" << i << "]: ";
        for(int j = 0; j < instancia.R; j++)
            cout << instancia.dist_PtoEncuentro_Refugio[i][j] << " ";
        cout << endl;
    }
    */

    return instancia;
}

int main(int argc, char **argv){
    Instance instancia = initInstance(argv[1]);

    return 0;
}