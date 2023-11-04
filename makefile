FLAGS := -Wall
LIBS :=  -lglfw -ldl -Ilib/glad/include -Ilib

output: src/main.cpp src/shader/shader.cpp src/camera/camera.cpp src/shader/shader.h src/camera/camera.h
	g++ src/main.cpp src/shader/shader.cpp src/camera/camera.cpp lib/glad/src/glad.o $(LIBS) $(FLAGS) -o output

clean:
	rm output

run:
	./output

