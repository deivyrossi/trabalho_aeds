#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP


#include <vector>
#include <string>

using namespace std;

class Arquivo {
public:
    vector<vector<int>> matriz;

    void processarArquivo(const string& nomeArquivo);
    Arquivo();

    vector<vector<int>>& getMatriz();
};

#endif
