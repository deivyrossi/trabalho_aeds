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
    Posicao encontrarMelhorPos(vector<vector<int>>& matriz, int linhas, int colunas, int x, int y);
    Posicao encontrarCaminho(const vector<vector<int>>& matriz, int linhas, int colunas);
    void imprimirMatriz(const vector<vector<int>>& matriz);
    void salvarIteracaoNoArquivo(const vector<vector<int>>& matriz, int iteracao, Posicao posAnimal, bool animalVivo);
    bool existeSaida(const vector<vector<int>> matriz, Posicao pos);
    void SimularIteracoes(int linhas, int colunas, vector<vector<int>>& matriz, Posicao posAnimal);
    void executarPrograma();
    

    private:
    Posicao posAnimal;

};



#endif