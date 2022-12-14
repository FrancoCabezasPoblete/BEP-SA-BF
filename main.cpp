#include "functions.h"
using namespace std;

int main(int argc, char **argv){
    auto start = chrono::high_resolution_clock::now();
    Instance instance = initInstance(argv[1]);

    // Solucion Inicial Factible
    pair<Solution,Instance> feasibleSolution = initFeasibleSolution(instance);
    Solution solution = feasibleSolution.first;
    instance = feasibleSolution.second;

    // SA+AM
    solution = simulatedAnnealing(instance, solution, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    auto stop = chrono::high_resolution_clock::now();

    printSolution(instance, solution, (chrono::duration_cast<chrono::microseconds>(stop - start)).count());

    return 0;
}
