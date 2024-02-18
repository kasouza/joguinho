# PKGS to be included using pkg-config (optional)
#PKGS := ncurses

LIBS := glad glfw3 stb_image

# Executables
EXEC := joguinho
TEST := "test_$(EXEC)"


# Object files
OBJS := $(addprefix src/,ecs.o data_structures/dynarr.o data_structures/map.o data_structures/bitset.o)
EXEC_OBJS := $(addprefix src/,main.o)
TEST_OBJS := $(addprefix test/,main.o test.o data_structures/dynarr.o data_structures/map.o data_structures/bitset.o)


# Configs
INCLUDE_DIRS := `(echo "$(addprefix -Ilibs/, $(LIBS))" | awk -v OFS="\n" '$$1=$$1' | sed 's/$$/\/include /')`
CFLAGS := -g -O0 -Iinclude $(INCLUDE_DIRS)
LDFLAGS := $(addprefix -Llibs/, $(LIBS)) $(addprefix -l, $(LIBS))

ifneq ($(PKGS),)
	CFLAGS += $(shell pkg-config --cflags $(PKGS))
	LDFLAGS += $(shell pkg-config --libs $(PKGS))
endif

# Targets
all: libs/build_libs $(EXEC) $(TEST)
	echo $(CFLAGS)

libs/build_libs:
	./libs/build.sh
	touch libs/build_libs

$(EXEC): $(EXEC_OBJS) $(OBJS)
	cc -o $@ $^ $(LDFLAGS)

$(TEST): $(TEST_OBJS) $(OBJS)
	cc -o $@ $^ $(LDFLAGS)

-include $(OBJS:.o=.d)
-include $(EXEC_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)

%.o: %.c
	echo $(addprefix -Ilibs/, $(LIBS))
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	-rm $(EXEC)
	-rm $(TEST)
	-find -type f -name *.d -o -name *.o -exec rm {} \;
