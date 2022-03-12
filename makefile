SRC_OBJ := \
	build/src/app.o                 \
	build/src/int_str.o             \
	build/src/int_c.o               \
	build/src/int_sbrk.o            \
	build/src/int_malloc.o          \
	build/src/int_errno.o           \
	build/src/int_file.o            \
	build/src/int_xfmtf.o           \
	build/src/int_stat.o            \
	build/src/int_sig.o             \
	build/src/int_tree.o            \
	build/src/_rld_new_interface.o  \
	build/src/memcpy.o              \
	build/src/_doprnt.o             \
	build/src/strlen.o              \
	build/src/malloc.o              \
	build/src/memccpy.o             \
	build/src/strchr.o              \
	build/src/free.o                \
	build/src/strpbrk.o             \
	build/src/strcmp.o              \
	build/src/strcpy.o              \
	build/src/memset.o              \
	build/src/fgets.o               \
	build/src/bcopy.o               \
	build/src/strncmp.o             \
	build/src/bzero.o               \
	build/src/sprintf.o             \
	build/src/calloc.o              \
	build/src/ioctl.o               \
	build/src/memcmp.o              \
	build/src/strcat.o              \
	build/src/getenv.o              \
	build/src/realloc.o             \
	build/src/read.o                \
	build/src/strncpy.o             \
	build/src/strtok.o              \
	build/src/__ll_rshift.o         \
	build/src/write.o               \
	build/src/tolower.o             \
	build/src/strncat.o             \
	build/src/strdup.o              \
	build/src/qsort.o               \
	build/src/getcwd.o              \
	build/src/bcmp.o                \
	build/src/strtol.o              \
	build/src/__filbuf.o            \
	build/src/strrchr.o             \
	build/src/atoi.o                \
	build/src/stat.o                \
	build/src/fflush.o              \
	build/src/fclose.o              \
	build/src/gettxt.o              \
	build/src/fprintf.o             \
	build/src/fopen.o               \
	build/src/fstat.o               \
	build/src/isatty.o              \
	build/src/open.o                \
	build/src/access.o              \
	build/src/sbrk.o                \
	build/src/ftell.o               \
	build/src/close.o               \
	build/src/signal.o              \
	build/src/times.o               \
	build/src/atof.o                \
	build/src/fcntl.o               \
	build/src/lseek.o               \
	build/src/_atod.o               \
	build/src/wait.o                \
	build/src/fread.o               \
	build/src/exit.o                \
	build/src/getpid.o              \
	build/src/fork.o                \
	build/src/strstr.o              \
	build/src/_exithandle.o         \
	build/src/gethostname.o         \
	build/src/__flsbuf.o            \
	build/src/time.o                \
	build/src/ungetc.o              \
	build/src/syssgi.o              \
	build/src/fcvt.o                \
	build/src/_prctl.o              \
	build/src/chmod.o               \
	build/src/getpagesize.o         \
	build/src/__readenv_sigfpe.o    \
	build/src/rename.o              \
	build/src/unlink.o              \
	build/src/mmap.o                \
	build/src/dup2.o                \
	build/src/pathconf.o            \
	build/src/ftruncate.o           \
	build/src/flock.o               \
	build/src/mkstemp.o             \
	build/src/strerror.o            \
	build/src/strcspn.o             \
	build/src/fputs.o               \
	build/src/gets.o                \
	build/src/putc.o                \
	build/src/mktemp.o              \
	build/src/getc.o                \
	build/src/fseek.o               \
	build/src/fwrite.o              \
	build/src/fgetc.o               \
	build/src/fdopen.o              \
	build/src/freopen.o             \
	build/src/puts.o                \
	build/src/rewind.o              \
	build/src/setvbuf.o             \
	build/src/fputc.o               \
	build/src/fscanf.o              \
	build/src/pipe.o                \
	build/src/munmap.o              \
	build/src/kill.o                \
	build/src/umask.o               \
	build/src/utime.o               \
	build/src/sigset.o              \
	build/src/creat.o               \
	build/src/dup.o                 \
	build/src/ctime.o               \
	build/src/tmpnam.o              \
	build/src/_cleanup.o            \
	build/src/tempnam.o             \
	build/src/__ll_to_d.o           \
	build/src/set_fpc_csr.o         \
	build/src/__ull_to_d.o          \
	build/src/__f_to_ll.o           \
	build/src/__d_to_ll.o           \
	build/src/__ull_to_f.o          \
	build/src/__ll_to_f.o           \
	build/src/get_fpc_csr.o         \
	build/src/fp_class_d.o          \
	build/src/__d_to_ull.o          \
	build/src/__ll_mul.o            \
	build/src/__f_to_ull.o          \
	build/src/atol.o                \
	build/src/strtoul.o             \
	build/src/strtod.o              \
	build/src/toupper.o             \
	build/src/ldexp.o               \
	build/src/ecvt.o                \
	build/src/__ll_div.o            \
	build/src/__ll_lshift.o         \
	build/src/__ull_rem.o           \
	build/src/__ll_rem.o            \
	build/src/__ull_div.o           \
	build/src/strtoull.o            \
	build/src/strtoll.o             \
	build/src/__ull_rshift.o        \
	build/src/perror.o              \
	build/src/tsearch.o             \
	build/src/tfind.o               \
	build/src/cfree.o               \
	build/src/__assert.o            \
	build/src/memalign.o            \
	build/src/execvp.o              \
	build/src/execlp.o              \
	build/src/getpgrp.o             \
	build/src/printf.o              \
	build/src/_exit.o               \
	build/src/execve.o

ELF := ugen ujoin uld umerge uopt usplit cc cfe as1
BIN := $(addprefix bin/,$(ELF))
OBJ := $(addprefix build/,$(addsuffix .o,$(ELF)))
SRC := $(addprefix build/,$(addsuffix .c,$(ELF)))

CC      := cc
CCFLAG  := -fno-pie -fno-strict-aliasing -DMMAP -DALLOCA -O2 -Wall -Wextra
WFLAG   := -Wno-uninitialized

.PHONY: default
default: $(BIN)

.PHONY: clean
clean:
	rm -f -r bin build

$(BIN):
bin/%: build/%.o $(SRC_OBJ) | bin
	$(CC) -no-pie -s -o $@ $^

$(OBJ):
build/%.o: build/%.c | build
	$(CC) $(CCFLAG) $(WFLAG) -Isrc -c -o $@ $<

$(SRC): donor/libc.so.1.sym
build/cfe.c: donor/libmalloc.so.sym
build/%.c: donor/%.text.bin donor/%.data.bin donor/%.sym | build
	tools/elf $@ $^

$(SRC_OBJ): src/app.h
build/src/%.o: src/%.c | build/src
	$(CC) $(CCFLAG) -c -o $@ $<

bin build build/src:
	mkdir -p $@
