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


void PegarFogo(int linhas, int colunas, vector<vector<int>>& matriz){
    vector<vector<int>> novaMatriz = matriz;
    

    int xAnimal, yAnimal = 0;
    encontrarCaminho(xAnimal, yAnimal);

    while(iterator != matriz.end()){
        if(matriz[i][j] !== 2){
            return -1;
        }
    }

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(matriz[i][j] == 2){
                matriz[i][j] = 3;
                contagem++;
            }


            if(!VENTO_CIMA && !VENTO_BAIXO && !VENTO_ESQUERDA && !VENTO_DIREITA){
                if(i > 0 && matriz[i-1][j] == 1){
                    novaMatriz[i-1][j] = 2;
                }
                if(i < linhas - 1 && matriz[i+1][j] == 1){
                    novaMatriz[i+1][j] = 2;
                }
                if(j > 0 && matriz[i][j-1] == 1){
                    novaMatriz[i][j-1] = 2;
                }
                if(j < colunas - 1 && matriz[i][j+1] == 1){
                    novaMatriz[i][j+1] = 2;
                }
            }

            if(VENTO_CIMA && i > 0 && matriz[i-1][j] == 1){
                novaMatriz[i-1][j] = 2;
            }
            if(VENTO_BAIXO && i < linhas - 1 && matriz[i+1][j] == 1){
                novaMatriz[i+1][j] = 2;
            }
            if(VENTO_ESQUERDA && j > 0 && matriz[i][j-1] == 1){
                novaMatriz[i][j-1] = 2;
            }
            if(VENTO_DIREITA && j < colunas - 1 && matriz[i][j+1] == 1){
                novaMatriz[i][j+1] = 2;
            }

            novaMatriz[i][j] = 3;
        }
    }






}

void inicializarMatriz(vector<vector<int>>& matriz, int linhas, int colunas, int valorInicial) {
    matriz.resize(linhas, vector<int>(colunas, valorInicial));
}


void encontrarCaminho(int i, int j){
    for(int i = 0; i<=matriz.size(); i++){
        for(int j = 0 j<=matriz.size(); j++){
            if(matriz[i][j] == 0){
                return [i, j];
            }

            return [-1, -1];
        
        }
    }
}

void encontrarMelhorOp(){
    list<int> opcoes;
    if(matriz[i][j] == 4){
        return [i, j];
    }

    int dx = {0, 0, -1, 1};
    int dy = {1, -1, 0, 0};

    for(int i = 0; i<=matriz.size(); i++){
        for(int j = 0 j<=matriz.size(); j++){
            int nx = i + dx[k];
            int ny = j + dy[k];
            if(nx < 0 || nx <= matriz.size() || ny < 0 || ny <= matriz[0].size()){
                if(matriz[nx][ny] == 4){
                    return [nx, ny];
                }
                if(matriz[nx][ny] == 0 || matriz[nx][ny] == 1){
                    push_back(nx, ny);
                }
            }

            if(!opcoes.empty()){
                return opcoes.front();
            }

            if(opcoes.empty()){
                return [-1, -1];
            }
        }
    }
}

void 



