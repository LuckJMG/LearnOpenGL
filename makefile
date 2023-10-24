FLAGS := -Wall
LIBS := -Ilib/glad/include -Ilib -lglfw -ldl

output: src/main.cpp src/shader/shader.cpp glad.o
	g++ src/main.cpp src/shader/shader.cpp glad.o $(LIBS) $(FLAGS) -o output

glad.o:
	g++ -c lib/glad/src/glad.c $(LIBS)

clean:
	rm output *.o

run:
	./output

