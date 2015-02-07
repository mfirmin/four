UNAME := $(shell uname)

CC = g++ -std=c++0x

BINDIR = ./bin
BUILDDIR = ./build
SRCDIR = ./src
LIB = ./lib
INC = -Iinclude

TARGET=./bin/world

SRCEXT=cpp
SOURCES= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

LIBOBJS = $(shell find $(LIB) -type f -name *.o)

ifeq ($(UNAME), Darwin)
	LDFLAGS = -L/opt/X11/lib -L/usr/local/lib -lGLU -lGL -lm -lode
endif
ifeq ($(UNAME), Linux)
	LDFLAGS = -L/usr/X11R6/lib -lGLU -lGL -lm -lode
endif

GLFWCFLAGS = `pkg-config --cflags glfw3`
GLFWLDFLAGS = `pkg-config --static --libs glfw3`

all: $(TARGET) Makefile

clean: 
	@echo " Cleaning";
	@echo " rm -r $(BUILDDIR) $(TARGET)"; rm -r $(BUILDDIR) $(TARGET)

#LINK
$(TARGET): $(OBJECTS)
	@echo " Linking . . ."
	$(CC) $(GLFWCFLAGS) -o $(TARGET) $^ $(LIBOBJS) $(GLFWLDFLAGS) $(LDFLAGS)

#COMPILE
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	@echo " $(CC) -c -o $@ $< $(INC)"; $(CC) -c -o $@ $< $(INC)
