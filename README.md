# Laboratório 1 - Algoritmos de Ordenação 📊

![C++](https://img.shields.io/badge/C%2B%2B-000080?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Estruturas de Dados II](https://img.shields.io/badge/Estruturas_de_Dados-ADD8E6?style=for-the-badge&logoColor=black)

## 📌 Sobre o Projeto
Este projeto foi desenvolvido como requisito do Laboratório 1 da disciplina de Estruturas de Dados II do curso de Sistemas de Informação[cite: 1]. O objetivo principal é a implementação e a análise comparativa de desempenho de diferentes algoritmos de ordenação em linguagem C/C++[cite: 1].

O sistema processa conjuntos de dados numéricos gerados dinamicamente e realiza a medição empírica de complexidade, analisando o comportamento teórico versus o observado[cite: 1].

## ⚙️ Funcionalidades
O programa possui um menu interativo que permite[cite: 1]:
- **Gerar conjuntos de dados** de tamanho $N$ (ex: 1.000, 10.000, 50.000, 100.000 elementos)[cite: 1].
- **Configurar a organização inicial**: Dados aleatórios, previamente ordenados, ordem inversa ou parcialmente ordenados[cite: 1].
- **Exibir os dados** gerados[cite: 1].
- **Executar ordenações individuais ou em lote** (comparação completa)[cite: 1].

## 🧮 Algoritmos Implementados
O projeto implementa os seguintes métodos de ordenação sem o uso de bibliotecas prontas[cite: 1]:
- `Selection Sort`[cite: 1]
- `Insertion Sort`[cite: 1]
- `Shell Sort`[cite: 1]
- `Quick Sort`[cite: 1]
- `Heap Sort`[cite: 1]

## 📊 Instrumentação e Análise
Para garantir rigor na comparação, o sistema isola as execuções trabalhando sobre cópias idênticas do vetor original[cite: 1]. Para cada algoritmo executado, o sistema coleta e exibe[cite: 1]:
1. Número de comparações realizadas[cite: 1]
2. Número de movimentações/trocas de elementos[cite: 1]
3. Tempo total de execução[cite: 1]

*(A análise teórica e as respostas ao questionário do laboratório encontram-se no documento de relatório na pasta `/docs`)*.

## 🚀 Como Executar
1. Clone este repositório:
   ```bash
   git clone [https://github.com/guilhermegma/nome-do-repositorio.git](https://github.com/guilhermegma/nome-do-repositorio.git)
