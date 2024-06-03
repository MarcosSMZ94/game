build: 
	gcc -Wall -std=c99 ./src/*.c -lSDL2main -lSDL2 -I/usr/include/SDL2 -o game

run:
	./game

clean:
	rm game