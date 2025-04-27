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

#include "include/arquivo.hpp"
#include "include/config.hpp"
#include "include/algoritmos.hpp"

Posicao Algoritmos::encontrarMelhorPosBFS(vector<vector<int>>& matriz, int linhas, int colunas, int x, int y) {
    queue<Posicao> fila;
    vector<vector<Posicao>> veioDe(linhas, vector<Posicao>(colunas, {-1, -1}));
    vector<vector<bool>> visitado(linhas, vector<bool>(colunas, false));
    vector<Posicao> direcoes = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    fila.push({x, y});
    visitado[x][y] = true;

    while (!fila.empty()) {
        Posicao atual = fila.front();
        fila.pop();

        for (const auto& direcao : direcoes) {
            int nx = atual.x + direcao.x;
            int ny = atual.y + direcao.y;

            if (nx >= 0 && ny >= 0 && nx < linhas && ny < colunas && !visitado[nx][ny]) {
                if (matriz[nx][ny] == 2 || matriz[nx][ny] == 5 || matriz[nx][ny] == 3)
                    continue;

                veioDe[nx][ny] = {atual.x, atual.y};
                visitado[nx][ny] = true;

                if (matriz[nx][ny] == 4) {
                    Posicao p = {nx, ny};
                    while (veioDe[p.x][p.y].x != x || veioDe[p.x][p.y].y != y) {
                        p = veioDe[p.x][p.y];
                        if (p.x == -1 || p.y == -1) {
                            return {x, y};
                        }
                    }
                    return p;
                }

                fila.push({nx, ny});
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (visitado[i][j] && (matriz[i][j] == 0 || matriz[i][j] == 1)) {
                Posicao p = {i, j};
                while (veioDe[p.x][p.y].x != x || veioDe[p.x][p.y].y != y) {
                    p = veioDe[p.x][p.y];
                    if (p.x == -1 || p.y == -1) {
                        return {x, y};
                    }
                }
                return p;
            }
        }
    }

    return {x, y};
}



void Algoritmos::imprimirMatriz(const vector<vector<int>>& matriz) {
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[0].size(); ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << '\n';
    }
}


bool Algoritmos::existeSaida(const vector<vector<int>> matriz, Posicao pos) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = pos.x + dx[i];
        int ny = pos.y + dy[i];

        if (nx >= 0 && ny >= 0 && nx < static_cast<int>(matriz.size()) && ny < static_cast<int>(matriz[0].size())) {
            if (matriz[nx][ny] == 0 || matriz[nx][ny] == 4) {
                return true;
            }
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
    int iteracaoLocal = 1;

    bool animalVivo = true;
    vector<Posicao> focosFogo;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) {
                focosFogo.push_back({i, j});
            }
        }
    }

    while (animalVivo && !focosFogo.empty() && iteracaoLocal <= maxIteracoes) {
        cout << "Iteracao " << iteracaoLocal << endl;

        Posicao proxima = encontrarMelhorPosBFS(matriz, linhas, colunas, posAnimal.x, posAnimal.y);

        if ((matriz[proxima.x][proxima.y] == 0 || matriz[proxima.x][proxima.y] == 1 || matriz[proxima.x][proxima.y] == 4) && (proxima.x != posAnimal.x || proxima.y != posAnimal.y)) {
            posAnimal = proxima;
            passosAnimal++;
            iteracoesParado = 0;
        } else {
            iteracoesParado++;
        }

        if (matriz[posAnimal.x][posAnimal.y] == 4) {
            encontrouAgua++;
            matriz[posAnimal.x][posAnimal.y] = 0;
        }

        vector<vector<int>> novaMatriz = matriz;
        vector<Posicao> novosFocos;

        for (auto& fogo : focosFogo) {
            int x = fogo.x;
            int y = fogo.y;

            vector<pair<int, int>> direcoesVento;
            if (VENTO_CIMA) direcoesVento.push_back({-1, 0});
            if (VENTO_BAIXO) direcoesVento.push_back({1, 0});
            if (VENTO_ESQUERDA) direcoesVento.push_back({0, -1});
            if (VENTO_DIREITA) direcoesVento.push_back({0, 1});

            for (auto [dx, dy] : direcoesVento) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < linhas && ny < colunas) {
                    if (matriz[nx][ny] == 1 && !(nx == posAnimal.x && ny == posAnimal.y)) {
                        novaMatriz[nx][ny] = 2;
                        novosFocos.push_back({nx, ny});
                    }
                }
            }
        }

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == 2) {
                    novaMatriz[i][j] = 5;
                } else if (matriz[i][j] == 5) {
                    novaMatriz[i][j] = 3;
                }
            }
        }

        matriz = novaMatriz;
        focosFogo.clear();

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == 2 || matriz[i][j] == 5) {
                    focosFogo.push_back({i, j});
                }
            }
        }

        if (iteracoesParado >= 3 && !existeSaida(matriz, posAnimal)) {
            animalVivo = false;
        }

        imprimirMatriz(matriz);
        salvarIteracaoNoArquivo(matriz, iteracaoLocal, posAnimal, animalVivo);

        if (!animalVivo) break;

        iteracaoLocal++;
    }

    if (animalVivo) {
        cout << "Animal sobreviveu!\n";
    } else {
        cout << "Animal morreu.\n";
    }

    cout << "Passos: " << passosAnimal << endl;
    cout << "Águas encontradas: " << encontrouAgua << endl;
}

void Algoritmos::salvarIteracaoNoArquivo(const vector<vector<int>>& matriz, int iteracao, Posicao posAnimal, bool animalVivo) {
    ofstream arquivoSaida("output.dat", ios::app);

    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao abrir output.dat para escrita." << endl;
        return;
    }

    arquivoSaida << "Iteracao " << iteracao << ":\n";
    arquivoSaida << "Posicao do animal: (" << (posAnimal.x+1)<< ", " << (posAnimal.y+1) << ")\n";
    arquivoSaida << "Situacao: " << (animalVivo ? "Animal vivo" : "Animal morto") << "\n";

    for (const auto& linha : matriz) {
        for (int valor : linha) {
            int visivel = (valor == 5) ? 2 : valor;
            arquivoSaida << visivel << " ";
        }
        arquivoSaida << "\n";
    }

    arquivoSaida << "\n";
    arquivoSaida.close();
}

void Algoritmos::executarPrograma() {
    ofstream limpaArquivo("output.dat", ios::trunc);
    limpaArquivo.close();

    Arquivo arq;
    vector<vector<int>> matriz = arq.getMatriz();

    if (matriz.empty()) {
        cerr << "Erro: matriz vazia!" << endl;
        return;
    }

    int linhas = matriz.size();
    int colunas = matriz[0].size();

    Posicao inicial = encontrarCaminho(matriz, linhas, colunas);

    if (inicial.x == -1 || inicial.y == -1) {
        cerr << "Erro: posicao inicial do animal nao encontrada!" << endl;
        return;
    }

    SimularIteracoes(linhas, colunas, matriz, inicial);
}
