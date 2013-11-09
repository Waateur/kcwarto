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
CXXFLAGS = -O0 -g -Weverything -Werror
# FAST
# CXXFLAGS = -O2
# XtraFAST
# CXXFLAGS = -Ofast


all	:	console

console	:	quarto

quarto	:	main.o jeu.o menu.o minmax.o plateau.o pioche.o coup.o kase.o pion.o
	clang++ -o quarto *.o

main.o	: main.cxx Jeu.h Menu.h
	clang++ -o main.o -c main.cxx

jeu.o	: Jeu.cpp Plateau.h Pioche.h MinMax.h
	clang++ -o jeu.o -c Jeu.cpp

menu.o	: Menu.cpp
	clang++ -o menu.o -c Menu.cpp

minmax.o	: MinMax.cpp Plateau.h Pioche.h Coup.h
	clang++ -o minmax.o -c MinMax.cpp

plateau.o	: Plateau.cpp Kase.h
	clang++ -o plateau.o -c Plateau.cpp

pioche.o	: Pioche.cpp Pion.h
	clang++ -o pioche.o -c Pioche.cpp

coup.o	: Coup.cpp Pion.h
	clang++ -o coup.o -c Coup.cpp

kase.o	: Kase.cpp
	clang++ -o kase.o -c Kase.cpp

pion.o	: Pion.cpp
	clang++ -o pion.o -c Pion.cpp

clean	: 
	rm -rf *.o

mrproper:	clean
	rm -rf quarto
