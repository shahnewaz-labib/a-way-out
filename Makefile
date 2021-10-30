# for .cpp files only
SRCDIR=src

# Classes with Header .h and .cpp files
CLASS_DIR=$(SRCDIR)/ClassDef
CLASS_HEADERS=$(SRCDIR)/include

OBDIR=obj
IDIR=

# Exclude a file from this pattern matching
_EXCLUDE=
EXCLUDE=$(patsubst %.cpp,$(OBDIR)/%.o,$(_EXCLUDE))


OBJ_CPP=$(patsubst $(SRCDIR)/%.cpp,$(OBDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
OBJ_CLASS=$(patsubst $(CLASS_DIR)/%.cpp,$(OBDIR)/%.o,$(wildcard $(CLASS_DIR)/*.cpp))
_OBJ=$(OBJ_CPP) $(OBJ_CLASS)


OBJ=$(filter-out $(EXCLUDE),$(_OBJ))

LIBS=-lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
CC=g++ --std=c++17

Program: $(OBJ)
	$(CC) $^ -o $@ $(IDIR) $(LIBS)

# $(OBDIR)/main.o: $(SRCDIR)/main.cpp
#	$(CC) -c $^ -o $@

$(OBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@

$(OBDIR)/%.o: $(CLASS_DIR)/%.cpp $(CLASS_HEADERS)/%.hpp
	$(CC) -c $< -o $@

clean:
	rm $(OBDIR)/*.o
	rm Program
