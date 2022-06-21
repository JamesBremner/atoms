#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./include \
	-I../ravencode/pub/src \
	-I../raven-set \
	-I../boost/boost1_78

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

OPT = -O2
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJ = \
	$(ODIR)/main.o \
	$(ODIR)/cRunWatch.o

### COMPILE

$(ODIR)/cRunWatch.o :
	g++ -o $@ -c ../raven-set/cRunWatch.cpp \
	$(INCS) $(CCflags) 

$(ODIR)/%.o: %.cpp  
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)

bats: $(OBJ)
	g++ $(OPT) \
	-o bin/starter.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

