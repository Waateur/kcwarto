all: quarto

quarto: main.o jeu.o menu.o minmax.o plateau.o pioche.o coup.o kase.o pion.o
        g++ -o quarto *.o

main.o : main.cpp Jeu.h Menu.h
        g++ -o main.o -c main.cpp -W -Wall

jeu.o : Jeu.cpp Plateau.h Pioche.h MinMax.h
        g++ -o jeu.o -c Jeu.cpp -W -Wall

menu.o : Menu.cpp
        g++ -o menu.o -c Menu.cpp -W -Wall

minmax.o : MinMax.cpp Plateau.h Pioche.h Coup.h
        g++ -o minmax.o -c MinMax.cpp -W -Wall

plateau.o : Plateau.cpp Kase.h
        g++ -o plateau.o -c Plateau.cpp -W -Wall

pioche.o : Pioche.cpp Pion.h
        g++ -o pioche.o -c Pioche.cpp -W -Wall

coup.o : Coup.cpp Pion.h
        g++ -o coup.o -c Coup.cpp -W -Wall

kase.o : Kase.cpp
        g++ -o kase.o -c Kase.cpp -W -Wall

pion.o : Pion.cpp
        g++ -o pion.o -c Pion.cpp -W -Wall

clean : rm -rf *.o

mrproper: clean
        rm -rf quarto
