#include "algoritmos.hpp"
#include "arquivo.hpp"
#include "config.hpp"

int main() {
    Arquivo arq;
    arq.processarArquivo("input.dat");
    
    Algoritmos alg;
    alg.executarPrograma();
    
    return 0;
}
