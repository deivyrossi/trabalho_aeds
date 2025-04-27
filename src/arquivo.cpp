#include "include/arquivo.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

#include "include/config.hpp"

Arquivo::Arquivo() {}


vector<vector<int>> Arquivo::getMatriz() {
    ifstream arquivo("input.dat");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir input.dat" << endl;
        return {};
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    int fogoX, fogoY;
    arquivo >> fogoX >> fogoY;

    fogoX--;
    fogoY--;

    vector<vector<int>> matriz(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (!(arquivo >> matriz[i][j])) {
                cerr << "Erro ao ler valor da matriz na posição (" << i << ", " << j << ")" << endl;
                return {};
            }
        }
    }

    
    if (fogoX >= 0 && fogoX < linhas && fogoY >= 0 && fogoY < colunas) {
        matriz[fogoX][fogoY] = 2;
    } else {
        cerr << "Posição inicial do fogo inválida: (" << fogoX << ", " << fogoY << ")" << endl;
    }

    return matriz;
}

