#include "arquivo.hpp"
#include "algoritmos.hpp"
#include <iostream>
#include "config.hpp"

int main() {
    Arquivo arq;
    arq.processarArquivo("input.dat");
    vector<vector<int>> matriz = arq.getMatriz();
    int linhas = arq.getLinhas();
    int colunas = arq.getColunas();
   
    Algoritmos alg;
    alg.PegarFogo(linhas,colunas, matriz);
    return 0;
}
