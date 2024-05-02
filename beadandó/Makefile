objects:	
	gcc -c square.c
	gcc -c obstacle.c
	gcc -c whitesquare.c
make:
	gcc -o game main.c obstacle.o square.o whitesquare.o -lSDL2 -lopengl32
run:
	./game