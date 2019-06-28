CC = i686-w64-mingw32-gcc
CPP = i686-w64-mingw32-g++
DLLTOOL = i686-w64-mingw32-dlltool

CC_64 = x86_64-w64-mingw32-gcc
CPP_64 = x86_64-w64-mingw32-g++
DLLTOOL_64 = x86_64-w64-mingw32-dlltool

STRIP = strip

CFLAGS = -O2 -pipe -fno-ident -fvisibility=hidden -Icapnhook
LDFLAGS = -static -static-libgcc -static-libgcc

OMNIMIX_VERSION = 1.0.0

DLLS = \
	build/32/omnimix.dll #\
#	build/64/omnimix.dll

src_hook := \
	pe.c \
	peb.c \
	table.c \

include util/Makefile

UTIL_SOURCES := $(src_util:%.c=util/%.o)
CAPNHOOK_SOURCES += $(src_hook:%.c=capnhook/hook/%.o)

#MAIN_SOURCES = $(UTIL_SOURCES) $(CAPNHOOK_SOURCES) omnimix.o
MAIN_SOURCES = $(UTIL_SOURCES) omnimix.o libavs.a libjubeat.a
DEF_SOURCES = jubeat.def avs.def

SOURCES_32 = $(foreach source,$(MAIN_SOURCES),build/32/$(source))
SOURCES_64 = $(foreach source,$(MAIN_SOURCES),build/64/$(source))

all: build $(EXES) $(DLLS)

build:
	mkdir build build/{32,64} build/{32,64}/{capnhook,capnhook/hook,util}

build/32/omnimix.dll: $(SOURCES_32)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -flto -Lbuild/32 -o $@ $^ -lavs -ljubeat -lpsapi
	$(STRIP) $@

build/64/omnimix.dll: $(SOURCES_64)
	$(CC_64) $(CFLAGS) -shared -flto -Lbuild/64 -o $@ $^ -ljubeat
	$(STRIP) -R .note -R .comment $@

clean:
	rm -f $(EXES) $(DLLS) $(SOURCES_32) $(SOURCES_64) build/{32,64}/libjubeat.a
	rmdir build/{32,64}/{capnhook/hook,capnhook,util} build/{32,64} build

build/32/lib%.a: %.def
	$(DLLTOOL) -p jb -d $< -l $@

build/64/lib%.a: %.def
	$(DLLTOOL_64) -p jb -d $< -l $@

build/32/%.o: %.c
	$(CC) $(CFLAGS) -s -flto -DOMNIMIX_VERSION=\"$(OMNIMIX_VERSION)\" -c -o $@ $<

build/32/%.o: %.cpp
	$(CPP) $(CFLAGS) -s -flto -Wall -c -o $@ $<

build/64/%.o: %.c
	$(CC_64) $(CFLAGS) -s -flto -DOMNIMIX_VERSION=\"$(OMNIMIX_VERSION)\" -c -o $@ $<

build/64/%.o: %.cpp
	$(CPP_64) $(CFLAGS) -s -flto -Wall -c -o $@ $<
