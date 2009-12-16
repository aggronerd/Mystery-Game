EXAMPLE_BIN=isometric
OBJF = isometric.o
LIBS=clanApp clanDisplay clanCore clanGL
#LIBS=clanApp clanDisplay clanCore clanGL1
#LIBS=clanApp clanDisplay clanCore clanSDL
#LIBS=clanApp clanDisplay clanCore clanGDI

PACKAGES = $(patsubst %,%-2.1,$(LIBS))
CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread

#EXAMPLE_BIN contains list of example binaries to build

all: $(EXAMPLE_BIN)

$(EXAMPLE_BIN): $(OBJF)
	$(CXX) $(CXXFLAGS) $(OBJF) -o $(EXAMPLE_BIN) `pkg-config --libs $(PACKAGES)` $(EXTRA_LIBS)

clean:
	rm -f $(OBJF) $(EXAMPLE_BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# EOF #

