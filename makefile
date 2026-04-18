IRIX_OBJ := \
	build/src/internal.o \
	build/src/int_str.o \
	build/src/int_file.o \
	build/src/int_stat.o \
	build/src/memcpy.o \
	build/src/_doprnt.o \
	build/src/strlen.o \
	build/src/malloc.o \
	build/src/memccpy.o \
	build/src/strchr.o \
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
	build/src/read.o \
	build/src/strncpy.o \
	build/src/strtok.o \
	build/src/write.o \
	build/src/strdup.o \
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

APP := ugen ujoin uld umerge uopt usplit cc cfe as0 as1
EXT := err.english.cc
BIN := $(addprefix bin/,$(APP) ld)
LIB := $(addprefix bin/,$(EXT))
OBJ := $(addprefix build/,$(addsuffix .o,$(APP)))
SRC := $(addprefix build/,$(addsuffix .c,$(APP)))

CC = gcc
AR = ar
CPPFLAGS =
CFLAGS = -fno-strict-aliasing -O2 -Wall -Wextra
LDFLAGS = -Lbuild -s
RECOMPILEFLAGS :=

.PHONY: default
default: $(BIN) $(LIB)

.PHONY: clean
clean:
	rm -f -r bin build

$(LIB): bin/%: donor/%
	@mkdir -p $(dir $@)
	cp -f $< $@

bin/ld: bin/uld
	ln -f -s uld $@

$(BIN):
bin/%: build/%.o build/libirix.a
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $< -lirix -lm

$(OBJ):
$(OBJ): CPPFLAGS += -Isrc
$(OBJ): CFLAGS += -Wno-unused -Wno-array-bounds
build/%.o: build/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(SRC): donor/libc.so.1
build/uld.c: donor/libgen.so
build/umerge.c: donor/libm.so
build/cfe.c: donor/libmalloc.so
build/as0.c build/as1.c: donor/libexc.so
build/ugen.c: RECOMPILEFLAGS += -s
build/%.c: donor/%
	@mkdir -p $(dir $@)
	tools/recompile $(RECOMPILEFLAGS) $^ > $@

build/libirix.a: $(IRIX_OBJ)
	$(AR) rc $@ $(IRIX_OBJ)

$(IRIX_OBJ): CFLAGS += -Wpedantic
build/src/signal.o: CFLAGS += -Wno-deprecated-declarations
build/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c -o $@ $<

-include $(IRIX_OBJ:.o=.d)
