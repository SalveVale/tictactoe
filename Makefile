.PHONEY: generate clean

generate:
	g++ -c tic.cpp
	g++ tic.o -o tictactoe -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o