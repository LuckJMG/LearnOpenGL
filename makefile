FLAGS := -Wall
LIBS :=  -lglfw -lassimp -ldl -Ilib/glad/include -Ilib

output: src/main.cpp src/shader/shader.cpp src/camera/camera.cpp src/shader/shader.h src/camera/camera.h src/model/model.cpp src/model/mesh.cpp src/model/model.hpp src/model/mesh.hpp
	g++ src/main.cpp src/shader/shader.cpp src/camera/camera.cpp src/model/model.cpp src/model/mesh.cpp lib/glad/src/glad.o $(LIBS) $(FLAGS) -o output

clean:
	rm output

run:
	./output

