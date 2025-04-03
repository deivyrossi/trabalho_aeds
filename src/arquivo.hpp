#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Arquivo {
public:
    vector<vector<int>> matriz;
    int linhas;
    int colunas;
    void processarArquivo(const string& nomeArquivo);
    vector<vector<int>> getMatriz() const;
    int getLinhas() const;
    int getColunas() const;
};

#endif
