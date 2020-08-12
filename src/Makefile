CC=clang++
CFLAGS=-I.

LIBS=-lGLEW -lGLU -lGL -lglfw

DEPS=Camera.h Chunk.h DirectionalLight.h Light.h Material.h Shader.h Window.h
OBJS=Camera.o Chunk.o DirectionalLight.o Light.o main.o Material.o Shader.o Window.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

proccraft: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~ 