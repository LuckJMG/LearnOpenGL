FLAGS := -Wall
LIBS :=  -lglfw -lassimp -ldl -Ilib/glad/include -Ilib

output: src/main.cpp src/engine/*
	g++ src/main.cpp src/engine/*.cpp lib/glad/src/glad.o $(LIBS) $(FLAGS) -o output

clean:
	rm output

run:
	./output

