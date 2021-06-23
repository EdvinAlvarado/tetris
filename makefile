CC = g++
WFLAGS = -Wall -Wextra 
CPPFLAGS = -std=c++14 $(WFLAGS)
LDFLAGS = -lSDL2
OBJECT = main.o tetris.o IO.o board.o

tetris: $(OBJECT)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o tetris $(OBJECT)

main.o: main.cpp tetris.hpp IO.hpp board.hpp screen.hpp
	$(CC) $(CPPFLAGS) -c main.cpp

tetris.o: tetris.cpp tetris.hpp
	$(CC) $(CPPFLAGS) -c tetris.cpp

IO.o: IO.cpp IO.hpp board.hpp screen.hpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c IO.cpp

board.o: board.cpp board.hpp tetris.hpp IO.hpp screen.hpp
	$(CC) $(CPPFLAGS) -c board.cpp

clean:
	rm *.o tetris 
