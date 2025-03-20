#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <time.h>

using namespace std;

int main() {
    ifstream arquivo("nomes.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo."  << endl;
        return 1;
    }

    int compilacao = system("g++ Merge-Sort.cpp -o Merge");
    if (compilacao != 0) {
        cerr << "Erro ao compilar" << endl;
        return 1;
    }

    int compilacaoAlternativo = system("g++ Merge-Sort-Alternativo.cpp -o MergeA");
    if (compilacaoAlternativo != 0) {
        cerr << "Erro ao compilar" << endl;
        return 1;
    }
    string linha;


    FILE* arquivoTempo = fopen("TempoExec.csv", "a");
    if (arquivoTempo == nullptr) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }
    fprintf(arquivoTempo, "Arquivo , Merge-Sort, Merge-Sort-Aleatorio \n");

    while (getline(arquivo, linha)) {
        cout << "Arquivo atual : " << linha << endl;
        double TempoNormalMedia = 0.0;
        double TempoAlternativoMedia = 0.0;

        for (int i = 0; i < 6; i++){
            clock_t Ticks[2];
            string exe = "Merge " + linha+ ".txt";
            string exeA = "MergeA " + linha+ ".txt";
            // NORMAL
            Ticks[0] = clock();
            int execucao = system(exe.c_str());
            if (execucao != 0) {
                cerr << "Erro ao executar" << endl;
                return 1;
            }            
            Ticks[1] = clock();
            double TempoNormal = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
            // MODIFICADO

            Ticks[0] = clock();
            int execucaoA = system(exeA.c_str());
            if (execucaoA != 0) {
                cerr << "Erro ao executar" << endl;
                return 1;
            }            
            Ticks[1] = clock();
            double TempoAlternativo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
            if (i != 0){
                TempoNormalMedia =  TempoNormalMedia + TempoNormal;
                TempoAlternativoMedia = TempoAlternativoMedia +  TempoAlternativo;
            }          
        } 
        TempoNormalMedia = TempoNormalMedia/ 5;
        TempoAlternativoMedia = TempoAlternativoMedia/5;
        fprintf(arquivoTempo, "%s, %f , %f\n", linha.c_str(), TempoNormalMedia, TempoAlternativoMedia);
    }
    arquivo.close();

    return 0;
}
