

all: main

main.o: main.cpp
	g++ -c main.cpp
main: main.o
	g++ main.o -o main

git:
	git add .
	git commit -m"testing push"
	git push origin master




clean:
	-rm main.o
