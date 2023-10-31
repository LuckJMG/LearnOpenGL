FLAGS := -Wall
LIBS :=  -lglfw -ldl -Ilib/glad/include -Ilib

output: src/main.cpp src/shader/shader.cpp
	g++ src/main.cpp src/shader/shader.cpp lib/glad/src/glad.o $(LIBS) $(FLAGS) -o output

clean:
	rm output

run:
	./output

