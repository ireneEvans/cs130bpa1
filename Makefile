

all: main


main: main.o
	g++ -o main main.cpp
main.o: main.cpp 
	g++ -c main.cpp

git:
	git add .
	git commit -m"testing push"
	git push origin main




clean:
	-rm main.o
