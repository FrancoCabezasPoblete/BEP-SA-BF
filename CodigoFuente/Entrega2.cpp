#include "functions.h"
using namespace std;

int main(int argc, char **argv){
    Instance instance = initInstance(argv[1]);

    // Solucion Inicial Factible
    Solution solution = initFeasibleSolution(instance);
    
    // SA+AM #TODO

    return 0;
}
