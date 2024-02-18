GLAD_OBJS := src/gl.o
CFLAGS += -Iinclude

all: libglad.a

libglad.a: $(GLAD_OBJS)
	ar -rc $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o

clean:
	-rm libglad.a
	-find -type f -name "*.o" -exec rm {} \;
