build:
	g++ -Wall -std=c++17 -I"./libs/" src/*.cpp -lSDL2 -llua -o manatee;
run:
	./manatee
clean:
	rm manatee
