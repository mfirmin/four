UNAME := $(shell uname)

INCLUDELOCAL = -I/usr/local/include -O3
ifeq ($(UNAME), Darwin)
	LIBOPT = -L/opt/X11/lib -L/usr/local/lib -lGLU -lGL -lGLC -lm -lode
	FLTKLD = -L/usr/local/lib -lfltk -lpthread -framework Cocoa
	FLTKCXX = -I/usr/local/include -I/usr/local/include/FL/images -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
endif
ifeq ($(UNAME), Linux)
	LIBOPT = -L/usr/X11R6/lib -lGLU -lGL -lGLC -lm -lode
	FLTKCXX = -I/usr/local/include -I/usr/local/include/FL/images -I/usr/local/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
	FLTKLD = -L/usr/local/lib -lfltk -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11
endif

GVCFLAGS = `pkg-config libgvc --cflags` -Wall -g -O2
GVLDFLAGS = `pkg-config libgvc --libs`

GLFW = `pkg-config --cflags glfw3`
GLFW2 = `pkg-config --static --libs glfw3`

CC = g++ -std=c++0x

all: world Makefile

clean: 
	rm *.o world

world: world.o ode.o entity.o geometry.o plane.o box.o renderer.o utils.o
	$(CC) $(GLFW) -o world *.o $(GLFW2) $(INCLUDELOCAL) $(LIBOPT)  

plane.o: ../src/entity/Plane.h ../src/entity/Plane.cpp ../src/entity/Geometry.cpp
	$(CC) -c ../src/entity/Plane.cpp -o plane.o $(LIBOPT) $(INCLUDELOCAL)

renderer.o: ../src/entity/Entity.h ../src/entity/Geometry.h ../src/renderer/Renderer.cpp ../src/renderer/Renderer.h ../src/entity/Box.h ../src/entity/Plane.h ../src/utils/utils.h
	$(CC) -c ../src/renderer/Renderer.cpp -o renderer.o $(LIBOPT) $(INCLUDELOCAL)

ode.o: ../src/physics/ODEWrapper.h ../src/physics/ODEWrapper.cpp ../src/math/VECTOR.h
	$(CC) -c ../src/physics/ODEWrapper.cpp -o ode.o $(LIBOPT) $(INCLUDELOCAL)

entity.o: ../src/entity/Entity.h ../src/Entity/Entity.cpp  ../src/utils/utils.h
	$(CC) -c ../src/entity/Entity.cpp -o entity.o $(LIBOPT) $(INCLUDELOCAL)

geometry.o: ../src/entity/Geometry.h ../src/entity/Geometry.cpp
	$(CC) -c ../src/entity/Geometry.cpp -o geometry.o $(LIBOPT) $(INCLUDELOCAL)

box.o: ../src/entity/Box.h ../src/entity/Box.cpp ../src/entity/Geometry.h
	$(CC) -c ../src/entity/Box.cpp -o box.o $(LIBOPT) $(INCLUDELOCAL)

utils.o: ../src/utils/utils.h ../src/utils/utils.cpp
	$(CC) -c ../src/utils/utils.cpp -o utils.o $(LIBOPT) $(INCLUDELOCAL)

world.o: ../src/world/world.h ../src/world/world.cpp ../src/math/VECTOR.h ../src/entity/entity.h ../src/physics/ODEWrapper.h
	$(CC) -c ../src/world/World.cpp $(LIBOPT) $(INCLUDELOCAL)
