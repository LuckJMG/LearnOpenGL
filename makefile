FLAGS := -Wall
LIBS :=  -lglfw -ldl -Ilib/glad/include -Ilib/glm -Ilib

output: src/main.cpp src/shader/shader.cpp glad.o
	g++ src/main.cpp src/shader/shader.cpp glad.o $(LIBS) $(FLAGS) -o output

glad.o:
	g++ -c lib/glad/src/glad.c -lglfw -ldl -Ilib/glad/include

clean:
	rm output *.o

run:
	./output

