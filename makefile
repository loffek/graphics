tut01: tut01.o simulation.o world.o scene_graph.o render_consumer.o shaders.o node.o mesh.o file_helpers.o
	g++ $(CFLAGS) -o tut01 tut01.o simulation.o world.o scene_graph.o render_consumer.o shaders.o node.o mesh.o file_helpers.o -lglfw3 -lGLEW -framework Cocoa -framework OpenGL -framework IOKit

tut01.o: tut01.cpp simulation.hpp
	g++ $(CFLAGS) -c tut01.cpp -I ../glm-0.9.4.0/

simulation.o: simulation.cpp simulation.hpp world.hpp node.hpp mesh.hpp render_consumer.hpp
	g++ $(CFLAGS) -c simulation.cpp -I ../glm-0.9.4.0/

world.o: world.cpp world.hpp scene_graph.hpp node.hpp
	g++ $(CFLAGS) -c world.cpp -I ../glm-0.9.4.0/

scene_graph.o: scene_graph.cpp scene_graph.hpp node.hpp
	g++ $(CFLAGS) -c scene_graph.cpp -I ../glm-0.9.4.0/

render_consumer.o: render_consumer.cpp render_consumer.hpp shaders.hpp mesh.hpp node.hpp world.hpp
	g++ $(CFLAGS) -c render_consumer.cpp -I ../glm-0.9.4.0/

shaders.o: shaders.cpp shaders.hpp node.hpp
	g++ $(CFLAGS) -c shaders.cpp

node.o: node.cpp node.hpp
	g++ $(CFLAGS) -c node.cpp -I ../glm-0.9.4.0/

mesh.o: mesh.cpp mesh.hpp file_helpers.hpp
	g++ $(CFLAGS) -c mesh.cpp

file_helpers.o: file_helpers.cpp file_helpers.hpp
	g++ $(CFLAGS) -c file_helpers.cpp




material.o: material.cpp material.hpp
	g++ $(CFLAGS) -c material.cpp


clean:
	rm -f *.o tut01
