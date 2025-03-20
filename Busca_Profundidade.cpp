#include <iostream>
#include <vector>
using namespace std;

int buscarDFS(vector<int> &preOrdem, int valorProcurado) {
    int comparacoes = 0;

    // Percorrendo a sequência de pré-ordem (simulando DFS)
    for (int i = 0; i < preOrdem.size(); ++i) {
        comparacoes++;  // Contando a comparação
        if (preOrdem[i] == valorProcurado) {
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

    // Chamar a busca em profundidade (DFS)
    int comparacoes = buscarDFS(preOrdem, valorProcurado);

    // Exibir o número de comparações feitas
    cout << "Quantidade de comparações feitas na busca DFS: " << comparacoes << endl;

    return 0;
}
