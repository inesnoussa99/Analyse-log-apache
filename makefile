# Variables
CXX = g++ # -DMAP
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -g
LDFLAGS = 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Liste des fichiers sources et des objets correspondants
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/analog

# Règles par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS) $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Suppression des fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Remettre le projet à zéro
mrproper: clean
	rm -rf $(BIN_DIR)