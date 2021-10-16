

all: main



main: 
	g++ -std=c++11 -o main main.cpp 

git:
	git add .
	git commit -m"testing push"
	git push origin main




clean:
	-rm main.o
