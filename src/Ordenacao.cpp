#ifndef ORDENACAO_CPP
#define ORDENACAO_CPP

/* ============================================================
 * Modulo de ordenacao instrumentada.
 *
 * Contem:
 *   - struct Estatisticas (comparacoes, movimentacoes, tempo)
 *   - as 5 funcoes de ordenacao exigidas
 *   - executarAlgoritmo(): roda um algoritmo sobre uma COPIA do
 *     vetor original, mede o tempo e imprime as estatisticas
 *   - executarTodos(): roda os 5 algoritmos e imprime uma tabela
 *     resumo comparativa
 * ============================================================ */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm> // usado apenas para is_sorted() -- verificacao,
                     // nao ordena nada, entao nao viola a regra do
                     // enunciado sobre "nao usar funcoes prontas de
                     // ordenacao"
#include <iomanip>

using namespace std;
using namespace std::chrono;

/* ------------------------------------------------------------
 * Estrutura para armazenar as estatisticas de execucao de um
 * algoritmo de ordenacao, conforme exigido pelo enunciado.
 * ------------------------------------------------------------ */
struct Estatisticas {
    long comparacoes = 0;
    long movimentacoes = 0;
    double tempoExecucao = 0.0; // em segundos
};

typedef void (*FuncaoOrdenacao)(vector<int>&, Estatisticas&);

/* ============================================================
 * ALGORITMOS DE ORDENACAO
 * ============================================================ */

void selectionSort(vector<int>& v, Estatisticas& stats) {
    int menor_indice = 0;
    int tam = v.size();

    for (int i = 0; i < tam - 1; i++) {
        menor_indice = i;
        for (int j = i+1; j < tam; j++) {
            if (v[j] < v[menor_indice]) {
                menor_indice = j;
            }
            stats.comparacoes ++;
        }
        if (menor_indice != i) {
            int aux = v[i];
            v[i] = v[menor_indice];
            v[menor_indice] = aux;
            stats.movimentacoes += 3;
        }
    }
}

void insertionSort(vector<int>& v, Estatisticas& stats) {
    int chave = 0;
    int tam = v.size();

    for (int i = 1; i < tam; i++) {
        chave = v[i];
        stats.movimentacoes ++;
        int j = i-1;
        while (j >= 0) {
            if (v[j] > chave) {
                v[j+1] = v[j];
                j--;
                stats.movimentacoes ++;
                stats.comparacoes ++;
            } else {
                stats.comparacoes ++;
                break;
            }
        }
        v[j+1] = chave;
        stats.movimentacoes ++;
    }
}

void shellSort(vector<int>& v, Estatisticas& stats) {
    int chave = 0;
    int tam = v.size();

    for (int gap = tam / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < tam; i++) {
            chave = v[i];
            stats.movimentacoes ++;
            int j = i - gap;
            while (j >= 0) {
                if (v[j] > chave) {
                    v[j + gap] = v[j];
                    j -= gap;
                    stats.movimentacoes ++;
                    stats.comparacoes ++;
                } else {
                    stats.comparacoes ++;
                    break;
                }
            }
            v[j + gap] = chave;
            stats.movimentacoes ++;
        }
    }
}

/* --- Funcoes auxiliares para Quick Sort --- */
int partition(vector<int>& v, int low, int high, Estatisticas& stats) {
    int pivot = v[high];
    stats.movimentacoes++; // Cópia do valor do pivô

    int i = low - 1;
    for (int j = low; j < high; j++) {
        stats.comparacoes++;
        if (v[j] < pivot) {
            i++;
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            stats.movimentacoes += 3; // Troca completa
        }
    }
    int temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;
    stats.movimentacoes += 3; // Troca do pivô para posição final

    return i + 1;
}

void quickSortRec(vector<int>& v, int low, int high, Estatisticas& stats) {
    if (low < high) {
        int pi = partition(v, low, high, stats);
        quickSortRec(v, low, pi - 1, stats);
        quickSortRec(v, pi + 1, high, stats);
    }
}

void quickSort(vector<int>& v, Estatisticas& stats) {
    if (!v.empty()) {
        quickSortRec(v, 0, v.size() - 1, stats);
    }
}

/* --- Funcoes auxiliares para Heap Sort --- */
void heapify(vector<int>& v, int n, int i, Estatisticas& stats) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        stats.comparacoes++;
        if (v[left] > v[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        stats.comparacoes++;
        if (v[right] > v[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        int temp = v[i];
        v[i] = v[largest];
        v[largest] = temp;
        stats.movimentacoes += 3; // Troca completa
        
        heapify(v, n, largest, stats);
    }
}

void heapSort(vector<int>& v, Estatisticas& stats) {
    int n = v.size();

    // Constrói o Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, stats);
    }

    // Extrai os elementos do heap
    for (int i = n - 1; i > 0; i--) {
        int temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        stats.movimentacoes += 3; // Troca completa
        
        heapify(v, i, 0, stats);
    }
}

/* ============================================================
 * Execucao instrumentada
 * ============================================================ */
void executarAlgoritmo(FuncaoOrdenacao algoritmo, const string& nome,
                        const vector<int>& vetorOriginal, Estatisticas& statsSaida) {
    vector<int> copia = vetorOriginal;

    statsSaida = Estatisticas(); // zera

    auto inicio = high_resolution_clock::now();
    algoritmo(copia, statsSaida);
    auto fim = high_resolution_clock::now();

    statsSaida.tempoExecucao = duration<double>(fim - inicio).count();

    cout << "\n--- " << nome << " ---\n";
    cout << "Comparacoes   : " << statsSaida.comparacoes << "\n";
    cout << "Movimentacoes : " << statsSaida.movimentacoes << "\n";
    cout << "Tempo         : " << statsSaida.tempoExecucao << " s\n";
    cout << "Vetor ordenado corretamente? "
         << (is_sorted(copia.begin(), copia.end()) ? "SIM" : "NAO") << "\n\n";
}

void executarTodos(const vector<int>& vetorOriginal) {
    string nomes[5] = {"Selection Sort", "Insertion Sort", "Shell Sort", "Quick Sort", "Heap Sort"};
    FuncaoOrdenacao funcoes[5] = {selectionSort, insertionSort, shellSort, quickSort, heapSort};
    Estatisticas stats[5];

    cout << "\n========== EXECUTANDO TODOS OS ALGORITMOS (n = " << vetorOriginal.size() << ") ==========\n";

    for (int i = 0; i < 5; i++) {
        executarAlgoritmo(funcoes[i], nomes[i], vetorOriginal, stats[i]);
    }

    cout << "=========================== RESUMO ===========================\n";
    cout << left << setw(16) << "Algoritmo" << right
         << setw(14) << "Comparacoes" << setw(16) << "Movimentacoes" << setw(14) << "Tempo (s)" << "\n";
    for (int i = 0; i < 5; i++) {
        cout << left << setw(16) << nomes[i] << right
             << setw(14) << stats[i].comparacoes
             << setw(16) << stats[i].movimentacoes
             << setw(14) << stats[i].tempoExecucao << "\n";
    }
    cout << "================================================================\n\n";
}

#endif