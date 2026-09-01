#include <iostream>
#include <vector>
#include <random>
#include <algorithm> // Necessário para sort e reverse

using namespace std;

class Dados {
public:
    // Correção: Vetores devem ser de inteiros (int), e não da própria classe
    vector<int> dadosAletorios;
    vector<int> dadosPreOrdenados;
    vector<int> dadosInverso;
    vector<int> dadosParOrdenados; // (Parcialmente ordenados)

    void inserirDados() {
        cout << "\n==============================\n";
        cout << "       MENU DE OPCOES         \n";
        cout << "==============================\n";
        cout << "1. Testar com 1.000 dados\n";
        cout << "2. Testar com 10.000 dados\n";
        cout << "3. Testar com 50.000 dados\n";
        cout << "4. Testar com 100.000 dados\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opcao: ";
        
        int opcao;
        cin >> opcao;

        int qntd = 0;
        switch(opcao) {
            case 1: qntd = 1000; break;
            case 2: qntd = 10000; break;
            case 3: qntd = 50000; break;
            case 4: qntd = 100000; break;
            case 5: return;
            default: 
                cout << "\n[Erro] Opcao invalida!\n"; 
                return;
        }

        // Limpa vetores anteriores caso o usuário rode o menu de novo
        dadosAletorios.clear();
        dadosAletorios.reserve(qntd);

        // Configuração do gerador aleatório (fora do switch para evitar repetição)
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(1, qntd * 10);

        // 1. Preenche o vetor com dados aleatórios
        for(int i = 0; i < qntd; i++) {
            dadosAletorios.push_back(distrib(gen));
        }

        // 2. Prepara os outros cenários a partir do vetor aleatório
        
        // Copia e ordena (Cenário: Pré-ordenado / Melhor caso para alguns algoritmos)
        dadosPreOrdenados = dadosAletorios;
        sort(dadosPreOrdenados.begin(), dadosPreOrdenados.end());

        // Copia o ordenado e inverte (Cenário: Ordem inversa / Pior caso para alguns algoritmos)
        dadosInverso = dadosPreOrdenados;
        reverse(dadosInverso.begin(), dadosInverso.end());

        // Copia o ordenado e bagunça um pouquinho (Cenário: Parcialmente ordenado)
        dadosParOrdenados = dadosPreOrdenados;
        // Exemplo simples: troca 10% dos elementos de posição para simular desalinhamento leve
        for(int i = 0; i < qntd; i += 10) {
            if (i + 1 < qntd) {
                swap(dadosParOrdenados[i], dadosParOrdenados[i + 1]);
            }
        }

        cout << "\n[Sucesso] " << qntd << " dados gerados e preparados em todos os cenarios!\n";
    }
};