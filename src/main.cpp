#include "algoritmos.hpp"
#include "arquivo.hpp"
#include "config.hpp"

int main() {
    ofstream limpar("output.dat");
    limpar.close();
    Arquivo arq;
    vector<vector<int>> matriz = arq.getMatriz();

if (matriz.empty()) {
    cerr << "Erro: matriz vazia!" << endl;
    return 1;
}

int linhas = matriz.size();
int colunas = matriz[0].size();

Algoritmos alg;
Posicao posAnimal = alg.encontrarCaminho(matriz, linhas, colunas);

if (posAnimal.x == -1 || posAnimal.y == -1) {
    cerr << "Erro: posição inicial do animal não encontrada!" << endl;
    return 1;
}


    Posicao inicial = alg.encontrarCaminho(matriz, linhas, colunas);


    alg.SimularIteracoes(linhas, colunas, matriz, inicial);

    return 0;
}
