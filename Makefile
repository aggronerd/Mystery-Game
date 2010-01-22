MAIN_BIN=isometric
OBJF = isometric.o App.o World.o RandomGenerator.o
LIBS=clanApp clanDisplay clanCore clanGL clanSound clanVorbis clanMikMod
#LIBS=clanApp clanDisplay clanCore clanGL1 clanSound clanVorbis clanMikMod
#LIBS=clanApp clanDisplay clanCore clanSDL clanSound clanVorbis clanMikMod
#LIBS=clanApp clanDisplay clanCore clanGDI clanSound clanVorbis clanMikMod

PACKAGES = $(patsubst %,%-2.1,$(LIBS))
CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread

all: $(MAIN_BIN)

$(MAIN_BIN): $(OBJF)
	$(CXX) $(CXXFLAGS) $(OBJF) -o $(MAIN_BIN) `pkg-config --libs $(PACKAGES)` $(EXTRA_LIBS)

clean:
	rm -f $(OBJF) $(MAIN_BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# EOF #

