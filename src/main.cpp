#include "include/arquivo.hpp"
#include "include/algoritmos.hpp"
#include "include/config.hpp"

int main() {
    Arquivo arq;
    arq.processarArquivo("input.dat");
    
    Algoritmos alg;
    alg.executarPrograma();
    
    return 0;
}
