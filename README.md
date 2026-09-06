# Laboratório 1 - Algoritmos de Ordenação 📊

![C++](https://img.shields.io/badge/C%2B%2B-000080?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Estruturas de Dados II](https://img.shields.io/badge/Estruturas_de_Dados-ADD8E6?style=for-the-badge&logoColor=black)

## 📌 Sobre o Projeto
Este projeto foi desenvolvido como requisito do Laboratório 1 da disciplina de Estruturas de Dados II do curso de Sistemas de Informação. O objetivo principal é a implementação e a análise comparativa de desempenho de diferentes algoritmos de ordenação em linguagem C/C++.

O sistema processa conjuntos de dados numéricos gerados dinamicamente e realiza a medição empírica de complexidade, analisando o comportamento teórico versus o observado.

## 📂 Estrutura do Projeto
```text
📦 sorting-algorithms-analysis
├── 📁 docs/           # Documentação teórica e tabelas de resultados (.csv) exportadas
├── 📁 src/            # Código-fonte C++ principal
│   ├── Dados.cpp      # Regras de geração, gestão e manipulação dos dados
│   ├── main.cpp       # Ponto de entrada, menu interativo e automação de testes
│   └── Ordenacao.cpp  # Implementação e instrumentação dos algoritmos
├── Makefile           # Script de automação de compilação (Linux)
└── README.md          # Documentação do repositório
```

## ⚙️ Funcionalidades
O programa possui um menu interativo de terminal que permite:
- **Gerar conjuntos de dados** de tamanho N (1.000, 10.000, 50.000 e 100.000 elementos).
- **Configurar a organização inicial**: Dados aleatórios, previamente ordenados, ordem inversa ou parcialmente ordenados.
- **Exibir os dados** gerados em um formato de tabela paginada para conferência.
- **Executar ordenações individuais** para testes isolados.
- **Execução em Lote (Automática):** Realiza todos os testes possíveis sequencialmente e sem necessidade de interação humana.

## 🧮 Algoritmos Implementados
O projeto implementa os seguintes métodos de ordenação manualmente, proibindo o uso de funções de ordenação de bibliotecas prontas:
- `Selection Sort`
- `Insertion Sort`
- `Shell Sort`
- `Quick Sort`
- `Heap Sort`

## 📊 Instrumentação e Exportação (CSV)
Para garantir rigor absoluto na comparação empírica, o sistema isola as execuções trabalhando sobre cópias exatas do vetor original. 

Para cada algoritmo executado, o sistema coleta detalhadamente:
1. **Comparações:** Número de vezes que duas chaves de dados do vetor foram comparadas.
2. **Movimentações:** Número de deslocamentos, cópias ou trocas (*swaps*) de elementos.
3. **Tempo de Execução:** Medido em segundos com alta precisão.

**Geração de Relatórios Automáticos**
Ao selecionar a funcionalidade de exportação no menu (Opção 9), o sistema assume o controle, gera os dados silenciosamente e testa as **80 combinações possíveis** (5 algoritmos × 4 tamanhos × 4 cenários de organização). O resultado final é serializado e salvo no arquivo `docs/resultados.csv`, formatado com o cabeçalho padrão e pronto para anexação em planilhas ou relatórios de análise teórica.

*(A análise comparativa e as respostas ao questionário de complexidade do laboratório encontram-se no documento de relatório PDF na pasta `/docs`)*.

## 🚀 Como Executar

É necessário possuir um compilador C++ (como o `g++`) configurado no seu ambiente. Recomenda-se a compilação e execução via terminal em sistemas Linux.

1. **Clone este repositório:**
   ```bash
   git clone [https://github.com/guilhermegma/sorting-algorithms-analysis.git](https://github.com/guilhermegma/sorting-algorithms-analysis.git)
   ```

2. **Acesse a pasta principal do projeto:**
   ```bash
   cd sorting-algorithms-analysis
   ```

3. **Compile o código-fonte:**
   *Se você estiver usando o compilador G++ diretamente:*
   ```bash
   g++ src/main.cpp -o programa
   ```
   *Se o `Makefile` já estiver configurado, basta rodar:*
   ```bash
   make
   ```

4. **Execute o programa gerado:**
   ```bash
   ./programa
   ```
