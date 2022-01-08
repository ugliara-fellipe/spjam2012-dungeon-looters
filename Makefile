CPP := g++
INC := src
SRC := src
OBJ := build
LDFLAGS := -L.  -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_video -lallegro_audio -lallegro_physfs -lallegro_primitives -lallegro_acodec -lallegro_main


SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

build: env compile

rebuild: clean build

env:
	mkdir -p build

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CPP) -c -I $(INC) $< -o $@

compile: $(OBJECTS)
	$(CPP) -o dungeon-looters $^ $(LDFLAGS)

clean :
	rm -rf build dungeon-looters