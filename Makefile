CXX = g++
OUTPUT = sfmlgame1

SFML_DIR = .

CXX_FLAGS = -O0 -g
INCLUDES = -I./src -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CXX) -g $(OBJ_FILES) $(LDFLAGS) -o ./bin/$(OUTPUT)

.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_FILES) ./bin/$(OUTPUT)

run: $(OUTPUT)
	cd bin && ./$(OUTPUT) && cd ..
