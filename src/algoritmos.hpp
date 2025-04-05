#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <stdexcept>
#include <sstream>

using namespace std;

struct Posicao {
    int x;
    int y;
};


class Algoritmos {
public:
    void PegarFogo(int linhas, int colunas, vector<vector<int>>& matriz);
    Posicao encontrarMelhorPos(vector<vector<int>>& matriz, int linhas, int colunas, int x, int y);
    Posicao encontrarCaminho(const vector<vector<int>>& matriz, int linhas, int colunas);
    void imprimirMatriz(const vector<vector<int>>& matriz);
};

#endif