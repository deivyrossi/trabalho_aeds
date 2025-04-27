# 🔥 Simulador de Propagação de Incêndios em Florestas

**Disciplina:** Algoritmos e Estrutura de Dados  
**Professor:** Michel Pires da Silva – CEFET-MG  
**Aluno:** Deivy Rossi Teixeira de Melo 

---

## 📌 Objetivo

Este projeto implementa um simulador de propagação de incêndio em uma floresta representada por uma matriz dinâmica. Cada célula da matriz pode conter diferentes estados do ambiente (árvore saudável, em chamas, queimada, água ou vazio). O foco da simulação está na propagação do fogo, movimentação de um animal e influência do vento sobre o comportamento do incêndio.

---

## 🔧 Compilação e Execução
### Requisitos
- Compilador C++
- Sistema Linux
- make instalado

### Passos
- Clone o repositório:
```
git clone https://github.com/deivyrossi/trabalho_aeds.git
```

- Compile e execute:
```bash

make clean
make
make run
```

O arquivo output.dat será gerado, contendo a evolução da simulação.

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
| 5     | Fogo em transição (Não é mostrado)    |

---

### 🐾 Comportamento do Animal

O comportamento do animal na simulação é determinado por uma combinação de fatores, incluindo a busca por uma saída, a interação com o ambiente (fogo e água) e a tentativa de evitar focos de incêndio. O animal se move de maneira inteligente, tomando decisões baseadas nas condições ao seu redor.
**Principais Características do Comportamento Atualizado:**
- **Busca Inteligente com BFS:** O animal realiza uma busca em largura para encontrar o local mais seguro possível, preferencialmente próximo a água ou em uma posição distante do fogo.
- **Prioridade de Sobrevivência:** O movimento visa minimizar riscos — primeiro buscando água, depois áreas sem fogo ao redor.
- **Avaliação de Ambiente:** Durante a busca, o animal ignora áreas em chamas ou queimadas e prioriza caminhos por terra ou diretamente pela água.
- **Movimentação Otimizada:** Graças à BFS, o animal pode encontrar rotas mais seguras mesmo em situações complexas, evitando caminhos que o levariam diretamente ao fogo.
- **Fuga Dinâmica:** Em caso de estar completamente cercado sem saídas, o animal pode ficar parado até morrer.

**Desafios e Melhorias Futura:**
- Implementação de heurísticas mais avançadas (como A*) para trajetórias ainda mais otimizadas.
- Melhor adaptação do animal a incêndios que mudam muito rapidamente de direção por conta do vento.


A simulação do comportamento do animal reflete uma interação simples, mas realista, com o ambiente.

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



## 🤖 Estratégias e Algoritmos

### 📂 Classe Arquivo

A classe `Arquivo` é responsável por carregar a matriz de dados a partir de um arquivo de entrada chamado `input.dat` e fornecer essa matriz para outras partes do programa. A matriz representa um ambiente, com informações sobre as dimensões e o conteúdo de cada célula.

### **Métodos da Classe `Arquivo`**

#### **Construtor `Arquivo::Arquivo`**

- **Descrição:** Constrói uma instância da classe `Arquivo`. 
- **Funcionamento:** Este construtor não realiza operações específicas além da inicialização da classe. Ele é utilizado para criar um objeto da classe `Arquivo` quando necessário.

#### **Método `Arquivo::getMatriz`**

- **Descrição:** Carrega os dados da matriz a partir do arquivo `input.dat`.
- **Entrada:** O arquivo `input.dat` deve conter as dimensões da matriz, a posição inicial do fogo e os dados da matriz.
- **Saída:** Retorna a matriz carregada do arquivo no formato de um vetor bidimensional (`vector<vector<int>>`). Caso ocorra algum erro na leitura, um vetor vazio é retornado.

**Explicação Detalhada:**

1. **Abrir o Arquivo:**
   - O método tenta abrir o arquivo `input.dat` para leitura. Caso o arquivo não seja aberto corretamente, uma mensagem de erro é impressa e um vetor vazio é retornado.

2. **Ler as Dimensões da Matriz:**
   - O arquivo contém as dimensões da matriz (número de `linhas` e `colunas`). Esses valores são lidos e utilizados para criar a matriz.

3. **Ler a Posição Inicial do Fogo:**
   - O arquivo contém as coordenadas (x, y) da posição do fogo. Essas coordenadas são lidas, mas não são utilizadas diretamente dentro desta função.

4. **Construir a Matriz:**
   - A matriz é criada com base nas dimensões lidas e é inicializada como um vetor bidimensional de inteiros. Ela será preenchida com os valores lidos do arquivo.

5. **Preencher a Matriz:**
   - O método percorre cada célula da matriz, linha por linha, e lê os valores do arquivo. Caso ocorra um erro na leitura de algum valor, uma mensagem de erro é impressa e um vetor vazio é retornado.

6. **Retornar a Matriz:**
   - Caso a leitura da matriz seja bem-sucedida, o método retorna a matriz carregada. Caso contrário, um vetor vazio é retornado.

---


### 🧠 Classe `Algoritmos`

A classe `Algoritmos` contém as funções responsáveis pela simulação do movimento do animal e a propagação do fogo, além de interações com o ambiente.

---

### Função `encontrarMelhorPosBFS`

- **Objetivo:** Utilizar o algoritmo de **Busca em Largura (BFS)** para encontrar a melhor posição segura para o animal se mover, priorizando encontrar água (valor 4) ou área segura (valor 0).
  
- **Entradas:**
  - `matriz`: Matriz representando o ambiente (floresta, água, fogo, etc.).
  - `linhas`, `colunas`: Dimensões da matriz.
  - `x`, `y`: Posição atual do animal.

- **Saída:**
  - Retorna a melhor nova posição `(x, y)` para o animal se mover.
  - Se não houver melhor posição possível, permanece na posição atual.

- **Funcionamento Detalhado:**
  1. Cria uma fila para realizar a BFS, iniciando pela posição atual do animal.
  2. Mantém uma matriz de visitados para evitar revisitar células.
  3. Para cada célula:
     - Verifica as posições vizinhas (cima, baixo, esquerda, direita).
     - Se encontrar uma célula de água (`4`), imediatamente retorna essa posição.
     - Se encontrar uma célula vazia (`0`), marca como possível melhor movimento, caso não haja água.
  4. Se terminar a busca sem encontrar água, move para o local de terra mais seguro encontrado.
  5. Se não houver movimento possível, o animal permanece na posição atual.

- **Vantagens da BFS no Contexto:**
  - Garante encontrar a posição mais próxima de água, minimizando o tempo de exposição ao fogo.
  - Evita decisões precipitadas que poderiam levar à morte rápida.
  - Permite uma navegação estratégica do ambiente dinâmico (mudanças causadas pela propagação do incêndio).

---

#### **Função `imprimirMatriz`**

- **Objetivo:** Imprimir a matriz representando o ambiente.
- **Entrada:** A matriz que contém os valores do ambiente (fogo, água, animal, etc.).
- **Explicação:**
  - Itera pelas linhas e colunas da matriz.
  - Imprime cada valor da matriz seguido de um espaço.
  - Após imprimir cada linha, imprime uma quebra de linha para organizar a saída.

---

#### **Função `existeSaida`**

- **Objetivo:** Verificar se há uma saída possível para o animal a partir de uma posição dada.
- **Entradas:**
  - `matriz`: A matriz que representa o ambiente.
  - `pos`: A posição atual do animal.
- **Saída:** `true` se existir uma saída (posição de água ou fim do caminho), `false` caso contrário.
- **Explicação:**
  - Define os deslocamentos para as quatro direções possíveis (cima, baixo, esquerda, direita).
  - Para cada direção, calcula as novas posições possíveis.
  - Verifica se a nova posição está dentro dos limites da matriz.
  - Se a nova posição for água (valor 4) ou terra (valor 0), retorna `true`, indicando que há uma saída.
  - Se não houver saída em nenhuma direção, retorna `false`.

---

#### **Função `encontrarCaminho`**

- **Objetivo:** Encontrar a posição inicial onde o animal pode começar seu movimento.
- **Entradas:**
  - `matriz`: A matriz do ambiente.
  - `linhas` e `colunas`: Dimensões da matriz.
- **Saída:** A posição inicial `(x, y)` onde o animal pode começar, ou `(-1, -1)` se não encontrar uma posição válida.
- **Explicação:**
  - Itera sobre toda a matriz.
  - Quando encontra uma célula com valor `0` (terra), retorna as coordenadas dessa posição como a posição inicial do animal.
  - Se não encontrar nenhuma célula válida (valor 0), retorna `(-1, -1)`.

---

#### **Função `SimularIteracoes`**

- **Objetivo:** Simular o movimento do animal, propagação do fogo e interação com o ambiente ao longo de várias iterações.
- **Entradas:**
  - `linhas` e `colunas`: Dimensões da matriz.
  - `matriz`: A matriz que representa o ambiente.
  - `inicial`: A posição inicial do animal.
- **Saída:** Nenhuma diretamente, mas imprime o progresso da simulação e grava os resultados em um arquivo.
- **Explicação:**
  - Inicializa variáveis como a posição do animal, número de passos dados, água encontrada, e número de iterações paradas.
  - Cria uma lista de posições de fogo (focos).
  - Entra em um loop de simulação, que continua enquanto o animal estiver vivo, existirem focos de fogo e o número de iterações não exceder o máximo.
  - Em cada iteração:
    - Chama a função `encontrarMelhorPos` para determinar a próxima posição do animal.
    - Verifica se a nova posição é válida e atualiza a posição do animal.
    - Se o animal encontrar água (valor 4), registra o evento e altera o valor da célula para 0 (terra).
    - Propaga o fogo de acordo com as direções do vento.
    - Atualiza a matriz com os novos focos de fogo e status (fogo ativo ou apagado).
    - Verifica se o animal está parado há 3 iterações e se não há saída disponível. Caso isso aconteça, o animal morre.
    - Imprime a matriz atualizada e salva a iteração em um arquivo.
  - Após a simulação, imprime o resultado: se o animal sobreviveu ou morreu, o número de passos e o número de águas encontradas.

---

#### **Função `salvarIteracaoNoArquivo`**

- **Objetivo:** Salvar o estado da simulação em um arquivo `output.dat` após cada iteração.
- **Entradas:**
  - `matriz`: A matriz do ambiente após a iteração.
  - `iteracao`: O número da iteração atual.
  - `posAnimal`: A posição do animal.
  - `animalVivo`: Indica se o animal está vivo ou morto.
- **Explicação:**
  - Abre o arquivo `output.dat` para adicionar os dados.
  - Escreve o número da iteração, a posição do animal e seu status (vivo ou morto).
  - Itera sobre a matriz e escreve cada valor no arquivo, substituindo valores específicos por uma representação mais visível.
  - Fecha o arquivo após salvar os dados.

---

#### **Função `executarPrograma`**

- **Objetivo:** Executar o programa de simulação completo.
- **Entrada:** Nenhuma entrada diretamente, pois a função chama outras para realizar o processo.
- **Saída:** Nenhuma saída diretamente, mas inicia a simulação e gera o arquivo `output.dat`.
- **Explicação:**
  - Limpa o arquivo de saída (`output.dat`).
  - Cria uma instância da classe `Arquivo` e carrega a matriz do ambiente.
  - Verifica se a matriz não está vazia.
  - Chama a função `encontrarCaminho` para determinar a posição inicial do animal.
  - Se a posição inicial for válida, chama a função `SimularIteracoes` para começar a simulação.
  - Se houver erro ao carregar a matriz ou encontrar a posição inicial, o programa termina com uma mensagem de erro.
---

### 🔬 Considerações Finais

A simulação ilustrou de maneira eficaz como variáveis ambientais, como vento e hidratação, influenciam a propagação do incêndio. A modularização do código e o uso de estruturas dinâmicas permitiram uma implementação flexível e escalável, facilitando ajustes futuros.
A análise visual e os dados numéricos gerados ao longo das iterações forneceram uma compreensão detalhada do comportamento do sistema, ajudando a identificar pontos críticos.
**Pontos de Melhoria:**
- **Eficiência no Algoritmo:** O tempo de execução poderia ser otimizado, especialmente ao lidar com grandes matrizes e múltiplos focos de fogo.
- **Visualização:** A criação de uma interface gráfica poderia melhorar a interpretação dos resultados, facilitando a análise do comportamento do incêndio.

No geral, a simulação oferece uma boa base para entender a propagação de incêndios, com espaço para melhorias que podem enriquecer a experiência e a precisão dos resultados.

### 📬 Contato

Se você tiver dúvidas, sugestões ou qualquer tipo de feedback sobre o projeto, fique à vontade para entrar em contato.

- **E-mail:** deivyrossi@gmail.com
- **GitHub:** https://github.com/deivyrossi
- **LinkedIn:** https://www.linkedin.com/in/deivy-rossi-380263279/

