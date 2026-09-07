# ==========================================
# Makefile - Laboratório 1: Algoritmos de Ordenação
# ==========================================

# Definindo o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3

# Diretórios e arquivos
SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp
TARGET = programa

# Regra padrão executada ao rodar apenas 'make'
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(SRC)
	@echo "Compilando o projeto..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "Compilação concluída com sucesso! Executável '$(TARGET)' gerado."

# Regra para limpar os arquivos binários gerados
clean:
	@echo "Limpando arquivos binários..."
	rm -f $(TARGET)
	@echo "Limpeza concluída!"

# Declara que 'all' e 'clean' não são arquivos
.PHONY: all clean