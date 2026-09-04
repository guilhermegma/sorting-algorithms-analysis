#include <iostream>
#include "Dados.cpp"

using namespace std;

int main() {
    Dados gerenciador;
    int opcao = 0;

    while (opcao != 3) {
        cout << "\n==============================\n";
        cout << "        MENU PRINCIPAL        \n";
        cout << "==============================\n";
        cout << "1. Gerar/Inserir Dados\n";
        cout << "2. Exibir Dados\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                gerenciador.inserirDados();
                break;
            case 2:
                gerenciador.exibirDados();
                break;
            case 3:
                cout << "\nSaindo...\n";
                break;
            default:
                cout << "\n[Erro] Opcao invalida!\n";
                break;
        }
    }

    return 0;
}