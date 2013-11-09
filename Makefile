############################################################################
#	MakeFile fort Compiling The Kcwarto Core And LibKcwarto
#
############################################################################
# Make Lib
###########################################################################
#	Compiling  Variables 
##########################################################################
#CPPFLAGS args for preprocesser
#CXXFLAGS args for compiler C++
##############################
#	Compiler
##############################
# CXX = g++
CXX = clang++

############################
#	Flags
###########################

# DEBUG 
#CXXFLAGS = -O0 -g -Weverything 
# FAST
# CXXFLAGS = -O2
# XtraFAST
 CXXFLAGS = -Ofast

# Compile tout 
all	:	libkcwarto.a libkcwarto.so console
# Compile le binaire
console	:	libkcwarto.a  main.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o quarto main.o libkcwarto.a
main.o	: main.cxx Jeu.h Menu.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o main.o -c main.cxx
#Compile les Libraries
libkcwarto.a	: jeu.o menu.o minmax.o plateau.o pioche.o coup.o kase.o pion.o
	ar rcs libkcwarto.a *.o

libkcwarto.so	: jeu.o menu.o minmax.o plateau.o pioche.o coup.o kase.o pion.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o libkcwarto.so -shared -fPIC pion.o kase.o coup.o pioche.o plateau.o  minmax.o menu.o jeu.o

#Compile les .o
jeu.o	: Jeu.cpp Plateau.h Pioche.h MinMax.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o jeu.o -c Jeu.cpp

menu.o	: Menu.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o menu.o -c Menu.cpp

minmax.o	: MinMax.cpp Plateau.h Pioche.h Coup.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o minmax.o -c MinMax.cpp

plateau.o	: Plateau.cpp Kase.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o plateau.o -c Plateau.cpp

pioche.o	: Pioche.cpp Pion.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o pioche.o -c Pioche.cpp

coup.o	: Coup.cpp Pion.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o coup.o -c Coup.cpp

kase.o	: Kase.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o kase.o -c Kase.cpp

pion.o	: Pion.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o pion.o -c Pion.cpp

clean	: 
	rm -rf *.o *.a *.so

mrproper:	clean
	rm -rf quarto
