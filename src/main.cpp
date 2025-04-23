#include "algoritmos.hpp"
#include "arquivo.hpp"
#include "config.hpp"

int main() {
    // Limpa o arquivo de saída antes de iniciar a simulação
    ofstream limpar("output.dat");
    limpar.close();

    // Lê a matriz inicial do input.dat
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


    // Encontra a posição inicial do animal (posição segura com valor 0)
 
  

    // Executa a simulação completa
    alg.SimularIteracoes(linhas, colunas, matriz, posAnimal);

    return 0;
}
