#ifndef __APP_H__
#define __APP_H__

#define _GNU_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/times.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define UNUSED __attribute__((unused))

#ifdef __GNUC__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define EB
#endif
#endif

#ifdef WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif

#define NULLPTR 0
typedef uint32_t PTR;

#define eexit() exit(EXIT_FAILURE)

#define wprint(...) fprintf(stderr, "warning: " __VA_ARGS__)
#define eprint(...) {fprintf(stderr, "error: " __VA_ARGS__); eexit();}
#ifdef DEBUG
#define pdebug printf
#define wdebug wprint
#define edebug eprint
#else
#define pdebug(...) {}
#define wdebug(...) {}
#define edebug(...) {}
#endif

#include "cpu.h"
#include "int_str.h"
#include "int_c.h"
#include "int_brk.h"
#include "int_malloc.h"
#include "int_errno.h"
#include "int_file.h"
#include "int_fmt.h"
#include "int_stat.h"
#include "int_signal.h"
#include "int_tree.h"

#endif /* __APP_H__ */
