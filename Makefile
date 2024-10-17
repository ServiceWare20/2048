# Programarea Calculatoarelor, seria CC
# Tema2 - 2048
build: 2048 

2048: 2048.c
	gcc -Wall 2048.c -o 2048 -lSDL2 -lSDL2_mixer -lncurses

clean:
	rm -f 2048

run:
	./2048
