output: ./src/main.cpp
	g++ src/main.cpp glad/src/glad.c -Iglad/include -lglfw -ldl -Wall -o output

clean:
	rm output

run:
	./output

