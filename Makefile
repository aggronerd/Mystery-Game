GAME_BIN=./bin/isometric
EDITOR_BIN=./bin/plot_editor

GAME_DIR=./source/game
EDITOR_DIR=./source/editor
MYSTERY_XML_DIR=./source/mystery_xml

MYSTERY_XML_OBJF= \
$(MYSTERY_XML_DIR)/Decision.o \
$(MYSTERY_XML_DIR)/Decisions.o \
$(MYSTERY_XML_DIR)/DiscreteRange.o \
$(MYSTERY_XML_DIR)/Option.o \
$(MYSTERY_XML_DIR)/Options.o \
$(MYSTERY_XML_DIR)/Plot.o \
$(MYSTERY_XML_DIR)/Range.o \
$(MYSTERY_XML_DIR)/Result.o
GAME_OBJF = \
$(GAME_DIR)/isometric.o \
$(GAME_DIR)/App.o \
$(GAME_DIR)/RandomGenerator.o \
$(GAME_DIR)/IsometricConversions.o \
$(GAME_DIR)/IsometricGrid.o \
$(GAME_DIR)/MovableGameObject.o \
$(GAME_DIR)/Overlay.o \
$(GAME_DIR)/PlayerCharacter.o \
$(GAME_DIR)/RandomGenerator.o \
$(GAME_DIR)/World.o $(MYSTERY_XML_OBJF)
EDITOR_OBJF = \
$(EDITOR_DIR)/plot_editor.o \
$(EDITOR_DIR)/MainWindow.o $(MYSTERY_XML_OBJF)

#Other graphical libraries: clanGL1, clanSDL, clanGDI
GAME_LIBS=clanApp clanDisplay clanCore clanGL clanSound clanVorbis clanMikMod
EDITOR_LIBS=

GAME_PACKAGES = $(patsubst %,%-2.1,$(GAME_LIBS))
GAME_CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread

all: $(GAME_BIN) $(EDITOR_BIN)

$(GAME_BIN): $(GAME_OBJF)
	$(CXX) $(GAME_CXXFLAGS) $(GAME_OBJF) -o $(GAME_BIN) `pkg-config --libs $(GAME_PACKAGES)` $(EXTRA_LIBS)

$(EDITOR_BIN): $(EDITOR_OBJF)
	$(CXX) $(EDITOR_OBJF) -o $(EDITOR_BIN)

clean:
	rm -f $(OBJF) $(MAIN_BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# EOF #

