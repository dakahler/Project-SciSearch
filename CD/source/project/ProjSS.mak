# ------------------------------------------
# Title:		ProjSS
# File:			ProjSS.mak
# Author:		Dave Kahler
# 
# Info:			PSS makefile
#				Standard makefile for SDK,
#				modified slightly to point to
#				the files I need to compile.
# 
# -------------------------------------------

# -------------------------------------------
# Define some directories;
# -------------------------------------------
SRCDIR  = C:\PSS\Program\ProjSS
CMPDIR  = C:\gba\bin
LIBDIR  = C:\gba\lib\gcc-lib\arm-agb-elf\3.0.2\interwork
LIBDIR2 = C:\gba\arm-agb-elf\lib\interwork
INCDIR  = C:\gba\lib\gcc-lib\arm-agb-elf\3.0.2\include
INCDIR2 = C:\gba\arm-agb-elf\include

# -------------------------------------------
# Define what extensions we use;
# -------------------------------------------
.SUFFIXES : .cpp .s

# -------------------------------------------
# Define the flags for the compilers;
# -------------------------------------------
CFLAGS  = -I $(INCDIR2) -I $(INCDIR) -I $(SRCDIR) -mthumb-interwork -c -g -O3 -Wall -fverbose-asm
SFLAGS  = -I $(INCDIR2) -I $(INCDIR) -mthumb-interwork 
LDFLAGS = -L $(LIBDIR) -L $(LIBDIR2) -T LinkScript 

# -------------------------------------------
# Define the list of all O files;
# -------------------------------------------
O_FILES			 =  boot.o				\
					vblank.o			\
					crtbegin.o			\
					crtend.o			\
					PSSInit.o			\
					PSSDisplay.o		\
					PSSInterface.o		\
					PSSSimulation.o		\
#					PSSOAM_alloc.o		\
					main.o

# -------------------------------------------
# Define the final dependecy;
# -------------------------------------------
all : ProjSS.bin

# -------------------------------------------
# Define the copy from .elf to .bin file
# -------------------------------------------
ProjSS.bin : ProjSS.elf
	objcopy -v -O binary ProjSS.elf ProjSS.bin
	-@echo ------------------------------------------ 
	-@echo Done 
	-@echo ------------------------------------------ 
	
# -------------------------------------------
# Define the linker instruction;
# -------------------------------------------
ProjSS.elf : $(O_FILES)
	ld $(LDFLAGS) -o ProjSS.elf $(O_FILES) -lstdc++ -lgcc -lc  
	-@echo ------------------------------------------ 
	-@echo Linking Done
	-@echo ------------------------------------------ 

# -------------------------------------------
# Define each compile;
# -------------------------------------------
{$(SRCDIR)}.cpp.o::
	gcc  $(CFLAGS) $< 
	-@echo ------------------------------------------ 
	-@echo CPP-Sources Compiled 
	-@echo ------------------------------------------ 

# -------------------------------------------
# Define each assemble;
# -------------------------------------------
{$(SRCDIR)}.s.o:
	as $(SFLAGS) $(SRCDIR)\$*.s -o$@
	-@echo ------------------------------------------ 
	-@echo ASM-Sources Compiled 
	-@echo ------------------------------------------ 
	

# -------------------------------------------
# EOF;

