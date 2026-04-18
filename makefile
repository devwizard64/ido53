IRIX_OBJ := \
	build/src/internal.o \
	build/src/int_str.o \
	build/src/int_mem.o \
	build/src/int_file.o \
	build/src/int_stat.o \
	build/src/memcpy.o \
	build/src/_doprnt.o \
	build/src/strlen.o \
	build/src/malloc.o \
	build/src/memccpy.o \
	build/src/strchr.o \
	build/src/free.o \
	build/src/strcmp.o \
	build/src/strcpy.o \
	build/src/memset.o \
	build/src/fgets.o \
	build/src/strncmp.o \
	build/src/sprintf.o \
	build/src/calloc.o \
	build/src/memcmp.o \
	build/src/strcat.o \
	build/src/getenv.o \
	build/src/realloc.o \
	build/src/read.o \
	build/src/strncpy.o \
	build/src/strtok.o \
	build/src/write.o \
	build/src/strdup.o \
	build/src/qsort.o \
	build/src/getcwd.o \
	build/src/bcmp.o \
	build/src/strtol.o \
	build/src/__filbuf.o \
	build/src/strrchr.o \
	build/src/atoi.o \
	build/src/stat.o \
	build/src/fflush.o \
	build/src/fclose.o \
	build/src/fopen.o \
	build/src/fstat.o \
	build/src/open.o \
	build/src/access.o \
	build/src/sbrk.o \
	build/src/signal.o \
	build/src/times.o \
	build/src/atof.o \
	build/src/fcntl.o \
	build/src/fread.o \
	build/src/strstr.o \
	build/src/gethostname.o \
	build/src/__flsbuf.o \
	build/src/time.o \
	build/src/ungetc.o \
	build/src/chmod.o \
	build/src/rename.o \
	build/src/unlink.o \
	build/src/mmap.o \
	build/src/pathconf.o \
	build/src/mktemp.o \
	build/src/fseek.o \
	build/src/fwrite.o \
	build/src/fgetc.o \
	build/src/fdopen.o \
	build/src/freopen.o \
	build/src/puts.o \
	build/src/rewind.o \
	build/src/setvbuf.o \
	build/src/fputc.o \
	build/src/fscanf.o \
	build/src/munmap.o \
	build/src/kill.o \
	build/src/utime.o \
	build/src/creat.o \
	build/src/ctime.o \
	build/src/_cleanup.o \
	build/src/tempnam.o \
	build/src/fp_class_d.o \
	build/src/strtoul.o \
	build/src/strtod.o \
	build/src/strtoull.o \
	build/src/strtoll.o \
	build/src/perror.o \
	build/src/tsearch.o \
	build/src/__assert.o \
	build/src/execvp.o \
	build/src/ctype.o

APP := driver ld ugen ujoin umerge uopt usplit cfe as0 as1
BIN := $(patsubst %,usr/lib/%,$(APP)) usr/bin/cc usr/bin/as usr/bin/ld usr/lib/uld
OBJ := $(patsubst %,build/%.o,$(APP))
SRC := $(patsubst %,build/%.c,$(APP))

CC = gcc
AR = ar
CPPFLAGS = -Iinclude
CFLAGS = -fno-strict-aliasing -O2 -Wall -Wextra
LDFLAGS = -Lbuild -s

.PHONY: default
default: $(BIN)

.PHONY: clean
clean:
	rm -f -r build $(BIN)

usr/lib/%: build/%.o build/libirix.a
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $< -lirix -lm

usr/bin/cc usr/bin/as: usr/lib/driver
	@mkdir -p $(dir $@)
	ln -f -s ../lib/driver $@

usr/bin/ld: usr/lib/ld
	@mkdir -p $(dir $@)
	ln -f -s ../lib/ld $@

usr/lib/uld: usr/lib/ld
	ln -f -s ld $@

$(OBJ):
build/%.o: build/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Wno-unused -Wno-array-bounds -c -o $@ $<

$(SRC):
build/%.c: donor/%
	@mkdir -p $(dir $@)
	tools/recompile $< usr/lib > $@

build/libirix.a: $(IRIX_OBJ)
	$(AR) rc $@ $(IRIX_OBJ)

$(IRIX_OBJ): CFLAGS += -Wpedantic
build/src/signal.o: CFLAGS += -Wno-deprecated-declarations
build/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c -o $@ $<

-include $(IRIX_OBJ:.o=.d)
