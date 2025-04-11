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

void Algoritmos::imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& elemento : linha) {
            cout << elemento << " ";
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


void Algoritmos::PegarFogo(int linhas, int colunas, vector<vector<int>>& matriz) {
    vector<vector<int>> novaMatriz = matriz;

    int iteracao = 0; 
    while (true) { 
        cout << "Iteração: " << iteracao << endl;
        imprimirMatriz(matriz);
        cout << endl;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
            

                if (i > 0 && matriz[i-1][j] == 1) novaMatriz[i-1][j] = 2;
                if (i < linhas - 1 && matriz[i+1][j] == 1) novaMatriz[i+1][j] = 2;
                if (j > 0 && matriz[i][j-1] == 1) novaMatriz[i][j-1] = 2;
                if (j < colunas - 1 && matriz[i][j+1] == 1) novaMatriz[i][j+1] = 2;
               
                    
                
            }
            
        }


        

        if (matriz == novaMatriz) break;
        matriz = novaMatriz;
        iteracao++;
    }

}

void Algoritmos::AnimalCaminho(int linhas, int colunas, vector<vector<int>> matriz, int xIni, int yIni){

    if(passos == 0){
        home = {xIni, yInix};
    }

    vector<vector<int>> visitado[linhas][colunas];
    queue <int> filaX;
    queue <int> filaY;

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(matriz[i][j] == 4){
                fila.push({i,j});
                visitado[i][j] = false;
            }
        }
    }

    filaX.push(xIni);
    filaY.push(yIni);

    visitado[xIni][yIni] = true;


    int dx[] = {-1, -1, 0, 0};
    int dy[] = {0, 0, -1, -1};

    int nx, ny;
    

    while(!filaX.empty() && !filaY.empty()){
        int x = filaX.front();
        int y = filaY.front();

        filaX.pop();
        filaY.pop();
    }

    for(int i = 0; i < 4; i++){
        nx = x + dx[i];
        nx = y + dy[i];

        if (nx < 0 || ny < 0 || nx >= linhas || ny >= colunas) {
            continue;
        }

    }







}

void Algoritmos::gerarRelatorio(const string &nomeArquivoEntrada) {
    Arquivo arq;
    
    string nomeArquivoSaida = "output.dat";
    ifstream arquivoEntrada(nomeArquivoEntrada);    
    
    ofstream arquivoSaida(nomeArquivoSaida);
    if (!arquivoSaida) {
        cerr << "Erro ao criar arquivo de saída: " << nomeArquivoSaida << endl;
        return;
    }

    arquivoSaida << "Relatório de Saída:\n";

    arquivoSaida << "\n\n";
    arquivoSaida << "Matriz final:\n";
    for (const auto &linha : arq.getMatriz()) {
        for (int valor : linha) {
            arquivoSaida << valor << " ";
        }
        arquivoSaida << endl;
    }
    arquivoSaida << "\n\n";
    
    arquivoSaida << "- Total de passos: " << iteracao << " passos." << endl;
    arquivoSaida.close();
    cout << "Relatório gerado em: " << nomeArquivoSaida << endl;
}

