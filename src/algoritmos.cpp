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

//teste





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

    int xAnimal = 0, yAnimal = 0;
    Posicao caminhoAnimal = encontrarCaminho(matriz, linhas, colunas);
    xAnimal = caminhoAnimal.x;
    yAnimal = caminhoAnimal.y;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) {
                novaMatriz[i][j] = 3;

               
                if (!VENTO_CIMA && !VENTO_BAIXO && !VENTO_ESQUERDA && !VENTO_DIREITA) {
                    if (i > 0 && matriz[i - 1][j] == 1) novaMatriz[i - 1][j] = 2;
                    if (i < linhas - 1 && matriz[i + 1][j] == 1) novaMatriz[i + 1][j] = 2;
                    if (j > 0 && matriz[i][j - 1] == 1) novaMatriz[i][j - 1] = 2;
                    if (j < colunas - 1 && matriz[i][j + 1] == 1) novaMatriz[i][j + 1] = 2;
                }

                if (VENTO_CIMA && i > 0 && matriz[i - 1][j] == 1) novaMatriz[i - 1][j] = 2;
                if (VENTO_BAIXO && i < linhas - 1 && matriz[i + 1][j] == 1) novaMatriz[i + 1][j] = 2;
                if (VENTO_ESQUERDA && j > 0 && matriz[i][j - 1] == 1) novaMatriz[i][j - 1] = 2;
                if (VENTO_DIREITA && j < colunas - 1 && matriz[i][j + 1] == 1) novaMatriz[i][j + 1] = 2;
                imprimirMatriz(matriz);
            }
        }
    }

    matriz = novaMatriz;

    if (matriz[xAnimal][yAnimal] == 2 || matriz[xAnimal][yAnimal] == 3) {
        cout << "O animal morreu." << endl;
        return;
    }


    if (matriz[xAnimal][yAnimal] == 4) {
        matriz[xAnimal][yAnimal] = 0;
        if (xAnimal > 0) matriz[xAnimal - 1][yAnimal] = 1;
        if (xAnimal < linhas - 1) matriz[xAnimal + 1][yAnimal] = 1;
        if (yAnimal > 0) matriz[xAnimal][yAnimal - 1] = 1;
        if (yAnimal < colunas - 1) matriz[xAnimal][yAnimal + 1] = 1;
    }
}