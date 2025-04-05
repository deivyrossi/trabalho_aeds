#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

#include "arquivo.hpp"
#include "config.hpp"
#include "algoritmos.hpp"



Posicao Algoritmos::encontrarMelhorPos(vector<vector<int>>& matriz, int linhas, int colunas, int x, int y) {
    vector<Posicao> direcoes = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    Posicao melhorPos = {x, y};
    int melhorValor = 3;

    for (const auto& direcao : direcoes) {
        int nx = x + direcao.x;
        int ny = y + direcao.y;

        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas) {
            int valor = matriz[nx][ny];

            if (valor == 4) return {nx, ny};
            if ((valor == 0 || valor == 1) && melhorValor == 3) {
                melhorPos = {nx, ny};
                melhorValor = valor;
            }
        }
    }

    return melhorPos;
}

void Algoritmos::imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& elemento : linha) {
            cout << elemento << " ";
        }
        cout << endl;
    }
}

Posicao Algoritmos::encontrarCaminho(const vector<vector<int>>& matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}


void Algoritmos::PegarFogo(int linhas, int colunas, vector<vector<int>>& matriz) {
    vector<vector<int>> novaMatriz = matriz;

    int iteracao = 0; 
    while (true) { 
        cout << "Iteração: " << iteracao << endl;
        imprimirMatriz(matriz);
        cout << endl;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == 2) { 
                    novaMatriz[i][j] = 3;

                    if (i > 0 && matriz[i-1][j] == 1) novaMatriz[i-1][j] = 2;
                    if (i < linhas - 1 && matriz[i+1][j] == 1) novaMatriz[i+1][j] = 2;
                    if (j > 0 && matriz[i][j-1] == 1) novaMatriz[i][j-1] = 2;
                    if (j < colunas - 1 && matriz[i][j+1] == 1) novaMatriz[i][j+1] = 2;
                }
            }
        }

        if (matriz == novaMatriz) break;
        matriz = novaMatriz;
        iteracao++;
    }
}

