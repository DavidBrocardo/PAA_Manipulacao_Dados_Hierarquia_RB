
// Implementacao base ultilzada do site Geeks for Geeks  
// https://www.geeksforgeeks.org/difference-between-bfs-and-dfs/ -> tem a explicacao certinha do algotirmo e apresenta a diferenca entre os dois algoritmos
// Fonte: https://www.geeksforgeeks.org/level-order-tree-traversal/  Acesso: 24/02/2025

// Recursive C++ program for level order traversal of Binary Tree
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int buscarBFS(vector<int> &preOrdem, int valorProcurado) {
    int comparacoes = 0;
    queue<int> fila;

    // Colocando os elementos da pré-ordem na fila
    for (int i = 0; i < preOrdem.size(); ++i) {
        fila.push(preOrdem[i]);
    }

    // Realizando a busca na fila (BFS)
    while (!fila.empty()) {
        comparacoes++;  // Contando a comparação
        int elemento = fila.front();
        fila.pop();

        if (elemento == valorProcurado) {
            cout << "Elemento " << valorProcurado << " encontrado!" << endl;
            return comparacoes;
        }
    }

    cout << "Elemento " << valorProcurado << " não encontrado!" << endl;
    return comparacoes;
}

int main() {
    // Pré-ordem já dada da árvore
    vector<int> preOrdem = {14, 11, 6, 12, 20, 17, 25, 30, 37, 40};

    // Valor a ser procurado
    int valorProcurado = 37;

    // Chamar a busca em largura (BFS)
    int comparacoes = buscarBFS(preOrdem, valorProcurado);

    // Exibir o número de comparações feitas
    cout << "Quantidade de comparações feitas na busca BFS: " << comparacoes << endl;

    return 0;
}
