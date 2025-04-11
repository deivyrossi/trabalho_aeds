#include "arquivo.hpp"
#include "algoritmos.hpp"
#include <iostream>
#include "config.hpp"

int main() {
    Arquivo arq;
    arq.processarArquivo("input.dat");
   
    vector<vector<int>>& matriz = arq.getMatriz();
    int linhas = matriz.size();
    int colunas = matriz[0].size();
  

    if (matriz.empty() || matriz[0].empty()) {
        cout << "Erro: Matriz não foi inicializada corretamente!" << endl;
        return -1;
    }
   
    Algoritmos alg;
    alg.PegarFogo(linhas,colunas, matriz);
    alg.gerarRelatorio("input.dat");

    return 0;
}
