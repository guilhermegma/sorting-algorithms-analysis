#include <iostream>
#include <vector>
#include <random>
#include <algorithm> // Necessário para sort e reverse
#include <iomanip>
#include <string>

using namespace std;

class Dados {
public:
    vector<int> dadosAletorios;
    vector<int> dadosPreOrdenados;
    vector<int> dadosInverso;
    vector<int> dadosParOrdenados; 

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
        dadosPreOrdenados.clear();
        dadosPreOrdenados.reserve(qntd);
        dadosInverso.clear();
        dadosInverso.reserve(qntd);
        dadosParOrdenados.clear();
        dadosParOrdenados.reserve(qntd);

        // Configuração do gerador aleatório (fora do switch para evitar repetição)
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(1, qntd * 10);
        uniform_int_distribution<int> incremento(1, 10);
        uniform_int_distribution<int> posicao(0, qntd - 1);

        // --- Dados aleatorios ---
        for (int i = 0; i < qntd; i++) {
            dadosAletorios.push_back(distrib(gen));
        }    // Cabeçalho exato que você pediu

        // --- Dados pre-ordenados ---
        // IMPORTANTE: o enunciado proibe usar funcoes de ordenacao prontas
        // da biblioteca (ex.: std::sort). Por isso a sequencia crescente
        // eh construida diretamente, por soma de incrementos aleatorios,
        // sem chamar nenhum algoritmo de ordenacao.
        {
            int valor = incremento(gen);
            dadosPreOrdenados.push_back(valor);
            for (int i = 1; i < qntd; i++) {
                valor += incremento(gen);
                dadosPreOrdenados.push_back(valor);
            }
        }

        // --- Dados em ordem inversa ---
        // Mesmo raciocinio: construida diretamente decrescente,
        // sem usar std::sort + std::reverse.
        {
            int valor = qntd * 10;
            dadosInverso.push_back(valor);
            for (int i = 1; i < qntd; i++) {
                valor -= incremento(gen);
                dadosInverso.push_back(valor);
            }
        }

        // --- Dados parcialmente ordenados ---
        // Parte da sequencia ja crescente (copia de vetor, isso NAO eh
        // ordenacao) e embaralha ~10% das posicoes com swaps aleatorios.
        dadosParOrdenados = dadosPreOrdenados;
        {
            int trocas = qntd / 10;
            if (trocas < 1) trocas = 1;
            for (int i = 0; i < trocas; i++) {
                int a = posicao(gen);
                int b = posicao(gen);
                swap(dadosParOrdenados[a], dadosParOrdenados[b]);
            }
        }

        cout << "\n[Sucesso] " << qntd << " dados gerados e preparados em todos os cenarios!\n";
    }

    // Retorna referencia ao vetor correspondente ao tipo escolhido
    // (1=Aleatorios, 2=Pre-Ordenados, 3=Inversos, 4=Parcialmente Ordenados)
    vector<int>& obterVetorPorTipo(int tipo) {
        switch (tipo) {
            case 1:  return dadosAletorios;
            case 2:  return dadosPreOrdenados;
            case 3:  return dadosInverso;
            case 4:  return dadosParOrdenados;
            default: return dadosAletorios;
        }
    }

    string nomeTipo(int tipo) {
        switch (tipo) {
            case 1:  return "Aleatorios";
            case 2:  return "Pre-Ordenados";
            case 3:  return "Inversos";
            case 4:  return "Parcialmente Ordenados";
            default: return "Desconhecido";
        }
    }

    bool vazio() {
        return dadosAletorios.empty();
    }

  void imprimirTabela(const vector<int>& v, const string& titulo) {
        if (v.empty()) {
            cout << "\n[Aviso] Nenhum dado gerado ainda!\n";
            return;
        }

        const int colunas = 10;            // 10 colunas cabem perfeitamente na largura do terminal
        const int linhasPorPagina = 20;     // Mostra 20 linhas (200 elementos) por vez
        const int itensPorPagina = colunas * linhasPorPagina;

        size_t totalElementos = v.size();
        size_t paginaAtual = 0;

        while (true) {
            cout << "\n=================================================================\n";
            cout << " " << titulo << " (Total: " << totalElementos << " elementos)\n";
            cout << "=================================================================\n";

            // Imprime o cabeçalho fixo de 10 colunas
            for (int c = 1; c <= colunas; ++c) {
                cout << setw(6) << "C" + to_string(c) << " ";
            }
            cout << "\n-----------------------------------------------------------------\n";

            size_t inicio = paginaAtual * itensPorPagina;
            size_t fim = min(inicio + itensPorPagina, totalElementos);

            // Imprime o bloco da página atual
            for (size_t i = inicio; i < fim; ++i) {
                cout << setw(6) << v[i] << " ";
                if ((i + 1) % colunas == 0) {
                    cout << "\n";
                }
            }
            
            // Garante quebra de linha se a última linha estiver incompleta
            if ((fim - inicio) % colunas != 0) {
                cout << "\n";
            }

            cout << "-----------------------------------------------------------------\n";
            cout << "Exibindo itens " << (inicio + 1) << " a " << fim << " de " << totalElementos;

            if (fim >= totalElementos) {
                cout << "\n\n[Fim da tabela]\n";
                break;
            }

            cout << "\nPressione [Enter] para ver a proxima pagina (ou digite 'q' para sair): ";
            string entrada;
            getline(cin, entrada);

            if (entrada == "q" || entrada == "Q") {
                break;
            }
            paginaAtual++;
        }
    }

    void exibirDados() {
        if (dadosAletorios.empty()) {
            cout << "\n[Erro] Voce precisa gerar os dados primeiro (Opcao 1)!\n";
            return;
        }

        cout << "\n==============================\n";
        cout << "  Deseja exibir quais dados?  \n";
        cout << "==============================\n";
        cout << "1. Exibir Aleatorios\n";
        cout << "2. Exibir Pre-Ordenados \n";
        cout << "3. Exibir Inversos\n";
        cout << "4. Exibir Parcialmente Ordenados\n";
        cout << "5. Voltar\n";
        cout << "Escolha uma opcao: ";
        
        int opcao;
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer do cin

        switch(opcao) {
            case 1:
                imprimirTabela(dadosAletorios, "Tabela de Dados Aleatorios");
                break;
            case 2: 
                imprimirTabela(dadosPreOrdenados, "Tabela de Dados Pre-Ordenados");
                break;
            case 3:
                imprimirTabela(dadosInverso, "Tabela de Dados Inversos");
                break;
            case 4:
                imprimirTabela(dadosParOrdenados, "Tabela de Dados Parcialmente Ordenados");
                break;
            case 5: 
                return;
            default: 
                cout << "\n[Erro] Opcao invalida!\n"; 
                break;
        }
    }

    // Função auxiliar para automatizar a geração sem usar o menu (cin)
    void gerarDadosSilencioso(int qntd) {
        dadosAletorios.clear(); dadosAletorios.reserve(qntd);
        dadosPreOrdenados.clear(); dadosPreOrdenados.reserve(qntd);
        dadosInverso.clear(); dadosInverso.reserve(qntd);
        dadosParOrdenados.clear(); dadosParOrdenados.reserve(qntd);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(1, qntd * 10);
        uniform_int_distribution<int> incremento(1, 10);
        uniform_int_distribution<int> posicao(0, qntd - 1);

        for (int i = 0; i < qntd; i++) dadosAletorios.push_back(distrib(gen));

        int valor = incremento(gen);
        dadosPreOrdenados.push_back(valor);
        for (int i = 1; i < qntd; i++) {
            valor += incremento(gen);
            dadosPreOrdenados.push_back(valor);
        }

        valor = qntd * 10;
        dadosInverso.push_back(valor);
        for (int i = 1; i < qntd; i++) {
            valor -= incremento(gen);
            dadosInverso.push_back(valor);
        }

        dadosParOrdenados = dadosPreOrdenados;
        int trocas = max(1, qntd / 10);
        for (int i = 0; i < trocas; i++) {
            int a = posicao(gen);
            int b = posicao(gen);
            swap(dadosParOrdenados[a], dadosParOrdenados[b]);
        }
    }
};