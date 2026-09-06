#include <iostream>
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
        cout << "9. Encerrar o programa\n";
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
                cout << "\nSaindo...\n";
                break;
            default:
                cout << "\n[Erro] Opcao invalida!\n";
                break;
        }
    }

    return 0;
}