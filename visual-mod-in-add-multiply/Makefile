build: main.o
	g++ -o main main.o

run: build
	./main

main.o: main.cpp
	g++ -c main.cpp

.PHONY: clean
clean:
	-rm -rf ./*.o
