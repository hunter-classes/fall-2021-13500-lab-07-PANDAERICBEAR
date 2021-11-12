main: indent.o
	g++ -o main indent.o

main.o: indent.cpp
	g++ -c indent.cpp

clean:
	rm -f *.o fixed.cpp main
