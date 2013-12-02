IDIR = ../include
LIBDIR = ../../lib
CC = g++

LGLFW = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -L $(LIBDIR)/glfw/lib/
IGLFW = -I $(LIBDIR)/glfw/include/
IGLM = -I $(LIBDIR)/glm/

CFLAGS = -I $(IDIR)

prog: main.o simulation.o graphics_engine.o shaders.o
	$(CC) $(CFLAGS) -o prog main.o simulation.o graphics_engine.o shaders.o $(LGLFW)

main.o: main.cpp $(IDIR)/simulation.hpp
	$(CC) $(CFLAGS) -c main.cpp $(IGLM) $(IGLFW)

simulation.o: simulation.cpp $(IDIR)/simulation.hpp $(IDIR)/graphics_engine.hpp
	$(CC) $(CFLAGS) -c simulation.cpp $(IGLFW)

graphics_engine.o: graphics_engine.cpp $(IDIR)/graphics_engine.hpp $(IDIR)/shaders.hpp
	$(CC) $(CFLAGS) -c graphics_engine.cpp $(IGLM) $(IGLFW)

shaders.o: shaders.cpp $(IDIR)/shaders.hpp
	$(CC) $(CFLAGS) -c shaders.cpp $(IGLFW)

#prog: tut01.o simulation.o world.o scene_graph.o render_consumer.o shaders.o node.o mesh.o file_helpers.o
#	$(CC) $(CFLAGS) -o tut01 tut01.o simulation.o world.o scene_graph.o render_consumer.o shaders.o node.o mesh.o file_helpers.o

#simulation.o: simulation.cpp simulation.hpp world.hpp node.hpp mesh.hpp render_consumer.hpp
#	$(CC) $(CFLAGS) -c simulation.cpp -I lib/glm/

#world.o: world.cpp world.hpp scene_graph.hpp node.hpp
#	$(CC) $(CFLAGS) -c world.cpp -I lib/glm/

#scene_graph.o: scene_graph.cpp scene_graph.hpp node.hpp
#	$(CC) $(CFLAGS) -c scene_graph.cpp -I lib/glm/

#render_consumer.o: render_consumer.cpp render_consumer.hpp shaders.hpp mesh.hpp node.hpp world.hpp
#	$(CC) $(CFLAGS) -c render_consumer.cpp -I lib/glm/


#node.o: node.cpp node.hpp
#	$(CC) $(CFLAGS) -c node.cpp -I lib/glm/

#mesh.o: mesh.cpp mesh.hpp file_helpers.hpp
#	$(CC) $(CFLAGS) -c mesh.cpp

#file_helpers.o: file_helpers.cpp file_helpers.hpp
#	$(CC) $(CFLAGS) -c file_helpers.cpp




#material.o: material.cpp material.hpp
#	$(CC) $(CFLAGS) -c material.cpp


clean:
	rm -f *.o prog
