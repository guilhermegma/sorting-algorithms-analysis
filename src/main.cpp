#include <iostream>
#include <fstream>
#include "Dados.cpp"
#include "Ordenacao.cpp"

using namespace std;

// Pequeno submenu para escolher qual das 4 organizacoes de dados usar
// antes de rodar um algoritmo de ordenacao.
int escolherOrganizacao() {
    cout << "\nEscolha a organizacao dos dados a ordenar:\n";
    cout << "1. Aleatorios\n";
    cout << "2. Pre-Ordenados\n";
    cout << "3. Inversos\n";
    cout << "4. Parcialmente Ordenados\n";
    cout << "Escolha: ";
    int tipo;
    cin >> tipo;
    return tipo;
}

void exportarResultadosCSV(Dados& gerenciador) {
    ofstream arquivo("docs/resultados.csv");
    
    arquivo << "Algoritmo,Tamanho,Organizacao,Comparacoes,Movimentacoes,Tempo\n";

    string nomesAlgo[5] = {"Selection Sort", "Insertion Sort", "Shell Sort", "Quick Sort", "Heap Sort"};
    FuncaoOrdenacao funcoes[5] = {selectionSort, insertionSort, shellSort, quickSort, heapSort};
    int tamanhos[4] = {1000, 10000, 50000, 100000};
    
    cout << "\n[Aviso] Iniciando execucao em lote. Isso pode demorar alguns minutos...\n";

    // 1. Ordem por Algoritmo (Selection ate Heap)
    for (int a = 0; a < 5; a++) {
        cout << "> Processando " << nomesAlgo[a] << "...\n";
        
        // 2. Ordem por Tamanho (1.000 ate 100.000)
        for (int t = 0; t < 4; t++) {
            int tamanhoAtual = tamanhos[t];
            gerenciador.gerarDadosSilencioso(tamanhoAtual); 
            
            // 3. Ordem por Organizacao (Aleatorio ate Parcialmente Ordenado)
            for (int org = 1; org <= 4; org++) {
                vector<int> copia = gerenciador.obterVetorPorTipo(org);
                Estatisticas stats;
                
                // Medição de tempo silenciosa (sem usar cout da executarAlgoritmo)
                auto inicio = high_resolution_clock::now();
                funcoes[a](copia, stats);
                auto fim = high_resolution_clock::now();
                
                stats.tempoExecucao = duration<double>(fim - inicio).count();
                
                // Gravando a linha no CSV
                arquivo << nomesAlgo[a] << "," 
                        << tamanhoAtual << "," 
                        << gerenciador.nomeTipo(org) << ","
                        << stats.comparacoes << ","
                        << stats.movimentacoes << ","
                        << fixed << setprecision(6) << stats.tempoExecucao << "\n";
            }
        }
    }
    
    arquivo.close();
    cout << "\n[Sucesso] Arquivo 'resultados.csv' gerado com as 80 combinacoes ordenadas!\n";
}

int main() {
    Dados gerenciador;
    int opcao = 0;

    while (opcao != 9) {
        cout << "\n========================================================\n";
        cout << " LABORATORIO 1 ED2 - ALGORITMOS DE ORDENACAO\n";
        cout << "========================================================\n";
        cout << "1. Gerar um conjunto de dados\n";
        cout << "2. Exibir os dados gerados\n";
        cout << "3. Ordenar utilizando Selection Sort\n";
        cout << "4. Ordenar utilizando Insertion Sort\n";
        cout << "5. Ordenar utilizando Shell Sort\n";
        cout << "6. Ordenar utilizando Quick Sort\n";
        cout << "7. Ordenar utilizando Heap Sort\n";
        cout << "8. Executar e comparar todos os algoritmos\n";
        cout << "9. Exportar todos os testes em CSV\n";
        cout << "10. Encerrar o programa\n";
        cout << "========================================================\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao >= 3 && opcao <= 8 && gerenciador.vazio()) {
            cout << "\n[Erro] Voce precisa gerar um conjunto de dados primeiro (opcao 1)!\n";
            continue;
        }

        Estatisticas stats;
        int tipo;

        switch (opcao) {
            case 1:
                gerenciador.inserirDados();
                break;
            case 2:
                gerenciador.exibirDados();
                break;
            case 3:
                tipo = escolherOrganizacao();
                executarAlgoritmo(selectionSort, "Selection Sort (" + gerenciador.nomeTipo(tipo) + ")",
                                   gerenciador.obterVetorPorTipo(tipo), stats);
                break;
            case 4:
                tipo = escolherOrganizacao();
                executarAlgoritmo(insertionSort, "Insertion Sort (" + gerenciador.nomeTipo(tipo) + ")",
                                   gerenciador.obterVetorPorTipo(tipo), stats);
                break;
            case 5:
                tipo = escolherOrganizacao();
                executarAlgoritmo(shellSort, "Shell Sort (" + gerenciador.nomeTipo(tipo) + ")",
                                   gerenciador.obterVetorPorTipo(tipo), stats);
                break;
            case 6:
                tipo = escolherOrganizacao();
                executarAlgoritmo(quickSort, "Quick Sort (" + gerenciador.nomeTipo(tipo) + ")",
                                   gerenciador.obterVetorPorTipo(tipo), stats);
                break;
            case 7:
                tipo = escolherOrganizacao();
                executarAlgoritmo(heapSort, "Heap Sort (" + gerenciador.nomeTipo(tipo) + ")",
                                   gerenciador.obterVetorPorTipo(tipo), stats);
                break;
            case 8:
                tipo = escolherOrganizacao();
                executarTodos(gerenciador.obterVetorPorTipo(tipo));
                break;
            case 9:
                exportarResultadosCSV(gerenciador);
                break;
            case 10:
                cout << "\nSaindo...\n";
                break;
            default:
                cout << "\n[Erro] Opcao invalida!\n";
                break;
        }
    }

    return 0;
}