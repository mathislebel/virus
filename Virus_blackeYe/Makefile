CXX = g++
CXXFLAGS = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = phishing_program

$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(BIN_DIR)/$(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC)

