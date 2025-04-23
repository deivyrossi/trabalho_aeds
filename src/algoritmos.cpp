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
int iteracao = 0;
int passos = 0;



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

void Algoritmos::imprimirMatriz(const std::vector<std::vector<int>>& matriz) {
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[0].size(); ++j) {
            if (i == static_cast<size_t>(posAnimal.x) && j == static_cast<size_t>(posAnimal.y)) { 
                cout << "A ";
            } else {
                int visivel = (matriz[i][j] == 5) ? 2 : matriz[i][j];
                cout << visivel << " ";
            }
        }
        cout << endl;
    }
}


bool Algoritmos::fogoAoRedor(int x, int y, int linhas, int colunas) {
    Arquivo arq;
    int numLinhas = linhas;
    int numColunas = colunas;
    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1, 1, -1, -1, 1, 1};
    
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || ny < 0 || nx >= numLinhas || ny >= numColunas) {
            continue;
        }

        int tipo = arq.getMatriz()[nx][ny];
        if (tipo == '2') {
            return true;
        }        
    }
    return false;
}

Posicao Algoritmos::encontrarCaminho(const vector<vector<int>>& matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}


void Algoritmos::SimularIteracoes(int linhas, int colunas, vector<vector<int>>& matriz, Posicao inicial) {
    posAnimal = inicial;
    int passosAnimal = 0;
    int encontrouAgua = 0;
    int iteracoesParado = 0;
    int maxIteracoes = MAX_ITERACOES;
    int iteracao = 0;
    bool animalVivo = true;

    vector<Posicao> focosFogo;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) {
                focosFogo.push_back({i, j});
            }
        }
    }

    while (animalVivo && !focosFogo.empty() && iteracao < maxIteracoes) {
        cout << "Iteração " << iteracao << endl;

     
        Posicao proxima = encontrarMelhorPos(matriz, linhas, colunas, posAnimal.x, posAnimal.y);

        if (proxima.x != posAnimal.x || proxima.y != posAnimal.y) {
            posAnimal = proxima;
            passosAnimal++;
            iteracoesParado = 0;
        } else {
            iteracoesParado++;
        }

     
        if (matriz[posAnimal.x][posAnimal.y] == 4) {
            encontrouAgua++;
            matriz[posAnimal.x][posAnimal.y] = 0;

            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
            for (int d = 0; d < 4; d++) {
                int nx = posAnimal.x + dx[d];
                int ny = posAnimal.y + dy[d];
                if (nx >= 0 && ny >= 0 && nx < linhas && ny < colunas) {
                    if (matriz[nx][ny] != 4 && matriz[nx][ny] != 3 && matriz[nx][ny != 0]) {
                        matriz[nx][ny] = 1;
                    }
                }
            }
        }

      
        vector<vector<int>> novaMatriz = matriz;
        vector<Posicao> novosFocos;

      
        for (auto& fogo : focosFogo) {
            int x = fogo.x;
            int y = fogo.y;
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};

            if (matriz[x][y] == 2 || matriz[x][y] == 5) {
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && ny >= 0 && nx < linhas && ny < colunas) {
                        if (matriz[nx][ny] == 1) { 
                            novaMatriz[nx][ny] = 2;
                            novosFocos.push_back({nx, ny});
                        }
                    }
                }
            }
        }

     
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == 2) {
                    novaMatriz[i][j] = 5;
                    novosFocos.push_back({i, j});
                } else if (matriz[i][j] == 5) {
                    novaMatriz[i][j] = 3;
                }
            }
        }

        matriz = novaMatriz;
        focosFogo = novosFocos;


for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        if (matriz[i][j] == 2 || matriz[i][j] == 5) {
            focosFogo.push_back({i, j});
        }
    }
}

        
        if (matriz[posAnimal.x][posAnimal.y] == 2) {
            Posicao fuga = encontrarMelhorPos(matriz, linhas, colunas, posAnimal.x, posAnimal.y);
            if (fuga.x != posAnimal.x || fuga.y != posAnimal.y) {
                posAnimal = fuga;
                passosAnimal++;
            } else {
                cout << "Animal morreu na iteração " << iteracao << endl;
                animalVivo = false;
                break;
            }
        }

        
        imprimirMatriz(matriz);
        salvarIteracaoNoArquivo(matriz, iteracao); 

        iteracao++;
    }

    if (animalVivo) {
        cout << "Animal sobreviveu!\n";
    }

    cout << "Passos: " << passosAnimal << endl;
    cout << "Águas encontradas: " << encontrouAgua << endl;
    cout << "Iterações parado: " << iteracoesParado << endl;
}





void Algoritmos::salvarIteracaoNoArquivo(const vector<vector<int>>& matriz, int iteracao) {
    ofstream arquivoSaida("output.dat", ios::app);

    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao abrir output.dat para escrita." << endl;
        return;
    }

    arquivoSaida << "Iteração " << iteracao << ":\n";

    for (const auto& linha : matriz) {
        for (int valor : linha) {
            int visivel;
            
            if(valor == 5){
                
                visivel = 2;
            }else{
                visivel = valor;
            }
            arquivoSaida << visivel << " ";
        }
        arquivoSaida << "\n";
    }

    arquivoSaida << "\n";
    arquivoSaida.close();
}

