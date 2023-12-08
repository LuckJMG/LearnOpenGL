FLAGS := -Wall
LIBS :=  -lglfw -lassimp -ldl -Ilib/glad/include -Ilib
ENGINE := src/engine/*.cpp src/engine/utils/*.cpp src/engine/components/*.cpp src/engine/objects/*.cpp

output: src/main.cpp $(ENGINE)
	g++ src/main.cpp $(ENGINE) lib/glad/src/glad.o $(LIBS) $(FLAGS) -o output

clean:
	rm output

run:
	./output

