all:
	g++ -Wall -O3 -o PPSO main.cc

clean:
	rm -f main *.o
