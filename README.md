# ido53
A static recompilation of IRIS Development Option version 5.3 for IRIX.  This is built on the pioneering technology from [metapro](https://github.com/devwizard64/metapro) used to recompile Nintendo 64 games.  It only provides the necessary software to compile *Super Mario 64* in my disassembly/decompilation of the game, which you can find [here](https://github.com/devwizard64/metarep/tree/main/UNSM).

Static recompilation involves converting a binary into C code that may be compiled to run on a different platform.  This technique allows for optimization of the entire binary at compile time, removing the overhead of emulation and providing performance comparable to compiling the original source code.  The following describes the recompilation process in further detail:
* The source binary is analyzed to find structural information, such as C function entry points.
* Each machine instruction is decoded and converted to a line of C code.  For example, `addiu t0,a0,a1` becomes `t0 = a0 + a1;`.
* Additional pattern-matching techniques are used to translate complex instruction patterns (such as jump tables or function calls) into equivalent C code.
* System calls or library functions are reimplemented as equivalent system calls or functionality specific to the target platform.
* The generated C code is compiled with aggressive optimization flags and built into a new binary.

## Building
Install dependencies (Debian):
```
apt install make python3 gcc
```
Build:
```
make
```
Most platforms should work with `mmap` and `alloca` functionality.  If your compiler does not support `alloca`, remove `-DALLOCA` from `CPPFLAGS`.  If the software builds, but you have issues running the software, you may try removing `-DMMAP`.  You will have to rebuild the software from scratch if you change these flags:
```
make clean && make
```
