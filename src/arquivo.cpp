#include "include/arquivo.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

#include "include/config.hpp"

Arquivo::Arquivo() {}

void Arquivo::processarArquivo(const string& nomeArquivo) {
    if (nomeArquivo.empty()) {
        cerr << "Nome do arquivo não pode ser vazio";
        return;
    }

    try {
        ifstream arqEntrada(nomeArquivo);
        if (!arqEntrada) {
            throw runtime_error("Arquivo não encontrado: " + nomeArquivo);
        }

        int linhas, colunas, fogoX, fogoY;
        if (!(arqEntrada >> linhas >> colunas >> fogoX >> fogoY)) {
            throw runtime_error("Erro ao ler dimensões da matriz e posição inicial do fogo");
        }

        matriz.resize(linhas, vector<int>(colunas));
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (!(arqEntrada >> matriz[i][j])) {
                    throw runtime_error("Erro ao ler valor da matriz na posição (" + to_string(i) + ", " + to_string(j) + ")");
                }
            }
        }

        cout << "Matriz carregada com sucesso!" << endl;
        cout << "Dimensões: " << linhas << "x" << colunas << endl;
        cout << "Fogo inicial em: (" << fogoX << ", " << fogoY << ")" << endl;

        cout << "Matriz lida:" << endl;
        for (const auto& linha : matriz) {
            for (int valor : linha) {
                cout << valor << " ";
            }
            cout << endl;
        }

        arqEntrada.close();
    } catch (const exception& e) {
        cerr << "Erro ao processar arquivo " << nomeArquivo << ": " << e.what() << endl;
    }
}
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

    vector<vector<int>> matriz(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (!(arquivo >> matriz[i][j])) {
                cerr << "Erro ao ler valor da matriz na posição (" << i << ", " << j << ")" << endl;
                return {};
            }
        }
    }

    return matriz;
}

