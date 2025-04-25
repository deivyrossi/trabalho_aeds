# 🔥 Simulador de Propagação de Incêndios em Florestas

**Disciplina:** Estrutura de Dados  
**Professor:** Michel Pires da Silva – CEFET-MG  
**Aluno:** Deivy Rossi Teixeira de Melo 
**Entrega:** 26 de abril de 2025

---

## 📌 Objetivo

Este projeto implementa um simulador de propagação de incêndio em uma floresta representada por uma matriz dinâmica. Cada célula da matriz pode conter diferentes estados do ambiente (árvore saudável, em chamas, queimada, água ou vazio). O foco da simulação está na propagação do fogo, movimentação de um animal e influência do vento sobre o comportamento do incêndio.

---

## 🔧 Compilação e Execução

### Requisitos:
- Compilador C++
- Sistema Linux
- `make` instalado

### Passos:

```bash
make clean
make
make run
```

---

## 🧩 Arquivos do Projeto

```
├── src/              # Códigos-fonte (.cpp)
├── include/          # Headers (.hpp)
├── input.dat         # Arquivo de entrada com matriz
├── output.dat        # Relatório gerado
├── Makefile          # Compilação automatizada
└── README.md         # Documentação
```

---

## 📥 Formato da Entrada (`input.dat`)

```
<linhas> <colunas> <fogoX> <fogoY>
<linha_1>
<linha_2>
...
<linha_n>
```

Exemplo:

```
5 5 1 1
1 1 1 1 4
1 2 1 1 1
1 1 1 1 4
0 0 1 1 1
1 4 1 0 4
```

---

## 🔁 Estados da Matriz

| Valor | Significado          |
|-------|----------------------|
| 0     | Área vazia           |
| 1     | Árvore saudável      |
| 2     | Árvore pegando fogo  |
| 3     | Árvore queimada      |
| 4     | Água                 |
| 5     | Fogo em transição    |
| A     | Posição do animal    |

---

## 🚶‍♂️ Comportamento do Animal

- Começa na primeira célula `0` da matriz.
- Se encontra `4`, hidrata a água e adjacentes.
- Possui vidas extras (pode resistir a até N queimaduras).
- Morre se estiver encurralado ou com fogo sem rota de fuga.

---

## 🌬️ Influência do Vento

O vento é configurável no arquivo `config.hpp`:

```cpp
#define VENTO_CIMA = true;
#define VENTO_BAIXO = true;
#define VENTO_ESQUERDA = false;
#define VENTO_DIREITA = true;
```

Com vento ativado, o fogo se propaga **somente nas direções permitidas**.

---

## 📤 Saída: `output.dat`

O estado da matriz é salvo a cada iteração, incluindo a posição do animal e os valores atualizados.

Exemplo de saída:

```
Iteração 0:
1 2 1 1 4 
2 2 2 1 1 
1 2 1 1 4 
0 A 1 1 1 
1 0 1 0 4
```

---

## 📊 Análise Visual

### 🔥 Sem vento

O fogo se propaga em todas as direções ortogonais. Exemplo (2 iterações):

![sem-vento](docs/sem-vento.png)

### 🌬️ Com vento direcionado

Ao ativar vento apenas para a direita, o fogo propaga de forma assimétrica:

![com-vento](docs/com-vento.png)

---

## 🤖 Estratégias e Algoritmos

- Busca por melhor posição: água > vazio > árvore
- Verificação de rotas de fuga (`existeSaida`)
- Propagação de incêndio controlada por vento
- Mecanismo de segunda chance ao pisar no fogo

---

## 🔬 Considerações Finais

A simulação ilustra com clareza como pequenas variações nas condições ambientais (vento, hidratação) impactam significativamente o avanço do incêndio. A modularização do código, o uso de estruturas de dados dinâmicas e a análise visual permitem avaliar com precisão o comportamento do sistema.

---

## 📈 Possíveis Melhorias

- Interface gráfica com SDL
- Entrada interativa via terminal
- Estatísticas salvas em CSV para gráficos

---

## ✅ Requisitos Atendidos

- [x] Modularização com headers
- [x] Simulação visual iterativa
- [x] Propagação com vento e sem vento
- [x] Gravação de `output.dat`
- [x] Caminho do animal, mortes, água
- [x] Makefile funcional
