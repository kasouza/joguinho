OBJS := stb_image.o
CFLAGS := -Iinclude

ALL: libstb_image.a

libstb_image.a: $(OBJS)
	ar -rc $@ $^

clean:
	-rm libstb_image.a
	-find -type f -name "*.o" -exec rm {} \;
