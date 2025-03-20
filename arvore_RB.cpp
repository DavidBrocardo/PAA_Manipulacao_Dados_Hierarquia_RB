#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <time.h>
#include <queue>
using namespace std;


class No {
public:
    int dado;
    string cor;
    No *esquerda, *direita, *pai;

    No(int valor) {
        dado = valor;
        cor = "Vermelho";
        esquerda = direita = pai = nullptr;
    }
};

class ArvoreRubroNegra {
private:
    No* raiz;
    No* NIL;

    // Função de rotação à esquerda
    void rotacionarEsquerda(No* x) {
        No* y = x->direita;
        x->direita = y->esquerda;
        if (y->esquerda != NIL) {
            y->esquerda->pai = x;
        }
        y->pai = x->pai;
        if (x->pai == nullptr) {
            raiz = y;
        }
        else if (x == x->pai->esquerda) {
            x->pai->esquerda = y;
        }
        else {
            x->pai->direita = y;
        }
        y->esquerda = x;
        x->pai = y;
    }

    // Função de rotação à direita
    void rotacionarDireita(No* x) {
        No* y = x->esquerda;
        x->esquerda = y->direita;
        if (y->direita != NIL) {
            y->direita->pai = x;
        }
        y->pai = x->pai;
        if (x->pai == nullptr) {
            raiz = y;
        }
        else if (x == x->pai->direita) {
            x->pai->direita = y;
        }
        else {
            x->pai->esquerda = y;
        }
        y->direita = x;
        x->pai = y;
    }

    // Função para corrigir a árvore Rubro-Negra após inserção
    void corrigirInsercao(No* k) {
        while (k != raiz && k->pai->cor == "Vermelho") {
            if (k->pai == k->pai->pai->esquerda) {
                No* tio = k->pai->pai->direita; // tio
                if (tio->cor == "Vermelho") {
                    k->pai->cor = "Preto";
                    tio->cor = "Preto";
                    k->pai->pai->cor = "Vermelho";
                    k = k->pai->pai;
                }
                else {
                    if (k == k->pai->direita) {
                        k = k->pai;
                        rotacionarEsquerda(k);
                    }
                    k->pai->cor = "Preto";
                    k->pai->pai->cor = "Vermelho";
                    rotacionarDireita(k->pai->pai);
                }
            }
            else {
                No* tio = k->pai->pai->esquerda; // tio
                if (tio->cor == "Vermelho") {
                    k->pai->cor = "Preto";
                    tio->cor = "Preto";
                    k->pai->pai->cor = "Vermelho";
                    k = k->pai->pai;
                }
                else {
                    if (k == k->pai->esquerda) {
                        k = k->pai;
                        rotacionarDireita(k);
                    }
                    k->pai->cor = "Preto";
                    k->pai->pai->cor = "Vermelho";
                    rotacionarEsquerda(k->pai->pai);
                }
            }
        }
        raiz->cor = "Preto";
    }


  
public:
    // Construtor
    ArvoreRubroNegra() {
        NIL = new No(0);
        NIL->cor = "Preto";
        NIL->esquerda = NIL->direita = NIL;
        raiz = NIL;
    }

    // Função de inserção
    void inserir(int dado) {
        No* novo_no = new No(dado);
        novo_no->esquerda = NIL;
        novo_no->direita = NIL;

        No* pai = nullptr;
        No* atual = raiz;

        // Inserção como em uma árvore de busca binária
        while (atual != NIL) {
            pai = atual;
            if (novo_no->dado < atual->dado) {
                atual = atual->esquerda;
            }
            else {
                atual = atual->direita;
            }
        }

        novo_no->pai = pai;

        if (pai == nullptr) {
            raiz = novo_no;
        }
        else if (novo_no->dado < pai->dado) {
            pai->esquerda = novo_no;
        }
        else {
            pai->direita = novo_no;
        }

        if (novo_no->pai == nullptr) {
            novo_no->cor = "Preto";
            return;
        }

        if (novo_no->pai->pai == nullptr) {
            return;
        }

        corrigirInsercao(novo_no);
    }


    No* GetRaiz() {
        return raiz;
    }
    
    // Busca DFS percorrendo a árvore em Pré-Ordem (Raiz → Esquerda → Direita)
    No* buscarDFS(No* no, int dado, int& comparacoes) {        
        if (no == NIL) return nullptr; 
        
        comparacoes++;
        //cout << "Visitando: " << no->dado << endl; // Mostra o percurso
        
        if (no->dado == dado) {
            return no;  
        }
    
        // Primeiro tenta encontrar na esquerda
        No* resultadoEsquerda = buscarDFS(no->esquerda, dado, comparacoes);
        if (resultadoEsquerda != nullptr) return resultadoEsquerda;
    
        // Se não encontrou na esquerda, busca na direita
        return buscarDFS(no->direita, dado, comparacoes);
    }


    No* buscarBFS(No* no, int dado, int& comparacoes) {        
        queue<No*> fila;  
        fila.push(no);  
    
        while (!fila.empty()) {
            comparacoes++;
            No* noAtual = fila.front(); 
            fila.pop(); 
    
            //cout << "Visitando: " << noAtual->dado << endl;
    
            // Verifica se encontrou o dado
            if (noAtual->dado == dado) {
                
                return noAtual;  
            }
    
            // Adiciona filhos à fila apenas se não forem NIL
            if (noAtual->esquerda != NIL) {  // Verifica se o filho esquerdo não é NIL
                fila.push(noAtual->esquerda);
            }
            if (noAtual->direita != NIL) {  // Verifica se o filho direito não é NIL
                fila.push(noAtual->direita);
            }
        }
    
        return nullptr;  // Elemento não encontrado
    }
    
    // Função auxiliar para chamar a busca DFS 
    int buscarElementoDFS(int dado) {
        int comparacoes = 0;
        No* resultado = buscarDFS(GetRaiz(), dado, comparacoes);
        return comparacoes;     
    }

    // Função auxiliar para chamar a busca BFS 
    int buscarElementoBFS(int dado) {
        int comparacoes = 0;
        No* resultado = buscarBFS(GetRaiz(), dado, comparacoes);
        
        return comparacoes;     
    }

};

int main() {
    ifstream arquivo("nomes.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo.1"  << endl;
        return 1;
    }

    clock_t Ticks[2];
    ArvoreRubroNegra arn;
    

    FILE* arquivoTempo = fopen("TempoExec.csv", "a");
    if (arquivoTempo == nullptr) {
        cerr << "Erro ao abrir o arquivo.2" << endl;
        return 1;
    }
    fprintf(arquivoTempo, "Arquivo , BFS, DFS \n");

    FILE* arquivoComparacoes = fopen("TempoExec.csv", "a");
    if (arquivoComparacoes == nullptr) {
        cerr << "Erro ao abrir o arquivo.2" << endl;
        return 1;
    }
    fprintf(arquivoTempo, "Arquivo ,Numero Buscado, BFS, DFS \n");
    string linha;
    while (getline(arquivo, linha)) {
        cout << "Arquivo" << linha <<".txt"<< endl;
       
        string caminhoCompleto = "EntradasArvores/Construir/" + linha + ".txt";
        //cout<<caminhoCompleto;
        ifstream dadosentrada(caminhoCompleto);
        if (!dadosentrada.is_open()) {
            cerr << "Erro ao abrir o arquivo.3" << endl;
            return 1;
        }
        vector<int> valores_inserir;
        
        string valor;
        // Lê o arquivo linha por linha
        while (getline(dadosentrada, valor)) {
            stringstream ss(valor);  // Usamos stringstream para separar os números
            int numero;
            while (ss >> numero) {  // Lê cada número da linha
                valores_inserir.push_back(numero);
            }
        }
        size_t tamanho = valores_inserir.size();   
      
        for (int i = 0; i < tamanho; ++i) {
            arn.inserir(valores_inserir[i]);
        }

        
        
        caminhoCompleto = "EntradasArvores/Consultar/" + linha + ".txt";
        ifstream dadosanalise(caminhoCompleto);
        if (!dadosanalise.is_open()) {
            cerr << "Erro ao abrir o arquivo." << endl;
            return 1;
        }
        vector<int> valores_verificar;
        
        
        while (getline(dadosanalise, valor)) {
            stringstream ss(valor);  // Usamos stringstream para separar os números
            int numero;
            while (ss >> numero) {  // Lê cada número da linha
                valores_verificar.push_back(numero);
            }
        }

        tamanho = valores_verificar.size();
        cout << tamanho << endl;
        double tempo_totalDFS = 0.0;
        int comparacoes = 0;
        for (int exe = 0; exe <= 5; ++exe) {
            Ticks[0] = clock();
            for (int i = 0; i < tamanho; ++i) {  // Executa muitas vezes
                comparacoes = arn.buscarElementoDFS(valores_verificar[i]);
                //cout << "Numero "<< valores_verificar[i] <<" comparacoes " << comparacoes << endl;
                
            }      
            Ticks[1] = clock();
            double duracao = (Ticks[1] - Ticks[0]) / static_cast<double>(CLOCKS_PER_SEC); // Em segundos
            //duracao *= 1000;  // milissegundos (ms)
            
            if (exe != 0){
                tempo_totalDFS += duracao;
            }
        }
        tempo_totalDFS  = tempo_totalDFS/5;
        cout <<"Tempo DFS  " << tempo_totalDFS << endl;
        //cout <<"Comparacoes "<<  comparacoes << endl;
        double tempo_totalBFS = 0.0;
        for (int exe = 0; exe <= 0; ++exe) {
            Ticks[0] = clock();
            for (int i = 0; i < tamanho; ++i) {  // Executa muitas vezes
                comparacoes = arn.buscarElementoBFS(valores_verificar[i]);
                //cout << "Numero "<< valores_verificar[i] <<" comparacoes " << comparacoes << endl;
            }      
            Ticks[1] = clock();
            double duracao = (Ticks[1] - Ticks[0]) / static_cast<double>(CLOCKS_PER_SEC); // Em segundos
            //duracao *= 1000;  // milissegundos (ms)
            
            if (exe != 0){
                tempo_totalBFS += duracao;
            }
        }

        tempo_totalBFS  = tempo_totalBFS/5;
        cout <<"Tempo BFS  " << tempo_totalBFS << endl;
        //fprintf(arquivoTempo, "Arquivo , BFS, DFS \n");
        fprintf(arquivoTempo, "%s, %f , %f\n", linha.c_str(), tempo_totalBFS, tempo_totalDFS);
        

    }

    



    

    

    return 0;
}
